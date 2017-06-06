<!DOCTYPE html>

<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="chrome=1,IE=edge" />
    <meta name="viewport" content="user-scalable=no, width=800" />
    <meta charset="utf-8" />
    <meta http-equiv="refresh" content="5">
    <title>.: Canon Remote :.</title>
    <style type="text/css">
      body {
        background-color: #FFFFFF;
        margin: 0px;
        font-family: Verdana;
        font-size: 12px;
      }
      #centered {
        position:absolute;
        top: 0%;
        left: 50%;
        width:30em;
        height:18em;
        background-color:#FFFFFF;
        margin-top: 10px; /*set to a negative number 1/2 of your height*/
        margin-left: -400px; /*set to a negative number 1/2 of your width*/
      }
    </style>
  </head>
<html>
    <head>
        <meta charset="utf-8" />
        <title>.: Canon Remote :.</title>
    </head>
 
    <div id="centered">
      <div style="margin:auto;width:800px;background-color:#FFFFFF;">
        <table>

          <tr>
<?php
  exec ("i2cget -y 0 0x08 0x20", $valExpTimeHigh, $return);
  if (is_array($valExpTimeHigh)) {
    $ExposureTime = hexdec($valExpTimeHigh[0]) << 8;
  } else {
    $ExposureTime = hexdec($valExpTimeHigh) << 8;
  }
  exec ("i2cget -y 0 0x08 0x21", $valExpTimeLow, $return);
  if (is_array($valExpTimeLow)) {
    $ExposureTime = $ExposureTime + hexdec($valExpTimeLow[0]);
  } else {
    $ExposureTime = $ExposureTime + hexdec($valExpTimeLow);
  }
  echo '<td>exposure time</td>';
  echo '<td><input type="number" name="ExposureTime" id="exposuretime" max="1800" min="5" value="';
  echo $ExposureTime;
  echo '">';
  echo '<button onclick="setExposureTime()">Set</button></td>';
?>
          </tr>

          <tr>
<?php
  exec ("i2cget -y 0 0x08 0x30", $valETAHigh, $return);
  if (is_array($valETAHigh)) {
    $ETA = floatval(hexdec($valETAHigh[0]) << 8);
  } else {
    $ETA = floatval(hexdec($valETAHigh) << 8);
  }
  exec ("i2cget -y 0 0x08 0x31", $valETALow, $return);
  if (is_array($valETALow)) {
    $ETA = $ETA + floatval(hexdec($valETALow[0]));
  } else {
    $ETA = $ETA + floatval(hexdec($valETALow));
  }
  $ETAm = floor($ETA/60.);
  $ETAs = floor($ETA - $ETAm*60.);
  echo '<td>eta</td>';
  echo '<td>';
  printf("%02dm", $ETAm);
  echo ':';
  printf("%02ds", $ETAs);
  echo '</td>';
?>
          </tr>

          <tr>
<?php
  exec ("i2cget -y 0 0x08 0x11", $valImageLoopStatus, $return);
  if (is_array($valImageLoopStatus)) {
    $ImageLoopStatus = hexdec($valImageLoopStatus[0]);
  } else {
    $ImageLoopStatus = hexdec($valImageLoopStatus);
  }

  echo '<td>image loop</td>';
  if ($ImageLoopStatus == 0 ) {
    echo ("<td><img id='loopon' src='data/button_green.png' onclick='changeImageLoop();'/></td>");
  } else {
    echo ("<td><img id='loopon' src='data/button_red.png' onclick='changeImageLoop();'/></td>");
  }
?>
          </tr>

          <tr>
<?php
  exec ("i2cget -y 0 0x08 0x12", $valFocusStatus, $return);
  if (is_array($valFocusStatus)) {
    $FocusStatus = hexdec($valFocusStatus[0]);
  } else {
    $FocusStatus = hexdec($valFocusStatus);
  }

  echo '<td>focus</td>';
  if ($FocusStatus == 0 ) {
    echo ("<td><img id='focuson' src='data/button_green.png' onclick='changeFocus();'/></td>");
  } else {
    echo ("<td><img id='focuson' src='data/button_red.png' onclick='changeFocus();'/></td>");
  }
?>
          </tr>

          <tr>
<?php
  exec ("i2cget -y 0 0x08 0x13", $valTriggerStatus, $return);
  if (is_array($valTriggerStatus)) {
    $TriggerStatus = hexdec($valTriggerStatus[0]);
  } else {
    $TriggerStatus = hexdec($valTriggerStatus);
  }

  echo '<td>trigger</td>';
  if ($TriggerStatus == 0 ) {
    echo ("<td><img id='triggeron' src='data/button_green.png' onclick='changeTrigger();'/></td>");
  } else {
    echo ("<td><img id='triggeron' src='data/button_red.png' onclick='changeTrigger();'/></td>");
  }
?>
          </tr>

        </table>
      </div>
    </div>

  <!-- javascript -->
  <script src="script.js"></script>
</body>
</html>
