// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Wire.begin(0x56);                // join i2c bus with address #2
  Wire.onRequest(requestEvent); 
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}
void loop()
{
  delay(100);
  }

// function that executes whenever data is requested by master
void requestEvent()
{
  Wire.write("helloWorld"); // respond with message of 6 bytes
  // as expected by master
}
void receiveEvent(int howMany)
{
  unsigned int i;
  Serial.print("Receive number:");
  Serial.print(howMany);
  Serial.print(' ');
  for(i=0;i<howMany;i++)
   { 
     Serial.print(Wire.read());         // print the character 
     Serial.print(' ');
   }
   Serial.print('\n');
} // register event

