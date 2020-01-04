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

  if (String("GetRTC") == param.asStr()) {
    getRTC();
  }  

  if (String("reboot") == param.asStr()) {
    espReboot();
  }  

  if (String("timeStatus") == param.asStr()) {
    timeStatus();
  }  
}
