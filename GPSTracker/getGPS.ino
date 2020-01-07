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

  //terminal.println(lat,6); // The float accuracy here is 6! Need to get this into a string maybe...
  //terminal.print("Latitude: "); terminal.println(lat);
  //terminal.print("Longitude: "); terminal.println(lng);

  //terminal.print("Latitude: "); terminal.println(lt);  //terminal.println(lag); - this is with dtostrf();
  //terminal.print("Longitude: "); terminal.println(ln); //terminal.println(lng); - this is with dtostrf();
  //terminal.print("Speed: "); terminal.println(speed);
  //terminal.print("Altitude: "); terminal.println(alt);
  //terminal.print("Viewed satellites: "); terminal.println(vsat);
  //terminal.print("Used satellites: "); terminal.println(usat);

}

/* DEPRECATED GPS QUERY...
 * void getGPSRaw() {
    modem.enableGPS();
    terminal.println("Raw GPS location query from SIM7000'") ;
    // Get time from GPS
    int year, month, day, hour, minute, second;
    modem.getGPSTime(&year, &month, &day, &hour, &minute, &second);
    // Create datastore strings for value parsing:
    String rawGps = modem.getGPSraw();
    String value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, value11, value12, value13, value14, value15, value16, value17, value18, value19, value20, value21, value22;

    // Create integers for data parsing:
    int data1; //1 GNSS run status -- 0-1 1
    int data2; //2 Fix status -- 0-1 1
    int data3; //3 UTC date & Time yyyyMMddhh mmss.sss yyyy: [1980,2039] MM : [1,12] dd:   [1,31] hh:   [0,23] mm:  [0,59] ss.sss:[0.000,60.999] 18
    int data4; //4 Latitude ±dd.dddddd [-90.000000,90.000000] 10
    int data5; //5 Longitude ±ddd.dddddd [-180.000000,180.000000] 11
    int data6; //6 MSL Altitude meters  8
    int data7; //7 Speed Over Ground Km/hour [0,999.99] 6
    int data8; //8 Course Over Ground degrees [0,360.00] 6
    int data9; //9 Fix Mode -- 0,1,2[1] 1
    int data10; //10 Reserved1   0
    int data11; //11 HDOP -- [0,99.9] 4
    int data12; //12 PDOP -- [0,99.9] 4
    int data13; //13 VDOP -- [0,99.9] 4
    int data14; //14 Reserved2   0
    int data15; //15 GPS Satellites in View -- [0,99] 2
    int data16; //16 GNSS Satellites Used -- [0,99] 2
    int data17; //17 GLONASS Satellites in View -- [0,99] 2
    int data18; //18 Reserved3   0
    int data19; //19 C/N0 max dBHz [0,55] 2
    int data20; //20 HPA[2] meters [0,9999.9] 6
    int data21; //21 VPA[2] meters [0,9999.9] 6 Total：(94) chars
    int data22; //22 ???? Have no clue on what this is, prints out 22 values instead of 21 according to the AT datasheet...

    // ... time to parse.
    data1 = rawGps.indexOf(',');  //finds location of first ,
    value1 = rawGps.substring(0, data1);   //captures first data String
    data2 = rawGps.indexOf(',', data1+1 );   //finds location of second ,
    value2 = rawGps.substring(data1+1, data2+1); value2.replace(",", "");   //captures second data String
    data3 = rawGps.indexOf(',', data2+1 );
    value3 = rawGps.substring(data2+1, data3+1); value3.replace(",", "");
    data4 = rawGps.indexOf(',', data3+1 );
    value4 = rawGps.substring(data3+1, data4+1); value4.replace(",", ""); //value4.remove(9, 1); - old method... remove deleted last comma from coordinate output
    data5 = rawGps.indexOf(',', data4+1 );
    value5 = rawGps.substring(data4+1, data5+1); value5.replace(",", ""); //value5.remove(9, 1); //fix parse... Delete comma from coordinate output
    data6 = rawGps.indexOf(',', data5+1 );
    value6 = rawGps.substring(data5+1, data6+1); value6.replace(",", "");
    data7 = rawGps.indexOf(',', data6+1 );
    value7 = rawGps.substring(data6+1, data7+1); value7.replace(",", "");
    data8 = rawGps.indexOf(',', data7+1 );
    value8 = rawGps.substring(data7+1, data8+1); value8.replace(",", "");
    data9 = rawGps.indexOf(',', data8+1 );
    value9 = rawGps.substring(data8+1, data9+1); value9.replace(",", "");
    data10 = rawGps.indexOf(',', data9+1 )
    value10 = rawGps.substring(data9+1, data10+1); value10.replace(",", "");
    data11 = rawGps.indexOf(',', data10+1 );
    value11 = rawGps.substring(data10+1, data11+1); value11.replace(",", "");
    data12 = rawGps.indexOf(',', data11+1 );
    value12 = rawGps.substring(data11+1, data12+1); value12.replace(",", "");
    data13 = rawGps.indexOf(',', data12+1 );
    value13 = rawGps.substring(data12+1, data13+1); value13.replace(",", "");
    data14 = rawGps.indexOf(',', data13+1 );
    value14 = rawGps.substring(data13+1, data14+1); value14.replace(",", "");
    data15 = rawGps.indexOf(',', data14+1 );
    value15 = rawGps.substring(data14+1, data15+1); value15.replace(",", "");
    data16 = rawGps.indexOf(',', data15+1 );
    value16 = rawGps.substring(data15+1, data16+1); value16.replace(",", "");
    data17 = rawGps.indexOf(',', data16+1 );
    value17 = rawGps.substring(data16+1, data17+1); value17.replace(",", "");
    data18 = rawGps.indexOf(',', data17+1 );
    value18 = rawGps.substring(data17+1, data18+1); value18.replace(",", "");
    data19 = rawGps.indexOf(',', data18+1 );
    value19 = rawGps.substring(data18+1, data19+1); value19.replace(",", "");
    data20 = rawGps.indexOf(',', data19+1 );
    value20 = rawGps.substring(data19+1, data20+1); value20.replace(",", "");
    data21 = rawGps.indexOf(',', data20+1 );
    value21 = rawGps.substring(data20+1, data21+1); value21.replace(",", "");
    data22 = rawGps.indexOf(',', data21+1 );
    value22 = rawGps.substring(data21+1);

    //GPS Lock LED
    if (value2 == "1") {
      gpsLockLed.on(); //Turns on the GPS Lock LED
      Blynk.virtualWrite(V7, value4); //Display latitude coordinate on value display
      Blynk.virtualWrite(V9, value5); //Display longitude coordinate on value display
      getRTC();
    } else {
      gpsLockLed.off();     //You can change LED color with: Blynk.setProperty(V3, "color", "#D3435C");
      Serial.println("GPS lock not achieved, led off.");
      delay(3000);          //retry after 3sec.
      getGPSRaw();

    }

    myMap.location(1, value4, value5, "From DIY rawGPS parsing."); //index is 1
    table.addRow(1, "GNSS run status", value1);
    table.addRow(2, "GPS Fix status", value2);
    table.addRow(3, "UTC date and time", value3);
    //table.addRow(4, "Latitude", value4.toFloat());
    //table.addRow(5, "Longitude", value5.toFloat());
    table.addRow(4, "Latitude", value4);
    table.addRow(5, "Longitude", value5);
    table.addRow(6, "Altitude in meters", value6);
    table.addRow(7, "Speed kmh", value7);
    table.addRow(8, "Course 360deg", value8);
    table.addRow(9, "Fix mode", value9);
    table.addRow(10, "RESERVED", value10);
    table.addRow(11, "HDOP", value11);
    table.addRow(12, "PDOP", value12);
    table.addRow(13, "VDOP", value13);
    table.addRow(14, "RESERVED2", value14);
    table.addRow(15, "GPS sats in view", value15);
    table.addRow(16, "GNSS sats used", value16);
    table.addRow(17, "GLONASS sats in view", value17);
    table.addRow(18, "RESERVED3", value18);
    table.addRow(19, "C/N0 max dBHz", value19);
    table.addRow(20, "HPA[2] meters", value20);
    table.addRow(21, "VPA[2] meters", value21);
    table.addRow(22, "UNDEFINED", value22);
    //Blynk.virtualWrite(V2, "add", 1, "GNSS run status", value1);

    Serial.println("Displaying raw data");
    Serial.println(rawGps);
}
*/
