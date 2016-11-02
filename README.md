# WeatherStation
Arduino powered weather station with 3D-Printed enclosure.
Arduino reads temperatures and humidity and sends it over http to a php-script which simply saves the values into a .json file.
A seperate webview displays the data with a graph.

## Hardware
- Arduino Uno + Ethernet Shield
- DS18F20 sensor for indoor temp
- Adafruit HTU21D-F for outdoor temp and humidity

## Code
- Server: The php script which gets the data from the arduino and saves it into json
  - you need to set a secretKey here which is used for "authentication"
- arduino: The arduino firmware which reads temps and sends them via http to the server
  - the http-request also needs the secretKey
- WebView: small web page to show a graph and current temps

## Enclosure
http://www.thingiverse.com/thing:1067700
Printed in ABS and coated with epoxy resign to make it more durable outside.
