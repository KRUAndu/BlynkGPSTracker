// Modem diagostics values, adding more later...
void getModemInfo() {
  String ccid = modem.getSimCCID();     
  String imei = modem.getIMEI();        
  String cop = modem.getOperator();     
  IPAddress local = modem.localIP();  
  int csq = modem.getSignalQuality();

  //modemDiag is the table, where we will be adding this info to.
  modemDiag.addRow(1, "CCID:", ccid);
  modemDiag.addRow(2, "IMEI:", imei);
  modemDiag.addRow(3, "SIM Operator:", cop);
  modemDiag.addRow(4, "IP Address:", local);
  modemDiag.addRow(5, "Signal quality:", csq);
}

void getModemPower() { // Values seem off atm.
  uint8_t chargeState = -99;
  int8_t percent = -99;
  uint16_t milliVolts = -9999;
  modem.getBattStats(chargeState, percent, milliVolts);

  modemDiag.addRow(6, "Battery charge state:", chargeState);
  modemDiag.addRow(7, "Battery charge 'percent':", percent);
  modemDiag.addRow(8, "Battery voltage:", milliVolts / 1000.0F);
}
