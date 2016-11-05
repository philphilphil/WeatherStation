# WeatherStation
Arduino powered weather station with 3D-Printed enclosure.
Arduino reads temperatures and humidity and sends it over http to a php-script which simply saves the values into a .json file.
A seperate webview displays the data with a graph.

My measurements: https://weather.phib.io/

## Hardware
- Arduino Uno + Ethernet Shield
- DS18F20 sensor for indoor temp
- Adafruit HTU21D-F for outdoor temp and humidity

## Code
- Server: The php script which gets the data from the arduino and saves it into json
  - you need to set a secretKey here which is used for "authentication"
  - because arduino can't do SSL, the request is unencrypted, so if someone sniffes your key in your local network he could send false temperatures
- arduino: The arduino firmware which reads temps and sends them via http to the server
  - the http-request also needs the secretKey
- WebView: small web page to show a graph and current temps

## Enclosure
http://www.thingiverse.com/thing:1067700
Printed in ABS and coated with epoxy resign to make it more durable outside.
