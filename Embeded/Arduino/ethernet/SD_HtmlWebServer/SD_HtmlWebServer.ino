
/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 */

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

#define Filename "client.txt"

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xE8, 0xE0, 0xB7, 0x9A, 0x73, 0x30 };
byte ip[] = {192, 168, 0, 177};
char msg[500];
File SDfile;

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() 
{
  SerialInit();
  SDInit();
  SDreading(msg);
  //EthernetInit();
}

void loop() 
{
  // listen for incoming clients
  EthernetClient client = server.available();

  if (client) 
  {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) 
        {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println(msg);
         for(int i = 0;i<500;i++)
           Serial.write(msg[i]);
          break;
        }
        if (c == '\n')
        {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
void SerialInit(void)
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial);    
}
void EthernetInit(void)
{
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}
void SDInit(void)
{
  pinMode(10,OUTPUT);
  
  if(!SD.begin(4))
  {
    Serial.println("SD was not Initialized");
  }
  else
  {
    Serial.println("SD was Initialized");   
  }
  if(SD.exists(Filename))
  {
    Serial.println("File found");
  }
  else
  {
    Serial.println("File not found");   
  }
}
void SDreading(char *msg)
{
  unsigned int count=0;
 
  SDfile = SD.open(Filename);
  
  if(SDfile)
  {
    while(SDfile.available())
    {
      char c = SDfile.read();
      Serial.write(c);
      msg[count] = c;
      count++;  
    }
  SDfile.close();
  }
  for(int i = 0;i<500;i++)
           Serial.write(msg[i]);
         
}
