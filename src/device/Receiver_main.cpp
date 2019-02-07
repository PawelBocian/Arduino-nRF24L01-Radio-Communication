#include <Arduino.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
                                              // Include all files
#include "message/Message.h"
#include "utils/Attributes.h"


RF24 radio(7,8);                              // Radio attached at board pin 7 and 8
RF24Network network(radio);                   // Network uses that radio

Message message;                              // Object represents message send via nRF24L01+ module

RF24NetworkHeader uno_header(UNO_NODE);       // Headers to radio communication between Master-Slave
RF24NetworkHeader mini_header(MINI_NODE);


void setup() {

  Serial.begin(115200);                       // Open serial monitor
  SPI.begin();                                // Allows you to communicate with SPI devices, with the Arduino as the master device.
  radio.begin();                              // Radio device begin
  network.begin(CHANNEL,MINI_NODE);            // Open connection at 45-th channel adress : UNO_NODE -> 01
  Serial.println(F("Receiver activated"));
}

void readMessage(){
  if(network.available()){
    int allRight = network.read(mini_header,&message,sizeof(message));   // Reading message
    if(allRight){
      Serial.print(F("Message received :"));
      Serial.println(message.getValue());
    }
  }
}

void loop() {

  network.update();                  // updates network regularry
  readMessage();                     // Send message to other device


}
