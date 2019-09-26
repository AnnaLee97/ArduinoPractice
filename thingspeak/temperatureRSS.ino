/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>

const char* ssid     = "myiptime";
const char* password = "00000000";

const char* host = "www.kma.go.kr";
const String api = "/update?api_key=GZCICZN529CQ81KR&field1=";
String arr[9];

void setup()
{
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    // We now create a URI for the request
    String url = "/wid/queryDFSRSS.jsp?zone=1168061000";

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String str = client.readStringUntil('\n');
        if(str.indexOf("<temp>") >= 0){
          arr[i] = str.substring(str.indexOf("<temp>")+6, str.lastIndexOf("</temp>"));
          i++;
        }
    }
     Serial.println();
       
}

int j=0;
void loop()
{
    delay(5000); 
    if(j<9){
    WiFiClient client;
    if (!client.connect("api.thingspeak.com", 80)) {
        Serial.println("connection failed");
        return;
        }
      
        String url = api+arr[j];
        client.println("GET "+ url +" HTTP/1.1\r\n" +
                   "Host: " + "api.thingspeak.com" + "\r\n"+
                   "Connection: close\r\n\r\n");
        j++;
        delay(5000);
     }
}
