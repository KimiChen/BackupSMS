<?php
error_reporting(E_ERROR | E_WARNING | E_PARSE);

$SMSContentKey = 'github.com/KimiChen/BackupSMS';

//数据库地址
$serverHost = SAE_MYSQL_HOST_M;
//数据库端口
$serverPort = SAE_MYSQL_PORT;
//数据库库名
$serverDatabase = SAE_MYSQL_DB;
//数据库用户名
$serverUser = SAE_MYSQL_USER;
//数据库密码
$serverPasswd = SAE_MYSQL_PASS;

//数据库连接
if (!$link = mysql_connect($serverHost.':'.$serverPort, $serverUser, $serverPasswd)) {
	exit('connect error:' . mysql_error() . "\n");
}
if (!mysql_select_db($serverDatabase)) {
	exit('select db error:' . mysql_error() . "\n");
}
mysql_query("SET NAMES utf8");

//初始化参数
$mod = strtolower(trim($_GET['mod']));
$uuid = strtolower(trim($_GET['uuid']));
if(strlen($uuid) != 12 || !in_array($mod, array('permit','sms','ad'))) {
	exit("success\n");
}


if($mod == 'permit'){
	//获得SMS短消息权限
	$sql = "SELECT rowid FROM bsms_data_sms WHERE uuid='{$uuid}' ORDER BY id DESC LIMIT 1";
	$query = mysql_query($sql);
	$resS = mysql_fetch_array($query, MYSQL_ASSOC);
	//0表示用户无权限给平台传送SMS数据，其他数字表示平台已有的SMS最大rowid
	if($resS['rowid']) {
		$smsid = $resS['rowid'];
	} else {
		$smsid = 0;
	}

	//获得AddressBook地址簿权限权限
	$sql = "SELECT address, address_original FROM bsms_data_addressbook WHERE uuid='{$uuid}' AND status = '1' ORDER BY id ASC LIMIT 1";
	$query = mysql_query($sql);
	$resA = mysql_fetch_array($query, MYSQL_ASSOC);
	//0表示用户无权限给平台传送AddressBook数据，其他数字表示平台已有的AddressBook最大rowid
	if($resA['address']) {
		$returnARR = mobileNumGet($resA['address']);
		$returnARR[] = "'{$resA['address']}'";
		$returnARR[] = "'{$resA['address_original']}'";
		$returnARR = array_unique($returnARR);
		$adid = implode(",", $returnARR);
	} else {
		$adid = NULL;
	}

	//获得帐号是否已过试用期
	//$sql = "SELECT rowid FROM bsms_user_perion WHERE uuid='{$uuid}' ORDER BY id DESC LIMIT 1";
	//$query = mysql_query($sql);
	//$resP = mysql_fetch_array($query, MYSQL_ASSOC);
	//0表示用户无权限，1表示用户有权限
	if($resP['rowid']) {
		$permitid = $resP['rowid'];
	} else {
		$permitid = 1;
	}
	mysql_close($link);
	echo "[{$smsid}/{$adid}/{$permitid}]";

	exit();
} elseif ($mod == 'sms') {

	//如果是iMessage，由于iMessage没有address值，这里补充上
	if($_POST['is_madrid'] == 1) {
		$_POST['address'] = $_POST['madrid_handle'];
		$_POST['date'] = $_POST['date']+978220800;
	}
	//如果text为空则subject赋给text
	if(!$_POST['text'] && $_POST['subject']) {
		$_POST['text'] = $_POST['subject'];
	}
	//替换sqlite3默认为空的关键字
	if($_POST['address'] == '(null)') $_POST['address'] = '';
	if($_POST['text'] == '(null)') $_POST['text'] = '';

	//过滤所有需要的数据
	$sql_uuid = strtolower(trim($_GET['uuid']));
	$sql_rowid = strtolower(trim($_POST['ROWID']));
	$sql_folder = mobileFolderFilter($_POST['flags'], $_POST['madrid_date_read'], $_POST['madrid_date_delivered']);
	$sql_type = strtolower(trim($_POST['is_madrid']));
	$sql_status = 0;
	$sql_address = mobileNumFilter(strtolower(trim($_POST['address'])));
	$sql_date = strtolower(trim($_POST['date']));
	$sql_time_creat = time();
	$sql_message = strtolower(trim($_POST['text']));

	//加密用户数据
	$sql_message = MooAuthCode($sql_message, 'ENCODE', $SMSContentKey.$sql_uuid, 0, false);

	//检查数据完整性
	if(!$sql_uuid || !$sql_rowid || !$sql_address || !$sql_date || !$sql_message) {
		exit("post error\n");
	}

	//将数据插入数据库
	$sql = "INSERT INTO bsms_data_sms SET uuid='{$uuid}', rowid='{$sql_rowid}', folder='{$sql_folder}', type='{$sql_type}', address='{$sql_address}', date='{$sql_date}', time_creat='{$sql_time_creat}', message='{$sql_message}'";
	mysql_query($sql);

	//如果数据出错，记录错误数据
	if(mysql_errno() != 0 ) {
		mysql_query("INSERT INTO bsms_log SET content_sql='".addslashes($sql)."', content_log='".addslashes(mysql_error())."'");
		exit( "sql error\n");
	} else {
		$sql_address_original = trim($_POST['address']);

		$sql = "SELECT id FROM bsms_data_addressbook WHERE uuid='{$uuid}' AND address='{$sql_address}' LIMIT 1";
		$query = mysql_query($sql);
		$resN = mysql_fetch_array($query, MYSQL_ASSOC);
		//插入addressbook
		if(!$resN['id']) {
			$sql = "INSERT INTO bsms_data_addressbook SET uuid='{$uuid}', status='1', num_sms = '1', address = '{$sql_address}', address_original = '{$sql_address_original}', time_update='{$sql_time_creat}'";
			mysql_query($sql);
		//更新的数量addressbook
		} else {
			$sql = "SELECT count(*) as num_sms FROM bsms_data_sms WHERE uuid='{$uuid}' AND address='{$sql_address}'";
			$query = mysql_query($sql);
			$resS = mysql_fetch_array($query, MYSQL_ASSOC);
			if($resS['num_sms']) {
				$sql_id = $resN['id'];
				$sql_num_sms = $resS['num_sms'];
				$sql = "UPDATE bsms_data_addressbook SET num_sms = '{$sql_num_sms}' WHERE id = '{$sql_id}' AND uuid='{$uuid}'";
				mysql_query($sql);
			}
		}
	}

	echo "post ok\n";
} elseif ($mod == 'ad') {

	$sql_uuid = strtolower(trim($_GET['uuid']));

	if($_POST['returnid']) {
		
		$returnid = explode(',', trim($_POST['returnid']));
		$idStr = substr($returnid[0], 1, count($returnid[0])-2);
		$sql_address = mobileNumFilter(strtolower(trim($idStr)));
		//插入addressbook
		$sql = "SELECT id FROM bsms_data_addressbook WHERE uuid='{$uuid}' AND address='{$sql_address}' LIMIT 1";
		$query = mysql_query($sql);
		$resN = mysql_fetch_array($query, MYSQL_ASSOC);
		if($resN['id']) {
			$sql_id = $resN['id'];
			$sql = "UPDATE bsms_data_addressbook SET status = '0' WHERE id = '{$sql_id}' AND uuid='{$uuid}'";
			mysql_query($sql);
		}
		echo "sms returnid ok\n";
	} else {
		$sql_address = mobileNumFilter(strtolower(trim($_POST['Address'])));
		$nameArr = mobileNameFilter($_POST);

		//插入addressbook
		$sql = "SELECT id FROM bsms_data_addressbook WHERE uuid='{$uuid}' AND address='{$sql_address}' LIMIT 1";
		$query = mysql_query($sql);
		$resN = mysql_fetch_array($query, MYSQL_ASSOC);
		if($resN['id']) {
			$sql_id = $resN['id'];
			$sql = "UPDATE bsms_data_addressbook SET status = '0', name_f = '{$nameArr['f']}', name_l = '{$nameArr['l']}', time_update='".time()."' WHERE id = '{$sql_id}' AND uuid='{$uuid}'";
			mysql_query($sql);
		}
		echo "sms update ok\n";
	}

} else {
	exit('else');
}

/**
 * 把换行符替换成空
 * @param $string - 待处理的字符串
 * @return 返回字符串
 */
function replace_n_2_br($str) {
	$order = array("\r\n", "\n", "\r");
	$replace = '';
	$str = str_replace($order, $replace, $str);
	return $str;
}

/**
 * 组成标准格式的用户名
 * @param $value - 待处理的数据
 * @return 返回用户名
 */
function mobileNameFilter($value) {

	$name['f'] = ($value['First'] == '(null)') ? '' : trim($value['First']);
	$name['l'] = ($value['Last'] == '(null)') ? '' : trim($value['Last']);
	return $name;
}

/**
 * 过滤并处理手机号码为标准格式
 * @param $value - 待处理的手机号码
 * @return 返回手机号码
 */
function mobileNumFilter($value) {
	$value = str_replace(" ", "" ,$value);
	$value = str_replace("-", "" ,$value);

	//处理中国短信号码
	$value_sub = substr($value, 0, 2);
	if($value_sub == '86' && strlen($value) == 13) {
		$value= substr($value, 2);
	}

	return trim($value);
}

/**
 * 返回不标准的手机格式
 * @param $value - 待处理的手机号码
 * @return 返回手机号码
 */
function mobileNumGet($value) {

	$returnArr = array();

	//处理中国短信号码
	if(strlen($value) == 11) {
		$value_sub1 = substr($value, 0, 3);
		$value_sub2 = substr($value, 3, 4);
		$value_sub3 = substr($value, 7, 4);
		$value1= "'{$value_sub1}-{$value_sub2}-{$value_sub3}'";
		$returnArr[] = $value1;

		$returnArr[] = "'86{$value}'";
		$returnArr[] = "'+86{$value}'";
	}
	return $returnArr;
}

/**
 * 识别短信为正确的格式
 * @param $value_flags - 待处理的手机号码
 * @param $value_madrid_date_read - iMessage独有字段
 * @param $value_madrid_date_delivered - iMessage独有字段
 * @return 1表示发件箱，0表示收件箱
 */
function mobileFolderFilter($value_flags, $value_madrid_date_read, $value_madrid_date_delivered) {

	if($value_flags == 3) {
		$value = 1;
	} elseif($value_flags == 2) {
		$value = 0;
	} elseif($value_madrid_date_read) {
		$value = 0;
	} elseif($value_madrid_date_delivered) {
		$value = 1;
	}else {
		$value = 0;
	}
	return $value;
}

/**
 * 调试代码函数
 * @param $value - 待输出的变量
 */
function d($v) {
	echo "--------------------------------------------print_r--------------------------------------------------<br>";
	echo "<pre>";
	print_r($v);
	echo "</pre>";
}

/**
 * 采用RC4为核心算法，主要用于对文本的加密或者解密
 * @param $string - 加密或解密的串
 * @param $operation - DECODE 解密；ENCODE 加密
 * @param $key - 密钥 默认为AUTHKEY常量
 * @param $expiry - 过期时间，默认为不过期
 * @param $base64 - 输出串是否使用base64_encode序列化
 * @return 返回字符串
 */
function MooAuthCode($string, $operation = 'DECODE', $key = '', $expiry = 0, $base64 = true) {
	/**
	 * $ckey_length 随机密钥长度 取值 0-32;
	 * 加入随机密钥，可以令密文无任何规律，即便是原文和密钥完全相同，加密结果也会每次不同，增大破解难度。
	 * 取值越大，密文变动规律越大，密文变化 = 16 的 $ckey_length 次方
	 * 当此值为 0 时，则不产生随机密钥
	 */
	$ckey_length = 0;

	//密匙
	$key = md5($key != '' ? $key : 'thisistmpkey');
	//密匙a会参与加解密
	$keya = md5(substr($key, 0, 16));
	//密匙b会用来做数据完整性验证
	$keyb = md5(substr($key, 16, 16));
	//密匙c用于变化生成的密文
	$keyc = $ckey_length ? ($operation == 'DECODE' ? substr($string, 0, $ckey_length): substr(md5(microtime()), -$ckey_length)) : '';

	//MooAuthCode参与运算的密匙cryptkey
	$cryptkey = $keya.md5($keya.$keyc);
	$key_length = strlen($cryptkey);

	/**
	 * 明文，前10位用来保存时间戳，解密时验证数据有效性，10到26位用来保存$keyb(密匙b)，解密时会通过这个密匙验证数据完整性
	 * 如果是解码的话，会从第$ckey_length位开始，因为密文前$ckey_length位保存 动态密匙，以保证解密正确
	 */
	if($base64) {
		$string = $operation == 'DECODE' ? base64_decode(substr($string, $ckey_length)) : sprintf('%010d', $expiry ? $expiry + time() : 0).substr(md5($string.$keyb), 0, 16).$string;
	} else {
		$string = $operation == 'DECODE' ? substr($string, $ckey_length) : sprintf('%010d', $expiry ? $expiry + time() : 0).substr(md5($string.$keyb), 0, 16).$string;
	}
	$string_length = strlen($string);

	$result = '';
	$box = range(0, 255);
	$rndkey = array();

	//RC4算法的初始化（KSA）部分，主要为获得不同的子密钥序列$box
	for($i = 0; $i <= 255; $i++) {
		$rndkey[$i] = ord($cryptkey[$i % $key_length]);
	}

	for($j = $i = 0; $i < 256; $i++) {
		$j = ($j + $box[$i] + $rndkey[$i]) % 256;
		$tmp = $box[$i];
		$box[$i] = $box[$j];
		$box[$j] = $tmp;
	}

	//RC4算法的伪随机子密码生成（PRGA)部分，采用之前生成的子密钥序列$box和明文进行异或运算，得到密文（解密也是同样的过程）
	for($a = $j = $i = 0; $i < $string_length; $i++) {
		$a = ($a + 1) % 256;
		$j = ($j + $box[$a]) % 256;
		$tmp = $box[$a];
		$box[$a] = $box[$j];
		$box[$j] = $tmp;
		$result .= chr(ord($string[$i]) ^ ($box[($box[$a] + $box[$j]) % 256]));
	}

	/**
	 * substr($result, 0, 10) == 0 验证数据有效性
	 * substr($result, 0, 10) - time() > 0 验证数据有效性
	 * substr($result, 10, 16) == substr(md5(substr($result, 26).$keyb), 0, 16) 验证数据完整性
	 * 验证数据有效性，请看未加密明文的格式
	 */
	if($operation == 'DECODE') {
		if((substr($result, 0, 10) == 0 || substr($result, 0, 10) - time() > 0) && substr($result, 10, 16) == substr(md5(substr($result, 26).$keyb), 0, 16)) {
			return substr($result, 26);
		} else {
			return '';
		}
	} else {
		if($base64) {
			return $keyc.str_replace('=', '', base64_encode($result));
		} else {
			return $keyc.$result;
		}
	}
}