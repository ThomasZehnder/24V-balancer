#include "Arduino.h"
#include "serial-display.hpp"
#include "24V-balancer.hpp"
#include "serial-help.hpp"

void help()
{
  char buf[30];
  sprintf(buf, "Cycle Time: %d s", cycleTime);
  serialPlusOled(buf);
  sprintf(buf, "Bandwith new: %d mV", bandwithVoltage);
  serialPlusOledDelayed(buf);
}

