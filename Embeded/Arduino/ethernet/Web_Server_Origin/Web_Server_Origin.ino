
#include <SPI.h> // needed in Arduino 0019 or later
#include <Ethernet.h>

// Ethernet Shield Settings
byte mac[] = { 0xE8, 0xE0, 0xB7, 0x9A, 0x73, 0x30 };

// If you don't specify the IP address, DHCP is used(only in Arduino 1.0 or later).
byte ip[] = { 192, 168, 0, 117 };
byte gtw[] = { 106, 159, 53, 159 };
byte sbm[] = { 255, 255, 255, 0};
  float sensorReading;
EthernetServer server(80);


void server_con(void);

void setup()
{
  delay(1000);

  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();

  Serial.println("connecting ...");
  Serial.println("server is at ");
  Serial.println(Ethernet.localIP());
}
void loop()
{
  sensorReading = (((analogRead(0) * 5040) / 1024.0)-400)/19.5;
    server_con();
}

void server_con(void)
{
  EthernetClient client= server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
            client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println("<!DOCTYPE HTML>");
          client.println();
          client.println("<html>");
            client.println("<head>");
              client.println("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">");
              client.println("<meta name=viewport content=\"width=80px, initial-scale=4, maximum-scale=4, user-scalable=no\"/>");
              client.println("<title>エヴァオタのホームページ</title>");
            client.println("<head>");
            client.print("<body>");
              client.print("<center><h1>若林家の室温</h1></center>");
              //client.print("<marquee>");
              client.print("<img width=50% heigth=50% src=");
              client.print("\"https://lh3.googleusercontent.com/-spKG08kO6FI/VVhscGh6l4I/AAAAAAAAC-w/LIB6R5zqACc/s640/2015_05_17_19_24_46.jpg\"");
              client.print(">");
              client.print("<font color=\"green\">←このArduinoをサーバーに使用しています。");
              client.print("<br /><font color=\"blue\">");
              client.print("現在の部屋の気温は、");
              client.print("<font size=\"40\" color=\"red\">");
              client.print(sensorReading);
              client.print("</font>");
              client.print("度です。\n");
              client.print("</font><br />");
              //client.print("</marquee>");
              client.print("<a href=\"http://www.yahoo.co.jp/\"> Yahooジャポン</a>");
            client.print("<body>");
          client.println("<br />");
          client.println("</html>");  

          break;
        }
        if (c == '\n') {
          
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
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


