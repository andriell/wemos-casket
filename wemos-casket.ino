// https://github.com/robsoncouto/arduino-songs
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

#define MAX_UL 0xFFFFFFFFUL

#define WEMOS_A0     17
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

#define DATA_LIST_SIZE 5
#define DATA_STR_LENGTH 25
#define PLAY_SONG_AFTER 30

byte dataPosition = 0;
String dataList[] = {
  "1234567890123456789012345",
  "1234567890123456789012345",
  "1234567890123456789012345",
  "1234567890123456789012345",
  "1234567890123456789012345",
};

unsigned long sleepTime = 0ul;

void setup()
{
  unsigned long startMillis = millis();
  wemosSetup();
  Serial.println("Wake up");
  beepSetup();
  ledSetup();
  liionSetup();
  eepromSetup();
  dbgSetup();
  wifiSetup();
  timeSetup();
  einkSetup();

  timeUpdate();

  unsigned long soungTime = eepromGetSoungTime();
  dbg(1, "Now: ");
  dbg(1, now());
  dbg(1, " Soung time: ");
  dbgLn(1, soungTime);

  if (soungTime > 0 && now() > soungTime) {
    dbgLn(1, "Play song");
    eepromSetSoungTime(0ul);
    beepSong3();
    sleepTime = 0ul;
  } else {
    dbgLn(1, "Update time");
    einkLoop();
    String strHMDM = timeHMDMString();
    eepromWrite(strHMDM);
    eepromSetSoungTime(now() + PLAY_SONG_AFTER - 1);
    sleepTime = PLAY_SONG_AFTER * 1e6;
  }
  wifiDisconnect();

  Serial.print("Execution time ");
  Serial.println(millis() - startMillis);
}

void loop() {
  Serial.println("Sleep");
  ESP.deepSleep(sleepTime);
}
