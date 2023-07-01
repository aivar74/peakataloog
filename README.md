# Temperature Sensor AT HOME
This project uses 4 ( unlimited number) temperature sensors in my apartment. all data is upluaded regularly 
to HTML pages. 
every Sensor has unique IP adress. 
also is at home 1 OLED 0,96"" Screen where all 4 temperature are displayed
Every i2C temperature sensor is using ESP8266 MINI board. 
Adress EXAMPLE: 
http://192.168.0.41/
http://192.168.0.42/
http://192.168.0.43/
http://192.168.0.44/

Every i2C ESP9266 is refreshing and available data on local wifi HTML pages 
ESP32 is connected to 1 OLED screen 0,96""
ESP32 is refreshing data reading from four different IP adress wich are about ESP8266 Sensors

