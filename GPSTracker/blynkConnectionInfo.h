// Please enter your APN, server information and auth tokens below.
const char apn[]  = ""; // Access Point Name, check your carrier for this.
const char user[] = ""; // In my case, user and pass were not needed.
const char pass[] = "";
uint16_t port     = 8080; // Port "8080" for non-SSL, "9443" for SSL connection. SIM7000E does not support SSL with TinyGSM yet, currently using non-SSL connection.

// Blynk setup
const char server[] = ""; // Fixed ip or domain (recommended)... it should go here.
const char auth[]   = ""; // Your auth token should go here.

// Select your modem (the modem needs to include GPS and has to be supported by the TinyGSM library):
#define TINY_GSM_MODEM_SIM7000
// #define TINY_GSM_MODEM_SIM808
// #define TINY_GSM_MODEM_SIM868
// #define TINY_GSM_MODEM_SIM900
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

// If the SIM card has a PIN code, uncomment this definition and set it below.
//#define GSM_PIN ""