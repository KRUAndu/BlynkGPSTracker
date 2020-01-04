// Full ESP reboot (with 3sec delay).
void espReboot() {
  Blynk.notify("Rebooting ESP32 in 3 seconds..."); delay(3000); // 3sec delay to ensure the message gets to the server
  ESP.restart();
}

// ESP deep sleep for battery saving
void espSleep() {
  Blynk.notify("ESP32 sleep in 3 seconds..."); delay(3000);
  // TO DO!
}

// ESP interrupt by MPU6050
void mpuInterrupt() {
  // TO DO! https://forum.arduino.cc/index.php?topic=580232.0
}