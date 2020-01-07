# BlynkGPSTracker

What you'll need on the hardware side:

* ESP32 (any should work, testing on Adafruit Huzzah32)
* Any TinyGSM library supported modem *WITH GPS*

I cannot recommend the ESP8266 due to limited serial. AT commands may not go through correctly.

What you'll need on the software side:

* Blynk
* TinyGSM (building on 0.7.9)
* TimeLib
* ESP32 board library

Blynk server side code will be added later.

TODO:

* SMS sending support: https://github.com/vshymanskyy/TinyGSM/pull/349
* Ninebot ES1/2/4 lock integration