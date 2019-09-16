#include <ESP8266WiFi.h>


const char* ssid = "****"; // ******* is your wifi SSID name
const char* pass = "*******";//********* is your wifi password
 
const char* host = "api.thingsio.ai";
const char* post_url = "/devices/deviceData"; 
const char* time_server = "baas.thethingscloud.com"; 
const int httpPort = 80;
char timestamp[10];
int count=0,i,m,j,k;
int humdity;
int outputpin= A0; 


WiFiClient client;
int GiveMeTimestamp()
{
  unsigned long timeout = millis();

  while (client.available() == 0)
  {
    if (millis() - timeout > 50000)
    {
      client.stop();
      return 0;
    }
  }

while (client.available())
      {
        String line = client.readStringUntil('\r');                    //indexOf() is a funtion to search for smthng , it returns -1 if not found
        int pos = line.indexOf("\"timestamp\"");                       //search for "\"timestamp\"" from beginning of response got and copy all data after that , it'll be your timestamp
        if (pos >= 0)                                                     
        {
          int j = 0;
          for(j=0;j<10;j++)
          {
            timestamp[j] = line[pos + 12 + j];
          }
        }
      }
}  
 
void setup() {
 
  Serial.begin(115200);
  WiFi.disconnect();
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid,pass );
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}
 
void loop() {
  
  int analogValue = analogRead(outputpin);
  
{
 
  
/////////////////////////////////////// SEND THE QUERY AND RECEIVE THE RESPONSE///////////////////////  

        humidity = analogValue;
        humidity = map(humidity,750,180,0,100);
        Serial.print("humidity (analog): ");
        Serial.print(humidity);
        Serial.print("%\n");
        
                

  Serial.print("connecting to ");
  Serial.println(host);                          //defined upside :- host = devapi2.thethingscloud.com or 139.59.26.117

///////////////////////////////////// TIMESTAMP CODE SNIPPET /////////////////////////
Serial.println("inside get timestamp\n");
  if (!client.connect(time_server, httpPort)) 
  {
    return;                                                        //*-*-*-*-*-*-*-*-*-*
  }

  client.println("GET /api/timestamp HTTP/1.1");                            //Whats this part doing, i didnt get
  client.println("Host: baas.thethingscloud.com");
  client.println("Cache-Control: no-cache");
  client.println("Postman-Token: ea3c18c6-09ba-d049-ccf3-369a22a284b8");
  client.println();

GiveMeTimestamp();                        //it'll call the function which will get the timestamp response from the server
Serial.println("timestamp receieved");
Serial.println(timestamp);
///////////////////////////////////////////////////////////////////////////////

// Use WiFiClient class to create TCP connections
  if (!client.connect(host, httpPort))            //host = devapi2.thethingscloud.com , port = 80
  {
    Serial.println("connection failed");                  // *-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-
    return;
  }
  
  client.print("Content-Length: ");
  client.println(); 

  unsigned long timeout = millis();
  while (client.available() == 0) 
  {
    if (millis() - timeout > 50000) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  Serial.println("***********************************************");
  Serial.println();
  Serial.println("closing connection");

  Serial.println("inside ThingsCloudPost");

 
  String PostValue = "{\"device_id\": 6111998 , \"slave_id\": 2";
         PostValue = PostValue + ",\"dts\":" +timestamp;
   PostValue = PostValue +",\"data\":{\"moisture%\":" + h1 +"}"+"}";
  
  
  Serial.println(PostValue);

//////////////////////////////// try to connect to server again and POST the data on the cloud //////////////////////////
  if (!client.connect(host, httpPort)) 
  {
    return;
  }

  client.print("POST ");
  client.print(post_url);               /// POST api/device-datas         HTTP/1.1     Host: baas.thethingscloud.com      Content-Type: application/json        Cache-Control: no-cache
  client.println(" HTTP/1.1");           //Authorization:          Content-Length: 
  client.print("Host: ");
  client.println(host);
  client.println("Content-Type: application/json");
  client.println("Cache-Control: no-cache");
  client.print("Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.IjViZTk1NzRiNDAyYjlkNGI5MDdiZjgwNyI.Ao71P5YERN9E66J7KJHRR5FczsJIHhmv44X7w9QoKCI");
  client.println();
  client.print("Content-Length: ");
  client.println(PostValue.length());
  client.println();
  client.println(PostValue);
 
//////////////////////////////////POSTING the data on to the cloud is done and now get the response form cloud server//////////////////
  while (client.available() == 0) 
  {
    if (millis() - timeout > 50000) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  Serial.println("Response From Server");
  while(client.available())
  { 
    String line2 = client.readStringUntil('\r');   
    Serial.print(line2);
    
  }
    
Serial.println("//////////////////////    THE END     /////////////////////");
delay(3000);
}
}
