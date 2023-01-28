#include "Adafruit_MCP23017.h"
#include "ESP8266WiFi.h"
#include "ESPAsyncTCP.h" 
#include "ESPAsyncWebServer.h"

const char* ssid = "Getraenkeautomat";
const char* password = "12345678";

IPAddress local_IP(192, 168, 43, 221);
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);



AsyncWebServer server(80);

int drink =-1;
int Schaechte;


void setup() {
pinMode(0, OUTPUT);

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


pinMode(16, OUTPUT);
pinMode(5, OUTPUT);
pinMode(4, OUTPUT);

pinMode(14, INPUT);
pinMode(12, INPUT);
pinMode(13, INPUT);
pinMode(3, INPUT);




server.on("/drink", HTTP_GET, [](AsyncWebServerRequest *request){
AsyncWebParameter* p = request->getParam(0);
String s=p->value();
drink=s.toInt();
request->send(200, "text/plain", "OK!" );
});


server.begin();
}

void loop() {

//Schacht0
if (drink==0)
{
MakeDrink(16,14); 
}
//Schacht1
else if(drink==1)
{
  MakeDrink(5,12);
}
//Schacht2
else if(drink==2)
{
  MakeDrink(4,13);
}
//Schacht3
else if(drink==3)
{
  MakeDrink(0,3);
}



if(drink!=-1)
{
  drink=-1;
}



}
void MakeDrink(int outputNR, int inputNR)
{

Serial.println("MOTOR START");
digitalWrite(outputNR, HIGH);

//ansonsten instant stop!
delay(700);

while(digitalRead(inputNR)==HIGH)
{
delay(10);
}




digitalWrite(outputNR, LOW);

}




  
