#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266WebServerSecureAxTLS.h>
#include <ESP8266WebServerSecureBearSSL.h>
#include <DHT.h>

#define DHT_PIN_DATA D7

DHT dht(DHT_PIN_DATA);

const char* ssid = "Excitel251-2.4G";
const char* password = "12345678";
int sense_Pin = 0;
 
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
  dht.begin();
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("...............");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  int size=100;
  String data,data1,data2;

  /*
  data=moisture
  data1=temperature
  data2=humidity
  */
  if (request.indexOf("/get-data") != -1)  {
    while(size--){
      data+= analogRead(sense_Pin)+' ';
      data+=',';

      data1+= dht.readTempC()+' ';
      data1+=',';

      data2+= dht.readHumidity()+' ';
      data2+=',';
    }
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html><p>");
  client.print(data);
  client.print("<br><br>");
  client.print(data1);
  client.print("<br><br>");
  client.print(data2);
  client.println("</p></html>");
 
  delay(1);
  Serial.println("Client disonnected");
}