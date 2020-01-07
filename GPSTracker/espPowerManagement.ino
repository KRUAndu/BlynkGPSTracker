// Full ESP reboot (with 3sec delay).
void espReboot() {
  Blynk.notify("Rebooting ESP32 in 3 seconds..."); delay(3000); // 3sec delay to ensure the message gets to the server
  ESP.restart();
}

// ESP deep sleep for battery saving
void espSleep() {
  Blynk.notify("ESP32 sleep in 3 seconds..."); delay(3000);
  modem.disableGPS(); // Disable the gps. is this necessary? 
  // TO DO!
}

// ESP interrupt by MPU6050
void mpuInterrupt() {
  // TO DO! https://forum.arduino.cc/index.php?topic=580232.0
  
  // Need to add deep sleep to the project for better battery life (include MPU6050 interrupts aswell)
  //https://community.blynk.cc/t/esp-deep-sleep/5622/6
}
