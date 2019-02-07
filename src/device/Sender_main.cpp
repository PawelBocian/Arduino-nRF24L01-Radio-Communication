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
  network.begin(CHANNEL,UNO_NODE);            // Open connection at 45-th channel adress : UNO_NODE -> 01
  Serial.println(F("Sender activated"));
}

void sendMessage(Message message){
  bool allRight = network.write(mini_header,&message,sizeof(message));   //Sending "req" message to SLAVE ( Arduino MINI PRO )
  if(allRight){
    Serial.println(F("Sending successful"));                  // Prints if message was send correctly
  }
  else
  {
    Serial.println(F("Sending failed"));                // Prints if message wasn't send correctly
  }
}

void loop() {

  message.setValue(millis());               // Set message value at current millis()
  sendMessage(message);                     // Send message to other device
  delay(2000);                              // Freeze for 2s (avoid too much messages)

}
