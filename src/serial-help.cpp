#include "Arduino.h"
#include "serial-display.hpp"

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
  serialPlusOledDelayed((char *)"@ = switch to Balance Mode (default)");
  serialPlusOledDelayed((char *)"# = switch to Out Test");
  serialPlusOledDelayed((char *)"b = switch to Input Bandwith Voltage");
  serialPlusOledDelayed((char *)"c = switch to Input Cycle Time");

  delay(2000);

}
