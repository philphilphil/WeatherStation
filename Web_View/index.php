<html>
<head>
<title>Weather - Fellbach, Germany</title>
<link rel="stylesheet" href="lib/spectre.min.css" />
<link rel="stylesheet" href="lib/chartist.min.css">
</head>
<body>
<script src="lib/chartist.min.js"></script>
<?php

$str = file_get_contents('/var/www/phib.io/weather/temps.json');
#Add [ ] and remove last , for valid json
$strFixed = "[".substr($str,0, -1)."]";
$json = json_decode($strFixed, true);

#print_r(json_encode(array_column($json, 'date')));
#print_r(json_encode(array_column($json, 'temp')));
?>

<center>
<table border="0">
        <tr>
                <td style="padding-right: 30px"><h1>Indoor: <?php echo($json[count($json)-1]["tempi"]); ?>C&deg;</h1><h6>measured at <?php echo($json[count($json)-1]["date"]); ?></h6></td>
                <td style="padding-left: 30px"><h1>Outdoor: <?php echo($json[count($json)-1]["tempo"]);  ?>C&deg;</h1><h6>Humidity: <?php echo($json[count($json)-1]["humo"]);  ?>%</h6></td>
        </tr>
</table>

<h4><b>Last 24h</b></h4>
<div class="ct-chart ct-perfect-fourth" style="height: 510px; margin: auto; width: 50%">
<script type="text/javascript">
        var data = {
        labels: <?php print_r(json_encode(array_column($json, 'date'))); ?>,
        series: [
                        <?php print_r(json_encode(array_column($json, 'tempo'))); ?>,
                        <?php print_r(json_encode(array_column($json, 'tempi'))); ?>

                        ]
        };

        var options = {
                width: 900,
                height: 500
                };
new Chartist.Line('.ct-chart', data, options);</script></div>
<h6>Arduino-powered Weather station with 3D-printed enclosure - Code on <a href='https://github.com/philphilphil/WeatherStation'>GitHub</a> - <a href='https://phib.io'>phib.io</a></h6>
</center>
</body>
</html>