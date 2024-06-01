//🎫Serial ID for node Device for mqtt broker
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <Arduino.h>
#include "SerialNumber.h"
String getSerialNumber() {
  // Retrieve the MAC address as a hex string
  char ssid[14];
  snprintf(ssid, 14, "%llX", ESP.getEfuseMac());
  
  // Convert the MAC address to a String for easier manipulation
  String ssid1 = ssid;
  int StrLen = ssid1.length();

  // Construct the serial number using the MAC address and MCU type
  String MCUtype = "ESP";
  String Serialnumber = MCUtype + "-";
  for (int j = 3; j < 6; j++) {  
    Serialnumber += ssid1.substring(StrLen - 2 - 2 * j, StrLen - 2 * j);
  }

  return Serialnumber;
}

