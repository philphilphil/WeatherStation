#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>
#include <Wire.h>
#include "Adafruit_HTU21DF.h"

//Ethernet shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "bckp.de";
IPAddress ip(192, 168, 0, 177);
EthernetClient client;

//Sensor 1 - indoor temp
int sensorPin = 2;
OneWire ds(sensorPin);

//sensor 2 - outdor temp/hum
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

void setup(void) {
  Serial.println("setup...");
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect . Needed for native USB port only
  }

  if (!htu.begin()) {
    Serial.println("Couldn't find HTU21DF-sensor!");
    while (1);
  }

  Ethernet.begin(mac);
  delay(1000);
}

void loop(void) {
  float tempInside = getTemp();
  float tempOutside = htu.readTemperature();
  float humOutside = htu.readHumidity();

  //Serial.println(tempOutside);
  String strTempi =  String(tempInside, 0);
  String strTempo =  String(tempOutside, 0);
  String strHum =  String(humOutside, 0);

  //remove leading and ending white spaces 
  strTempo.trim();
  strHum.trim();
  strTempi.trim();
  
  if (client.connect(server, 80)) {
    Serial.println("sending request to server");
    client.println("GET /weather/index.php?tempi=" + strTempi + "&tempo=" + strTempo + "&humo=" + strHum + "&key=secretKey HTTP/1.1");
    client.println("Host: bckp.de");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("connection failed");
  }

  client.stop();

  delay(60000*5); //every 5 minutes
}


float getTemp() {
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
    //no more sensors on chain, reset search
    ds.reset_search();
    return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
    Serial.print("Device is not recognized");
    return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad


  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;

}
