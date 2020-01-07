// Create button on v. pin V5 (arm/disarm).
BLYNK_WRITE(V5) {
  // Start to listen for hardware interrupts by the MPU6050 and go to deep sleep. Check the power consumption and see if the modem should be put to sleep aswell.
  // need to make void, currently have a empty placeholder mpuInterrupt(); on espPowerManagement.ino
}

// Create button on v. pin V6 (diagnostics page GPS update)
BLYNK_WRITE(V6) {
  int pinValue = param.asInt();
  Serial.print("gps update button (V6) pin status: "); Serial.println(pinValue);
  terminal.println("Starting GPS query..."); terminal.flush();
  getGPS();
  Blynk.virtualWrite(V6, 0); // Should set pin to 0
  // pinValue = 0;
}

// Create button on v. pin V10 (ESP reboot)
BLYNK_WRITE(V10) {
  int pinValue = param.asInt();
  espReboot();
  // pinValue = 0;
}

// Create button on v. pin V13 (Modem info update)
BLYNK_WRITE(V13) {
  int pinValue = param.asInt();
  Serial.print("modem info update button (v13) pin status: "); Serial.println(pinValue);
  terminal.println("Getting modem network info: ");
  getModemInfo();
  terminal.println("Getting modem power info");
  getModemPower();
  Blynk.virtualWrite(V13, 0); // Should set pin to 0
}

// Create button on v. pin V14 (enable/disable GPS). Currently it's buggy (read: does not work)
BLYNK_WRITE(V14) {
  int pinValue = param.asInt();
  if (pinValue = 1) {
    modem.enableGPS();
    Serial.print("gps set on");
  }
  if (pinValue = 0) {
    modem.disableGPS();
    Serial.print("gps set off");
  }
  Serial.print("GPS status: "); Serial.println(pinValue);
  terminal.print("GPS status:"); terminal.println(pinValue);
}
