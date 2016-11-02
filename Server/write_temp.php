<?php

if (!isset($_GET["temp"]) || !isset($_GET["key"]))
{
exit("nope");
}

$data["date"] = date('d-m-Y H:i');
$data["temp"] = $_GET["temp"];

if($_GET["key"] != "secretKey") {
	exit("nope");
}

$fp = fopen('/var/www/phib.io/weather/temps.json', 'a');
fwrite($fp, json_encode($data).",");
fclose($fp);
?>
