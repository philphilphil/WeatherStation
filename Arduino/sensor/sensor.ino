#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>

//Ethernet shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "bckp.de";
IPAddress ip(192, 168, 0, 177);
EthernetClient client;

//Sensor 1 - indoor temp
int sensorPin = 2;
OneWire ds(sensorPin);

//sensor 2 - outdor temp/hum

void setup(void) {
  Serial.println("setup...");
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
}

void loop(void) {
  float temperature = getTemp();
  //Serial.println(temperature);
  String strTemp =  String(temperature, 0);


if (client.connect(server, 80)) {
    //Serial.println("sending request to server");
    // Make a HTTP request:
    client.println("GET /weather/index.php?temp=" + strTemp + "&key=secretKey HTTP/1.1");
    client.println("Host: bckp.de");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
  client.stop();

  delay(60000); //every 1 minute

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
