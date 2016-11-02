# WeatherStation
Arduino powered weather station with 3D-Printed enclosure

## Hardware
- Arduino Uno + Ethernet Shield
- DS18F20 sensor for indoor temp
- Adafruit HTU21D-F for outdoor temp and humidity

## Code
- Server: The php script which gets the data from the arduino and saves it into json
- arduino: The arduino firmware which reads temps and sends them via http to the server
- WebView: small web page to show a graph and current temps

## Enclosure
http://www.thingiverse.com/thing:1067700
Printed in ABS and coated with epoxy resign to make it more durable outside.
