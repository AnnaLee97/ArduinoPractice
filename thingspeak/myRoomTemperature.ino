/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com  
*********/


#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>


// Data wire is connected to GPIO 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// Replace with your network credentials
const char* ssid = "myiptime";
const char* password = "00000000";
const String api = "/update?api_key=92Z8J256C052XR8W&field1=";

String readDSTemperatureC() {
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  float tempC = sensors.getTempCByIndex(0);

  if(tempC == -127.00) {
    Serial.println("Failed to read from DS18B20 sensor");
    return "--";
  } else {
    Serial.print("Temperature Celsius: ");
    Serial.println(tempC); 
  }
  return String(tempC);
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();

  
  // Start up the DS18B20 library
  sensors.begin();
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(); 
}
const char* host = "api.thingspeak.com";
const int httpPort = 80;

void loop(){
  delay(5000);
  WiFiClient client;
  String url = api+readDSTemperatureC();
  //char __url[sizeof(url)];
  //url.toCharArray(__url, sizeof(__url));
  
  if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }
    
  client.println("GET "+ url +" HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    
}
