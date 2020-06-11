// Retrieve the user's phone location.
BLYNK_WRITE(V15) {
  float phoneLatitude = param[0].asFloat();
  float phoneLongitude = param[1].asFloat();

/****************************************************************
 *  This will calculate the distance of you from the tracker. not done yet, must implement later. might need #include <math.h>
  float calcDistance(float A, float B, float C, float D) {
    float dLat;
    float dLon;
    dLat = (C - A);
    dLon = (D - B);
    dLat /= 57.29577951;
    dLon /= 57.29577951;
    float v_a;
    float v_c;
    float distance;

    v_a = sin(dLat/2) * sin(dLat/2) + cos(A) * cos(C) * sin(dLon/2) * sin(dLon/2);
    v_c = 2 * atan2(sqrt(v_a),sqrt(1-v_a));
    distance = r * v_c;
    return distance;
  }
**************************************************************** */
}

int gpsRetryCount = 0; // For counting GPS signal query retries...

void getGPS() {
  modem.enableGPS();
    float lat, lng, speed;
    int alt, vsat, usat;
    modem.getGPS(&lat, &lng, &speed, &alt, &vsat, &usat); delay(10);
    //Serial.println("getGPS started.");

    while (usat < 4) { // try to change the TinyGSMSIM7000 source code to output fix status... right now it's determining by sat. count
      if (gpsRetryCount == 15) {
          Blynk.notify("GPS location query timeout! Retry in X minutes...");
          table.addRow(1, "GPS loc. query timeout! Retry", "in Xmin.");
          gpsRetryCount = 0;
          Blynk.virtualWrite(V6, 0);
          return;
      }

      gpsRetryCount++; // Rises int. value of the counter by 1
      //Serial.print("no gps, values usat: " ); Serial.print(usat); Serial.print(", lat: " ); Serial.println(lat);
      table.addRow(1, "No GPS lock, hang on... retries:", gpsRetryCount);
      gpsLockLed.off();     // You can change LED color with: Blynk.setProperty(V3, "color", "#D3435C");
      //securityTable.addRow(1, "No GPS fix... " + currentDate, currentTime); -- maybe print out No gps lock with SAT count etc...
      delay(5000);          // Retry after 5sec.

      modem.getGPS(&lat, &lng, &speed, &alt, &vsat, &usat); delay(10); // Retry GPS query and update floats/integers for WHILE and IF arguments.
    }

    gpsRetryCount = 0; // Reset GPS signal query retry counter

    char gpsBuffer[10];
    String lt = dtostrf(lat, 2, 6, gpsBuffer); delay(10);  // avr-libc function for floats
    String ln = dtostrf(lng, 2, 6, gpsBuffer); delay(10);

    String currentTime = String(hour()) + ":" + minute() + ":" + second();
    String currentDate = String(day()) + "/" + month() + "/" + year();
    delay(10);

    table.addRow(1, "GPS Fix", 1);
    table.addRow(2, "Latitude", lt);
    table.addRow(3, "Longitude", ln);
    table.addRow(4, "Altitude (m)", alt);
    table.addRow(5, "Speed (km/h)", speed);
    table.addRow(6, "GPS sats in view", vsat);
    table.addRow(7, "GNSS sats used", usat);
    table.addRow(8, "Last update: " + currentDate, currentTime);
    delay(10);

  gpsLockLed.on(); //Turns on the GPS Lock LED
  myMap.location(0, lat, lng, "Bike0"); delay(10); // index 0 for myMap.location submit
  Blynk.virtualWrite(V7, lt); Blynk.virtualWrite(V9, ln);  //Display coordinates on value displays
  getRTC();
  Blynk.virtualWrite(V6, 0); // Reter update button from 1 to 0.
}
