# BlynkGPSTracker

What you'll need on the hardware side:

* ESP32 (any should work, testing on Adafruit Huzzah32)
* Any TinyGSM library supported modem *WITH GPS*

I cannot recommend the ESP8266 due to limited serial. AT commands may not go through correctly.

What you'll need on the software side:

* Blynk (library version 0.6.1)
* TinyGSM (library version 0.10.5)
* TimeLib
* ESP32 board library (board library 1.0.4) - https://github.com/espressif/arduino-esp32

Blynk server side code will be added later.

TODO:

* SMS sending support: https://github.com/vshymanskyy/TinyGSM/pull/349
* Ninebot ES1/2/4 lock integration