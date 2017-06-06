<?php
if (isset($_GET["value"])) {
  $value = strip_tags($_GET["value"]);
  
  if ((is_numeric($value)) && ($value <= 1800) && ($value >= 5) ) {
    
    $command = "i2cset -y 0 0x08 0x10 ".$value." w";
    exec ($command, $status, $return);

    $command = "i2cget -y 0 0x08 0x20";
    exec ($command, $valExpTimeHigh, $return);
    if (is_array($valExpTimeHigh)) {
      $ExposureTime = hexdec($valExpTimeHigh[0]) << 8;
    } else {
      $ExposureTime = hexdec($valExpTimeHigh) << 8;
    }
    
    $command = "i2cget -y 0 0x08 0x21";
    exec ($command, $valExpTimeLow, $return);
    if (is_array($valExpTimeLow)) {
      $ExposureTime = $ExposureTime + hexdec($valExpTimeLow[0]);
    } else {
      $ExposureTime = $ExposureTime + hexdec($valExpTimeLow);
    }
    
    echo $ExposureTime;

  } else { 
    echo("fail");
  }
} else {
  echo("fail");
}
?>
