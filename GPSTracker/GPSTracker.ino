/**************************************************************
 *
 * For this example, you need to install Blynk library:
 *   https://github.com/blynkkk/blynk-library/releases/latest
 *
 * TinyGSM Getting Started guide:
 *   https://tiny.cc/tinygsm-readme
 *
 ********************************************************
 * https://github.com/KRUAndu/BlynkGPSTracker/
 * SOMEWHAT UNSTABLE CODE AND POSSIBLE BUGS, IT'S STILL A PROTOTYPE... EXPECT ESP CORE PANICS.
 * I am writing this code to run on an ESP32 and SIM7000 NB-IoT + GPS module, so change the code accordingly to your network module/CPU.
 **************************************************************/

// Please enter your APN, server information and auth tokens below.
const char apn[]  = ""; // This is important, check your carrier for this.
const char user[] = ""; // In my case, user and pass were not needed.
const char pass[] = "";

// If the SIM card has a PIN code, uncomment definition and set it below.
//#define GSM_PIN ""

// Blynk setup
const char server[] = ""; // Fixed ip or domain (recommended)... it should go here.
const char auth[]   = ""; // Your auth token should go here.

// Select your modem (the modem has to be supported by TinyGSM needs to include GPS):
#define TINY_GSM_MODEM_SIM7000
// #define TINY_GSM_MODEM_SIM808
// #define TINY_GSM_MODEM_SIM868
// #define TINY_GSM_MODEM_SIM900
// #define TINY_GSM_MODEM_SIM7000
// #define TINY_GSM_MODEM_SIM5360
// #define TINY_GSM_MODEM_SIM7600
// #define TINY_GSM_MODEM_UBLOX
// #define TINY_GSM_MODEM_SARAR4
// #define TINY_GSM_MODEM_M95
// #define TINY_GSM_MODEM_BG96
// #define TINY_GSM_MODEM_A6
// #define TINY_GSM_MODEM_A7
// #define TINY_GSM_MODEM_M590
// #define TINY_GSM_MODEM_MC60
// #define TINY_GSM_MODEM_MC60E
// #define TINY_GSM_MODEM_ESP8266
// #define TINY_GSM_MODEM_XBEE
// #define TINY_GSM_MODEM_SEQUANS_MONARCH

#define BLYNK_PRINT Serial // Comment this out to disable prints and save space

// Default heartbeat interval for GSM is 60. If you want override this value, uncomment and set this option:
//#define BLYNK_HEARTBEAT 30

#include <TinyGsmClient.h> // TinyGSM library
#include <BlynkSimpleTinyGSM.h> // Native Blynk communication with the TinyGSM library
#include <TimeLib.h> // Time library
#include <WidgetRTC.h> // Real-time clock Blynk library (necessary for fetching time from the server)

/* // BLE connection, this *needs* some more research.
#define BLYNK_USE_DIRECT_CONNECT // For BLE connection (init. supposedly)
#include <BlynkSimpleEsp32_BT.h> // BLE library for Blynk, might conflict with TinyGSM
#include <BLEDevice.h> // BLE receiver
#include <BLEServer.h> // BLE server
*/

// Serial ports are set for the ESP32 (Adafruit Huzzah32 Feather)
// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial
#define SerialAT Serial1 //Pin 16/17 on ESP32

// or Software Serial on Uno, Nano (cannot recommend, messy input or does not work at all)
//#include <SoftwareSerial.h>
//SoftwareSerial SerialAT(2, 3); // RX, TX

TinyGsm modem(SerialAT);

// Need to add deep sleep to the project for better battery life (include MPU6050 interrupts aswell)
//https://community.blynk.cc/t/esp-deep-sleep/5622/6

//----------------------------------
// Defying and enabling Blynk modules here, setting virtual pins to them...:
//----------------------------------
BlynkTimer timer; WidgetRTC rtc;                                          // Enable timer and realtime clock query from Blynk server to the ESP32
WidgetMap myMap(V0);                                                      // Enable map on v. pin V0
WidgetTerminal terminal(V1);                                              // Enable diagnostics terminal on v. pin V1
WidgetTable table; BLYNK_ATTACH_WIDGET(table, V2);                        // Enable table called "table" on v. pin V2
WidgetLED gpsLockLed(V3);                                                 // Create LED for if GPS Lock is achieved, v. pin V3
// Last update timer display on V8. Set in getRTC.ino, set with function getRTC();
WidgetTable securityTable; BLYNK_ATTACH_WIDGET(securityTable, V11);       // Enable table for security logs (alarm triggered etc.), v. pin V11
WidgetTable modemDiag; BLYNK_ATTACH_WIDGET(modemDiag, V12);               // Enable table for modem diagnostics information, v. pin V12

BLYNK_CONNECTED() {
  // Synchronize time on connection
  rtc.begin();

  // Letting the phone know it's available.
  Blynk.notify("GPS Tracker successfully connected!");
}

//----------------------------------
// Blynk buttons are defined in blynkButtons.ino
// Blynk modules are defined in blynkModules.ino (not working, need to check)
// could change soon...
//----------------------------------

void setup()
{
  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);

  // Set GSM module baud rate
  SerialAT.begin(115200);
  delay(3000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();

  // Get modem info
  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);

  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");

  // Start Blynk session with server
  Blynk.begin(auth, modem, apn, user, pass, server, 8080); // Port set to 8080 as the SIM7000 is not capable of SSL with TinyGSM yet...

  // Other Time library functions can be used, like: timeStatus(), setSyncInterval(interval)...
  // Read more: http://www.pjrc.com/teensy/td_libs_Time.html
  setSyncInterval(10 * 60); // Sync interval in seconds (10 minutes)

  // Display digital clock every 10 seconds (start void getRTC(); every 10 sec)
  //timer.setInterval(10000L, getRTC);

  // After the ESP32 is (re)booted, the modem is (re)initialized with no GPS, thus need to set LED's back to 0... :
  gpsLockLed.off(); // GPS Lock LED
  Blynk.virtualWrite(V6, 0);
  Blynk.virtualWrite(V10, 0); //Rebooting to Reboot (1 to 0) on v. pin V10.

  // Clear the terminal content
  terminal.clear();

  // When done booting, write to the terminal.
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("-------------"));
  terminal.println(F("Blynk GPS Tracker prototype."));
  terminal.println(F("Commands here later..."));
  terminal.flush();
}

void loop()
{
  Blynk.run();
  timer.run();
}
