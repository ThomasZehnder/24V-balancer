#include "Arduino.h"
#include "serial-display.hpp"

void help()
{
  int aditionalDelay = 0;

  serialPlusOledDelayed((char *)"Out Tests");
  serialPlusOledDelayed((char *)"x,o = off/on");
  serialPlusOledDelayed((char *)"d = 100ms delay");
  serialPlusOledDelayed((char *)"p = 100ms puls");
  serialPlusOledDelayed((char *)"f = flash sequence 10 times fast");
  serialPlusOledDelayed((char *)"0..3 = select led (modal)");
  serialPlusOledDelayed((char *)"h = this help");
  
  delay(200+aditionalDelay);

  serialPlusOledDelayed((char *)"Mode Switch");
  serialPlusOledDelayed((char *)"^ = switch to Out Test");
  serialPlusOledDelayed((char *)"@ = switch to Balance Mode");


}
