BLYNK_WRITE(V1) { // Terminal on V1 (blynk virtual pin)
  //Start GetGPS gps query and submit the data to the map.
  if (String("GetGPS") == param.asStr()) {
    terminal.println("GetGPS query...") ;
    getGPS();
    terminal.flush();
  }

//  if (String("GetGPSRaw") == param.asStr()) {
//    getGPSRaw();
//  }

  if (String("GetRTC") == param.asStr()) { // Fetches the real time clock.
    getRTC();
  }

  if (String("reboot") == param.asStr()) { // Reboots the ESP32.
    espReboot();
  }

  if (String("timeStatus") == param.asStr()) { // seems to do a manual time sync.
    timeStatus(); //Time library function (http://www.pjrc.com/teensy/td_libs_Time.html)
  }

  if (String("GetInfo") == param.asStr()) {
    getModemInfo();
    getModemPower();
  }

}
