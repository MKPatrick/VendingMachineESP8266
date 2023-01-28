#include "ESP8266WiFi.h"
#include "ESPAsyncTCP.h" 
#include "ESPAsyncWebServer.h"

const char* ssid = "Getraenkeautomat";
const char* password = "12345678";

IPAddress local_IP(192, 168, 43, 222);
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);

#include <OneWire.h>
#include <DallasTemperature.h>

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;     

AsyncWebServer server(80);

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
float temp=0.0;
void setup() {
  // Start the DS18B20 sensor
  sensors.begin();
  pinMode(5, OUTPUT);
Serial.begin (115200);


if (!WiFi.config(local_IP, gateway, subnet )) {
Serial.println("STA Failed to configure");
}
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println("Connecting to WiFi..");
};
Serial.println("Verbunden!");


server.on("/temp", HTTP_GET, [](AsyncWebServerRequest *request){
AsyncWebParameter* p = request->getParam(0);

request->send(200, "text/plain", String(temp) );
});


server.begin();
}
float offset=0;
void loop() {

 sensors.requestTemperatures(); 
  temp = sensors.getTempCByIndex(0);
  Serial.print(temp);

delay(4000);

if(temp+offset<10)
{
  digitalWrite(5, LOW);
  offset=-1;
}
else
{
  digitalWrite(5, HIGH);
  offset=0;

}
}





  
