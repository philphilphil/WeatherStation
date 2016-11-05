<?php

if (!isset($_GET["tempi"]) || !isset($_GET["tempo"]) || !isset($_GET["humo"]) || !isset($_GET["key"]))
{
exit("nope");
}

if($_GET["key"] != "secretKey") {
	exit("nope");
}

$data["date"] = date('d-m-Y H:i');
$data["tempi"] = $_GET["tempi"];
$data["tempo"] = $_GET["tempo"];
$data["humo"] = $_GET["humo"];



$fp = fopen('/var/www/phib.io/weather/temps.json', 'a');
fwrite($fp, json_encode($data).",");
fclose($fp);
?>
