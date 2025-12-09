/*

  Switch on build in LED with serial input 115200 Baud:
  0,1,2,3 = select led, command is modal
  o = off
  x = on
  p = 100ms puls
  f = flash sequence 10 timef


  Arduino Nano
    Old Boot loader !!!
   I2C Bus:
   SDA = A4
   SCL = A5

  // initialize serial: baud rate fix to 115200


*/

#include "serial-help.hpp"
#include "serial-display.hpp"
#include "serial-led.hpp"
#include "Arduino.h"

#include "24V-balancer.hpp"
#include "balancer.hpp"

char c = 0;

char pinArray[4];
char selectetPin = 0;

bool valKey[2];
bool valKey_old[2];

int bandwithVoltage = 100;  // default 100mV
int newBandwithVoltage = 0; // for input bandwith voltage
int cycleTime = 30;         // default 30s

Balancer balancer;

void setup()
{
  // setup OLED display
  displaySetup();

  // initialize serial: baud rate fix to 115200

  Serial.begin(115200);
  Serial.println("################################################################");
  Serial.println(" 24V Balacer 2*12V (115200 Baud )");
  Serial.println("################################################################");
  Serial.print(__DATE__);
  Serial.print(" / ");
  Serial.println(__TIME__);

  // Default settings IO mapping
  pinArray[0] = LED_BUILTIN;
  pinArray[1] = 5;
  pinArray[2] = 6;
  pinArray[3] = 7;

#if defined(ARDUINO_AVR_UNO)
  // Uno pin assignments
  serialPlusOled((char *)"ARDUINO_AVR_UNO");

#elif defined(ARDUINO_AVR_NANO)
  // NANO
  serialPlusOled((char *)"ARDUINO_AVR_NANO");

  pinArray[0] = LED_BUILTIN;
  pinArray[1] = PD5;
  pinArray[2] = PD6;
  pinArray[3] = PD7;

#elif defined(ARDUINO_ESP8266_NODEMCU)
  // ESP8266_NODEMCU
  serialPlusOled((char *)"ESP8266_NODEMCU");

  pinArray[0] = LED_BUILTIN;
  pinArray[1] = D5;
  pinArray[2] = D6;
  pinArray[3] = D7;

#elif defined(ARDUINO_ESP8266_ESP13)
// ESP8266_ESP13 not tested
#error ESP8266_ESP13 not tested Stop compilation.

#else
#error Unsupported board selection. Stop compilation.
#endif

  // initialize leds
  ledInit();

  // initialize balancer
  balancer.setup();

  // INTRO Help (also accessable with \h)
  Serial.println("###############################################################");
  help();
  Serial.println("###############################################################");

  serialPlusOledDelayed((char *)"Boot finished!!!");

  delay(2000);
}

void loop()
{

  displayBalancer();

  balancer.cyclic();
}
