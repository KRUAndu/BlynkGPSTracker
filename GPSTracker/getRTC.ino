// Strings for currentTime and ...Date, these can be called from anywhere in the code.
String currentTime = String(hour()) + ":" + minute() + ":" + second();
String currentDate = String(day()) + " " + month() + " " + year();

// Get real time clock from the server.
void getRTC() {
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + "/" + month() + "/" + year();
  
  terminal.print("Current time: "); terminal.print(currentTime); terminal.print(" "); terminal.print(currentDate); terminal.println(); terminal.flush();

  Blynk.virtualWrite(V8, currentTime);  // Show last update time on v. pin V8 (value display)

  // NO ZERO FIX. TO DO!
  // You can call hour(), minute(), ... at any time
  // Please see Time library examples for details
  /*int gmthour = hour();
  if (gmthour == 24){
     gmthour = 0;
  }
  String displayhour =   String(gmthour, DEC);
  int hourdigits = displayhour.length();
  if(hourdigits == 1){
    displayhour = "0" + displayhour;
  }
  String displayminute = String(minute(), DEC);
  int minutedigits = displayminute.length();
  if(minutedigits == 1){
    displayminute = "0" + displayminute;
  }
  String displaysecond = String(second(), DEC);
  int seconddigits = displaysecond.length();
  if(seconddigits == 1){
    displaysecond = "0" + displaysecond;
  String lastUpdateTime = displayhour + ":" + displayminute + displaysecond;*/

  // Send time to the App
  //Blynk.virtualWrite(V1, currentTime);
  // Send date to the App
  //Blynk.virtualWrite(V2, currentDate);
}
