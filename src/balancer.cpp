#include "balancer.hpp"
#include "Arduino.h"

#define ANALOG_INPUT_PIN A0 // Define the analog input pin

void Balancer::setup()
{
    // Initialisierungscode hier einfügen
    startTime = millis();
    lastBalanceTime = startTime;
    lastMeasureTime = startTime; // Mess-Timer initialisieren
    balanceState = STATE_IDLE;
    cellIndex = 0;
    cellVoltages[0] = 0.0;
    cellVoltages[1] = 0.0;
}

void Balancer::cyclic()
{
    // Zyklischer Code hier einfügen
    unsigned long currentTime = millis();

    // Mess-Timer: alle 1 Sekunde
    if (currentTime - lastMeasureTime >= 1000)
    {
        lastMeasureTime = currentTime;
        cellVoltages[cellIndex] = readAnalogInput();
    }

    long elapsedTime = ((long)currentTime - lastBalanceTime) / 1000; // in Sekunden
    if (elapsedTime >= cycleTime)
    {
        lastBalanceTime = currentTime;
        Serial.println("Balancing cells..."); // Platzhalter-Ausgabe

        switch (balanceState)
        {
        case STATE_IDLE:
            balanceState = STATE_BALANCING_0;
            switchLoadResistor(cellVoltages[0]-cellVoltages[1] > (bandwithVoltage));
            Serial.println("State changed to BALANCING");
            break;

        case STATE_BALANCING_0:
            balanceState = STATE_BALANCING_1;
            switchLoadResistor(cellVoltages[1]-cellVoltages[0] > (bandwithVoltage));
            Serial.println("State changed to BALANCING_1");
        case STATE_BALANCING_1:
            balanceState = STATE_IDLE;
            incrementCellIndex();
            Serial.println("State changed to IDLE");
            break;
        }
    }
}

int Balancer::readAnalogInput()
{
    int value = analogRead(ANALOG_INPUT_PIN);
    float voltage = (value / 1023.0) * 15.0; // Annahme: 5V Referenzspannung mit Spannungsteiler 1/3
    Serial.print("Analog A0: ");
    Serial.print(voltage);
    Serial.println("V");
    return voltage;
}

float Balancer::getCellVoltage(int cellIndex)
{
    if (cellIndex < 0 || cellIndex >= 2)
    {
        Serial.println("Invalid cell index");
        return -1.0; // Ungültiger Index
    }
    return cellVoltages[cellIndex];
}

void Balancer::incrementCellIndex()
{
    cellIndex = (cellIndex + 1) % NUMBER_OF_CELLS;
    Serial.print("Cell index: ");
    Serial.println(cellIndex);
    digitalWrite(pinArray[CELL_SELECT_INDEX], cellIndex); // select cell
}

void Balancer::switchLoadResistor(bool state)
{
    // Load resistor control code here
    digitalWrite(pinArray[LOADRESISTOR_SELECT_INDEX], state); // select cell
    Serial.print("Load resistor:");

    Serial.println(state);
}