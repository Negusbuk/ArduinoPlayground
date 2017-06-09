<?php
if (isset ( $_GET ["value"] )) {
	$value = strip_tags ( $_GET ["value"] );
	
	$command = "i2cget -y 0 0x08 0x12";
	exec ( $command, $status, $return );
	
	$ret = hexdec ( $status [0] );
	if ($ret == "0") {
		$ret = "1";
	} else {
		$ret = "0";
	}
	
	$command = "i2cset -y 0 0x08 0x12 " . $ret;
	exec ( $command, $status, $return );
	
	echo ($ret);
} else {
	echo ("fail");
}
?>
