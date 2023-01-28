#include "Adafruit_MCP23017.h"
#include "ESP8266WiFi.h"
#include "ESPAsyncTCP.h" 
#include "ESPAsyncWebServer.h"

const char* ssid = "Getraenkeautomat";
const char* password = "12345678";

IPAddress local_IP(192, 168, 43, 221);
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);

#define MCP23017_ADDR 0x20
#define INPUT_PIN 14
#define INPUT_PIN 12

AsyncWebServer server(80);
Adafruit_MCP23017 MCP;

int drink =-1;
int Schaechte;

bool S0;
bool S1;
bool S2;
bool S3;
bool S4;
bool S5;

void setup() {

Serial.begin (115200);
MCP.begin (); 

if (!WiFi.config(local_IP, gateway, subnet )) {
Serial.println("STA Failed to configure");
}
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println("Connecting to WiFi..");
};
Serial.println("Verbunden!");

//Schacht0
MCP. pinMode (0, OUTPUT);
MCP. pinMode (8, INPUT);
MCP. pullUp (8, HIGH);

//Schacht1
MCP. pinMode (1, OUTPUT);
MCP. pinMode (9, INPUT);
MCP. pullUp (9, HIGH);

//Schacht2
MCP. pinMode (2, OUTPUT);
MCP. pinMode (10, INPUT);
MCP. pullUp (10, HIGH);

//Schacht3
MCP. pinMode (3, OUTPUT);
MCP. pinMode (11, INPUT);
MCP. pullUp (11, HIGH);

//Schacht4
MCP. pinMode (4, OUTPUT);
MCP. pinMode (12, INPUT);
MCP. pullUp (12, HIGH);

//Schacht5
MCP. pinMode (5, OUTPUT);
MCP. pinMode (13, INPUT);
MCP. pullUp (13, HIGH);


//Schacht0
MCP. pinMode (6, INPUT);
MCP. pullUp (6, HIGH);

//Schacht1
MCP. pinMode (7, INPUT);
MCP. pullUp (7, HIGH);

//Schacht2
MCP. pinMode (14, INPUT);
MCP. pullUp (14, HIGH);

//Schacht3
MCP. pinMode (15, INPUT);
MCP. pullUp (15, HIGH);

pinMode(12, INPUT_PULLUP);

pinMode(14, INPUT_PULLUP);

server.on("/drink", HTTP_GET, [](AsyncWebServerRequest *request){
AsyncWebParameter* p = request->getParam(0);
String s=p->value();
drink=s.toInt();
request->send(200, "text/plain", "OK!" );
});

server.on("/emptyschacht", HTTP_GET, [](AsyncWebServerRequest *request){
request->send(200, "text/plain",  (String(S0) + ";" + (S1) + ";" + (S2) + ";" + (S3) + ";" + (S4) + ";" + (S5) + ";"));
});
server.begin();
}

void loop() {

//Schacht0
if (drink==0)
{
MakeDrink(0,8); 
}
//Schacht1
else if(drink==1)
{
  MakeDrink(1,9);
}
//Schacht2
else if(drink==2)
{
  MakeDrink(2,10);
}
//Schacht3
else if(drink==3)
{
  MakeDrink(3,11);
}
//Schacht4
else if(drink==4)
{
  MakeDrink(4,12);
}
//Schacht5
else if(drink==5)
{
  MakeDrink(5,13);
}


if(drink!=-1)
{
  drink=-1;
}

if (MCP .digitalRead(6)==HIGH)
{
  Serial.println("Schacht0 ist Leer");
 S0 = true;
}

if (MCP .digitalRead(7)==HIGH)
{
  Serial.println("Schacht1 ist Leer");
  S1 = true;
}

if (MCP .digitalRead(14)==HIGH)
{
  Serial.println("Schacht2 ist Leer");
  S2 = true;
}

if (MCP .digitalRead(15)==HIGH) 
{
  Serial.println("Schacht3 ist Leer");
  S3 = true;
}

if (digitalRead(14)==HIGH) 
{
  Serial.println("Schacht4 ist Leer");
  S4 = true;
}

if (digitalRead(12)==HIGH) 
{
  Serial.println("Schacht5 ist Leer");
  S5 = true;
}

  
if (MCP .digitalRead(6)==LOW)
{
 S0 = false;
}

if (MCP .digitalRead(7)==LOW)
{
    S1 = false;
  }
  
if (MCP .digitalRead(14)==LOW)
{
  S2 = false;
  }


if (MCP .digitalRead(15)==LOW) 
{
    S3 = false;
  }

  if (digitalRead(14)==LOW) 
{
   S4 = false;
  }

  
    if (digitalRead(12)==LOW) 
{
  S5 = false;
  }


}
void MakeDrink(int outputNR, int inputNR)
{

Serial.println("MOTOR START");
MCP. digitalWrite(outputNR,HIGH);

//ansonsten instant stop!
delay(700);

//solange endschalter NICHT erreicht!!!
while(MCP .digitalRead(inputNR)==HIGH)
{
  delay(10);
   Serial.println("WAIT TILL LOW");
}


MCP .digitalRead(6)==HIGH;;
//wenn hier dann motor stellung erreicht
MCP. digitalWrite(outputNR,LOW);
}




  
