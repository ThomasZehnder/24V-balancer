#ifndef BALANCER_24V_H
#define BALANCER_24V_H      

#include "Arduino.h"




enum OperationMode : byte
{
  modeBalance = 0,
  modeLedCommand = 1,
  modeVoltBandwithInput = 2,
  modeCycleTime
};

extern OperationMode operationMode;

extern int bandwithVoltage;
extern int cycleTime; // in seconds

#endif
