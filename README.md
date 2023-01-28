# Compilation

You need ArduinoIDE and all necessary libaries:
- AsyncWebServer server
- Adafruit_MCP23017 
- OneWire
- DallasTemperature




# Workflow

All ESPs will wait till theres a available WLAN (you can configure it SSID & Password). You can easily create a Hotspot or something similar with a Tablet/Smartphone.
When there's a the controllers are in operation mode and gets a fixed IP. So make sure your client is the same subnet like them. (You can also change the IP and Subnet)


# IPS
Climate	192.168.43.220/24
Controll	192.168.43.221/24


# Endpoints GET

To activate the motor and getting a drink use:
## http://192.168.43.221/drink?id=X
id: Integer, 0-3(or 7)


To get current temperature:

## http://192.168.43.222/temp
Returns the temperature in °C with 2 decimals.
