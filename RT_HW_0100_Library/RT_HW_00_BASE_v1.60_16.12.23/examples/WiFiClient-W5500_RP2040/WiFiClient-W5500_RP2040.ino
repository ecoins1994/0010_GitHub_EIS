/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <W5500lwIP.h>

const char* host = "djxmmx.net";
const uint16_t port = 17;

Wiznet5500lwIP eth(1 /* chip select */);
uint8_t dir=0;
unsigned long timeout;
//=====================================================================================
void setup() {
  // Set up SPI pinout to match your HW
  SPI.setRX(16);
  SPI.setCS(17);
  SPI.setSCK(18);
  SPI.setTX(19);
//  SPI.setRX(0);
//  SPI.setCS(1);
//  SPI.setSCK(2);
//  SPI.setTX(3);

  Serial.begin(115200);
  delay(5000);
  Serial.println();
  Serial.println();
  Serial.println("Starting Ethernet port");
}
//==========================================================================================
void loop() {
            WiFiClient client;
  static bool wait = false;
//------------------------------------------------------------------------------------------
if(dir==0){Serial.println("Init W5500"); dir=1;}
if(dir==1){if (!eth.begin()) {Serial.println("No wired Ethernet hardware detected. Check pinouts, wiring."); delay(500);}
           else              {dir=2;}}
if(dir==2){if(!eth.connected()) {Serial.print("."); delay(500);}
           dir=3;}
if(dir==3){Serial.print("connecting to ");
           Serial.print(host);
           Serial.print(':');
           Serial.println(port);
            // Use WiFiClient class to create TCP connections

           dir=4;}
if(dir==4){if (!client.connect(host, port)) {Serial.println("connection failed"); delay(1000);} //delay(5000);
           dir=5;}
if(dir==5){Serial.println("sending data to server");
           timeout = millis();
           if (client.connected()) {client.println("hello from RP2040"); dir=6;}
           else                    {delay(500);}}
if(dir==6){while (client.available() == 0) {
           if (millis() - timeout > 5000) {
           Serial.println(">>> Client Timeout !");
            client.stop();
           delay(1000); dir=0;}
           dir=7;}}
if(dir==7){
  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }
  dir=8;}
if(dir==8){Serial.println(); Serial.println("closing connection");
           client.stop();
          if (wait) {delay(300000);}  // execute once every 5 minutes, don't flood remote service
           wait = true;
           dir=0;}
}
