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
$json = json_decode($str, true);


#print_r(json_encode(array_column($json, 'date')));
#print_r(json_encode(array_column($json, 'temp')));
?>

<center>
<table cellpadding="50" border="0">
	<tr>
		<td><h1>Indoor: <?php echo($json[count($json)-1]["temp"]); ?>C&deg;</h1><h6>measured at <?php echo($json[count($json)-1]["date"]); ?></h6></td>
		<td><h1>Outdoor: <?php echo($json[count($json)-1]["temp"]); ?>C&deg;</h1><h6>measured at <?php echo($json[count($json)-1]["date"]); ?></h6></td>
	</tr>
</table>

<div class="ct-chart ct-perfect-fourth" style="height: 510px; margin: auto; width: 50%">
<h4><b>Last 24h, measured every 30 min</b></h4>
<script type="text/javascript">
	var data = {
  	labels: <?php print_r(json_encode(array_column($json, 'date'))); ?>,
  	series: [
			<?php print_r(json_encode(array_column($json, 'temp'))); ?>,
    		[11, 13, 21, 31, 10, 13, 11]
  			]
	};

	var options = {
  		width: 900,
  		height: 500
		};
new Chartist.Line('.ct-chart', data, options);</script></div>
<h6>Arduino-powered Weather station with 3D-printed enclosure - Code on <a href='https://github.com/philphilphil/WeatherStation'>GitHub</a> - Blogpost about the hardware inc.</h6>
</center>
</body>
</html>
