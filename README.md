Temperature and Humidity Data Logger using an ESP8266 chip and DHT22.
Doesn't rely on something reading the serial to send data.

Components used:
* ESP8266 ESP-01S WIFI Module
* DHT22 Humidity & Temperature Sensor
* 100uF capacitor

Wiring:
* Red = VCC
* Black = GND
* Green = CH_PD
* Orange = RX
* Yellow = TX
* Gray = GPIO_2
* Blue = GPIO_0
* White = RST

RST to GND if you want to reset the board.
GPIO_0 to GND to start it into bootloader mode.
GPIO_2 can be interchanged with the GPIO_0's place in the DHT22 data line.
![layout](./resources/Logger_bb.svg)

First flash the ESP8266 chip by connecting everything and starting it in boot mode. Use esptool.py to flash it with Micropython firmware, then load up boot.py and main.py onto the chip using WebREPL.