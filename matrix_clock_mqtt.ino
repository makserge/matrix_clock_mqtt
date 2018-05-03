#include "TimeLib.h"
#include "TimeAlarms.h"
#include "SunFounderEmo.h"

const int CS_PIN = 10;

const double TIME_UPDATE_INTERVAL = 1;

SunFounderEmo ledDisp(CS_PIN);

boolean isUpdateDisplay = true;
boolean isTimeTick;

void getTimeTick() {
  isTimeTick = !isTimeTick;
  isUpdateDisplay = true;
}

void updateDisplay() {
  if (!isUpdateDisplay) {
    return;
  }
  isUpdateDisplay = false;
  
  ledDisp.resetDisplay();

  byte hours = hour();
  byte minutes = minute();

  if (hours > 9) {
    ledDisp.setDigit(3, hours / 10);
  }
  ledDisp.setDigit(2, hours % 10);
    
  ledDisp.setDigit(1, minutes / 10);
  ledDisp.setDigit(0, minutes % 10);

  ledDisp.showTimeTick(isTimeTick);

  ledDisp.updateDisplay();
}

void setup() {
  Alarm.timerRepeat(TIME_UPDATE_INTERVAL, getTimeTick);
}

void loop() {
  updateDisplay();
  Alarm.delay(100);
}
