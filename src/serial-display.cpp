#include "Arduino.h"
#include "serial-display.hpp"
#include "balancer.hpp"

SSD1306AsciiWire oled;

void displaySetup(void)
{
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setScrollMode(SCROLL_MODE_AUTO);

  oled.setFont(fixed_bold10x15);
  oled.clear();
  oled.println("24V Balancer");

  oled.setFont(System5x7);
  oled.print("Build: ");
  oled.println(__DATE__);
  oled.print(" / ");
  oled.println(__TIME__);
  delay(2000);
}

void serialPlusOled(char *s)
{
  Serial.println(s);
  oled.println(s);
}

void serialPlusOledDelayed(char *s)
{
  serialPlusOled(s);
  delay(50);
}

void displayBalancer()
{
  if (balancer.getUpdateDisplay())
  {
    balancer.setUpdateDisplay(false);

    // oled.clear();
    oled.setCursor(0, 0);
    oled.setFont(fixed_bold10x15);

    oled.print("Mode: ");
    oled.println(balancer.getState() + "         ");

    oled.setFont(System5x7);
    
    oled.print("Cell 1: ");
    oled.println(balancer.getCellVoltageString(0));

    oled.print("Cell 2: ");
    oled.println(balancer.getCellVoltageString(1));

    oled.print("Balancing: ");
    oled.println(balancer.getBalancingMode());
  }
}