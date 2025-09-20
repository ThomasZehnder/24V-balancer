#include "Arduino.h"
#include "serial-display.hpp"

extern int cycleTime;
extern int bandwithVoltage; 

void help()
{
  serialPlusOledDelayed((char *)"Out Tests");
  serialPlusOledDelayed((char *)"x,o = off/on");
  serialPlusOledDelayed((char *)"d = 100ms delay");
  serialPlusOledDelayed((char *)"p = 100ms puls");
  serialPlusOledDelayed((char *)"f = flash sequence 10 times fast");
  serialPlusOledDelayed((char *)"0..3 = select led (modal)");
  serialPlusOledDelayed((char *)"h = this help");

  delay(2000);

  serialPlusOledDelayed((char *)"Mode Switch");
  serialPlusOledDelayed((char *)"@= Balance Mode (default)");
  serialPlusOledDelayed((char *)"#= Out Test");
  serialPlusOledDelayed((char *)"b= Input Bandwith Voltage");
  serialPlusOledDelayed((char *)"c= Input Cycle Time");

  delay(2000);

  char buf[30];
  sprintf(buf, "Cycle Time: %d s", cycleTime);
  serialPlusOled(buf);
  sprintf(buf, "Bandwith new: %d mV", bandwithVoltage);
  serialPlusOledDelayed(buf);
}
