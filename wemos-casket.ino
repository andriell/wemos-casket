// https://forum.arduino.cc/index.php?topic=682683.0
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "const.h"
// ArduinoJson
#include <ArduinoJson.h>
// Time Timekeeping functionality for Arduino
#include <TimeLib.h>
// GxEPD2
// GFX_Root
#include <GFX.h>
#include <GxEPD2_BW.h> // including both doesn't hurt
#include <GxEPD2_3C.h> // including both doesn't hurt

#define WEMOS_D0     16
#define WEMOS_D1     5
#define WEMOS_D2     4
#define WEMOS_D3     0
#define WEMOS_D4_LED 2
#define WEMOS_D5     14
#define WEMOS_D6     12
#define WEMOS_D7     13
#define WEMOS_D8     15
#define WEMOS_TX     1
#define WEMOS_RX     3

#define TFT_CS   WEMOS_D2
#define TFT_DC   WEMOS_D3
#define TFT_RST  WEMOS_D1

void setup()
{
  wemosSetup();
  ledSetup();
  wifiSetup();
  timeSetup();
  einkSetup();
  dbgSetup();

  timeUpdate();
}

void loop() {
  srLoop();
  dbgLoop();
  einkLoop();
  delay(60000);
  //display.display(false); // full update
}
