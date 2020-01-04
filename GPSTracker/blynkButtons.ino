// Create button on v. pin V6 (diagnostics page GPS update)
BLYNK_WRITE(V6) {
  int pinValue = param.asInt();
  Serial.print("V6 pin status: "); Serial.println(pinValue);
  terminal.println("Start GPS query: ");
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
