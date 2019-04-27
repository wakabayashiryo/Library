#include <SPI.h> // needed in Arduino 0019 or later
#include <Ethernet.h>
#include <Twitter.h>
#include<stdio.h>

// The includion of EthernetDNS is not needed in Arduino IDE 1.0 or later.
// Please uncomment below in Arduino IDE 0022 or earlier.
//#include <EthernetDNS.h>


// Ethernet Shield Settings
byte mac[] = { 0xE8, 0xE0, 0xB7, 0x9A, 0x73, 0x30 };

// If you don't specify the IP address, DHCP is used(only in Arduino 1.0 or later).
byte ip[] = { 192, 168, 0, 117 };

// Your Token to Tweet (get it from http://arduino-tweet.appspot.com/)
Twitter twitter("582799724-YmrYm5s9VnGhY5G7vqzJfTR3XrLBUvVH2ClHtFdu");

// Message to post
char msg[] = "Hello, World! I'm Arduino!";
String strMsg;
char msg[100];
void setup()
{
  delay(1000);
  Ethernet.begin(mac, ip);
  // or you can use DHCP for autoomatic IP address configuration.
  // Ethernet.begin(mac);
  Serial.begin(9600);
  
  Serial.println("connecting ...");
  if (twitter.post(msg)) {
    // Specify &Serial to output received response to Serial.
    // If no output is required, you can just omit the argument, e.g.
    // int status = twitter.wait();
    int status = twitter.wait(&Serial);
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("connection failed.");
  }
}

void loop()
{
}
void twi(void)
{
  float temp = 0, data;
  for (unsigned int samp = 0; samp < 1000; samp++)
  {
    int sensorValue = analogRead(A0);
    float voltage = sensorValue * (4.65 / 1023.0);
    data = (voltage - 0.4) / 0.0195;
    temp += data;
  }

  strMsg = "現在の部屋の気温は、";
  strMsg += temp / 1000;
  strMsg += "度です。\n";
  strMsg += "電源をつけてから、";
  strMsg += count;
  strMsg += "回目の送信です。";
  sprintf(msg, "%s", strMsg.c_str());
  twi_send(); count++;
  
}
void twi_send(void)
{
  flag =  twitter.post(msg);
  if (flag)
  {
    // Specify &Serial to output received response to Serial.
    // If no output is required, you can just omit the argument, e.g.
    // int status = twitter.wait();
    int status = twitter.wait(&Serial);
    if (status == 200)
    {
      Serial.println("OK.");
    }
    else
    {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  }
  else
  {
    Serial.println("connection failed.");
  }


}
