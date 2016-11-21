<?php

$varValue = $_GET[flipCommand];

// Set device controle options (See man page for stty)
exec("/bin/stty -F /dev/ttyACM0 9600");

// Open serial port
$fp=fopen("/dev/ttyACM0","c+");
if(!$fp) die("Can't open device");

// Set blocking mode for writing
stream_set_blocking($fp,1);
fwrite($fp,$varValue);

?>
