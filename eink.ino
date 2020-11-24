// https://rop.nl/truetype2gfx/

// FreeSans24pt7b h:34
// FreeSans9pt7b h:13
// FreeSansBold24pt7b h:35
// FreeSans12pt7b H:17

//#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
//#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>



#define ENABLE_GxEPD2_GFX 0
// copy constructor for your e-paper from GxEPD2_Example.ino, and for AVR needed #defines
#define MAX_DISPLAY_BUFFER_SIZE 800 // 
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
//GxEPD2_BW<GxEPD2_154, MAX_HEIGHT(GxEPD2_154)> display(GxEPD2_154(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEP015OC1 no longer available
//GxEPD2_BW<GxEPD2_154_D67, MAX_HEIGHT(GxEPD2_154_D67)> display(GxEPD2_154_D67(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEH0154D67

// e.g. for Wemos D1 mini:
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // GDEH0154D67

// VCC  - 3v3
// GND  - GND
// D\C  - D3
// SDI  - D7
// CS   - D8
// CLK  - D5
// BUSY - D2


void einkSetup()
{
  display.init(74880, false, false);
}

void einkLoop()
{
  String strHMDM = timeHMDMString();
  String strHM = timeHMString();
  String strDM = timeDMString();

  display.setRotation(1);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);

    display.setFont(&FreeSans12pt7b);
    display.setCursor(3, 20);
    einkPrint(strHM);

    display.setFont(&FreeSansBold24pt7b);
    display.setCursor(0, 116);
    einkPrint(strHM);

    display.setFont(&FreeSans12pt7b);
    display.setCursor(124, 116);
    einkPrint(strDM);

    display.setFont(&lucon9pt7b);
    display.setCursor(0, 178);
    einkPrint(strHMDM);

    display.setFont(&lucon9pt7b);
    display.setCursor(0, 198);
    einkPrint(strHMDM);
  }
  while (display.nextPage());

  display.powerOff();
}
void einkPrint(String s) {
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(s, 0, 0, &tbx, &tby, &tbw, &tbh);
  dbg(2, "String:");
  dbg(2, s);
  dbg(2, " x:");
  dbg(2, tbx);
  dbg(2, " y:");
  dbg(2, tby);
  dbg(2, " w:");
  dbg(2, tbw);
  dbg(2, " h:");
  dbg(2, tbh);
  dbg(2, " xc:");
  dbgLn(2, ((display.width() - tbw) / 2) - tbx);
  display.print(s);
}
/*void einkPrintXY(String s, uint16_t x, uint16_t y)
  {
  display.setRotation(1);
  display.setFont(&FreeMonoBold18pt7b);
  display.setTextColor(GxEPD_BLACK);
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

  void einkPrintByCenter(String s)
  {
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(s, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  einkPrintXY(s, x, y);
  }*/

void einkOff()
{
  display.powerOff();
}
