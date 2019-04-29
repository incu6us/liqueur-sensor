
#include <Arduino.h>

#define CE_PIN 3
#define CSN_PIN 3 //Since we are using 3 pin configuration we will use same pin for both CE and CSN

#include "RF24.h"

RF24 radio(CE_PIN, CSN_PIN);

byte address[11] = "SimpleNode";
unsigned long payload = 0;

void setup()
{
  radio.begin();                  // Start up the radio
  radio.setAutoAck(1);            // Ensure autoACK is enabled
  radio.setRetries(15, 15);       // Max delay between retries & number of retries
  radio.openWritingPipe(address); // Write to device address 'SimpleNode'

  // initialize pin 4 (ATtiny leg 3) as an output.
  pinMode(4, OUTPUT);
}

void loop()
{
  int X = analogRead(3);
  if (X < 614)
  {
    digitalWrite(4, HIGH);
    delay(200);
    digitalWrite(4, LOW);
  }
  else
  {
    digitalWrite(4, HIGH);
  }

  radio.write(&X, sizeof(unsigned long));
  delay(200);
}