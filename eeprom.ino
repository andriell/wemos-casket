#include <EEPROM.h>


void eepromSetup() {
  EEPROM.begin(512);
  dataPosition = EEPROM.read(20);
  if (dataPosition >= DATA_LIST_SIZE) {
    dataPosition = 0;
  }
  dbg(2, "Eeprom dataPosition: ");
  dbgLn(2, dataPosition);
  for (int i = 0; i < DATA_LIST_SIZE; i++) {
    for (int j = 0; j < DATA_STR_LENGTH; j++) {
      dataList[i][j] = '\0';
    }
  }
  for (int i = 0; i < DATA_LIST_SIZE; i++) {
    for (int j = 0; j < DATA_STR_LENGTH; j++) {
      dataList[i][j] = char(EEPROM.read(100 + DATA_STR_LENGTH * i + j));
    }
  }
  for (int i = 0; i < DATA_LIST_SIZE; i++) {
    dbg(2, "Eeprom ");
    dbg(2, i);
    dbg(2, " ");
    dbgLn(2, dataList[i]);
  }
}

void eepromWrite(String s) {
  dataPosition++;
  if (dataPosition >= DATA_LIST_SIZE) {
    dataPosition = 0;
  }
  EEPROM.write(20, dataPosition);
  for (int i = 0; i < DATA_STR_LENGTH; i++) {
    if (i < s.length()) {
      EEPROM.write(100 + dataPosition * DATA_STR_LENGTH + i, s[i]);
      dataList[dataPosition][i] = s[i];
    } else {
      EEPROM.write(100 + dataPosition * DATA_STR_LENGTH + i, '\0');
      dataList[dataPosition][i] = '\0';
    }
  }
  EEPROM.commit();
}

time_t eepromGetSoungTime() {
  return eepromULRead(21);
}

void eepromSetSoungTime(time_t t) {
  eepromULWrite(21, t);
}

void eepromULWrite(int addr, unsigned long ul) {
  EEPROM.write(addr, ul & 0xFF);
  EEPROM.write(addr + 1, (ul & 0xFF00) >> 8);
  EEPROM.write(addr + 2, (ul & 0xFF0000) >> 16);
  EEPROM.write(addr + 3, (ul & 0xFF000000) >> 24);
  EEPROM.commit();
}

unsigned long eepromULRead(int addr) {
  unsigned long r;
  byte b = EEPROM.read(addr + 3);
  r = (r << 8) | b;
  b = EEPROM.read(addr + 2);
  r = (r << 8) | b;
  b = EEPROM.read(addr + 1);
  r = (r << 8) | b;
  b = EEPROM.read(addr);
  r = (r << 8) | b;
  return r;
}
