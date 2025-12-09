#include "Arduino.h"
#include "serial-led.hpp"
#include "serial-display.hpp"

void ledInit(void)
{
  int i;
  // initialize digital pin LED_BUILTIN as an output.
  for (i = 0; i < 4; i++)
  {
    pinMode(pinArray[i], OUTPUT);
    digitalWrite(pinArray[i], LOW); // turn the LED off by making the voltage LOW
    selectetPin = (1+i)%4;
  }
}

