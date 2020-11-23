// https://forum.arduino.cc/index.php?topic=682683.0
// Libraries:
// GxEPD2
// GFX_Root

// VCC  - 3v3
// GND  - GND
// D\C  - D3
// SDI  - D7
// CS   - D8
// CLK  - D5
// BUSY - D2


// GxEPD2_HelloWorld.ino by Jean-Marc Zingg

// uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX
#include <GFX.h>

#define ENABLE_GxEPD2_GFX 0
#include <GxEPD2_BW.h> // including both doesn't hurt
#include <GxEPD2_3C.h> // including both doesn't hurt
#include <Fonts/FreeMonoBold24pt7b.h>

// copy constructor for your e-paper from GxEPD2_Example.ino, and for AVR needed #defines
#define MAX_DISPLAY_BUFFER_SIZE 800 // 
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
//GxEPD2_BW<GxEPD2_154, MAX_HEIGHT(GxEPD2_154)> display(GxEPD2_154(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEP015OC1 no longer available
//GxEPD2_BW<GxEPD2_154_D67, MAX_HEIGHT(GxEPD2_154_D67)> display(GxEPD2_154_D67(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEH0154D67

// e.g. for Wemos D1 mini:
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // GDEH0154D67

void setup()
{
  Serial.begin(74880);
  display.init(74880, false, false);
}

const char HelloWorld[] = "Hello World! ";
int i = 0;
void helloWorld()
{
  String s = String(++i);
  display.setRotation(1);
  display.setFont(&FreeMonoBold24pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(s, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(s);
  }
  while (display.nextPage());
}

void loop() {
  helloWorld();
  display.powerOff();
  delay(10000);
  //display.display(false); // full update
}
