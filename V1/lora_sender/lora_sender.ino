/*********
  Modified from the examples of the Arduino LoRa library
  More resources: https://randomnerdtutorials.com
*********/

#include <SPI.h>
#include <LoRa.h>

const int csPin = 2;          // LoRa radio chip select
const int resetPin = 16;       // LoRa radio reset
const int irqPin = 15;         // change for your board; must be a hardware interrupt pin


int counter = 0;
int led = 0;

void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Sender");

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  delay(20);
  digitalWrite(2, HIGH);
  
  //setup LoRa transceiver module
  LoRa.setPins(csPin, resetPin, irqPin);

  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(868E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSpreadingFactor(12);
  //LoRa.setSignalBandwidth(62.5E3);
  
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  digitalWrite(2, LOW);
  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  while(LoRa.isTransmitting()) { yield(); }

  digitalWrite(2, HIGH);

  led++;
  counter++;
  delay(2000);
}
