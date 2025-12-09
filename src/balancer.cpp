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
    analogReference(DEFAULT); // Use internal 5V reference, AREF pin unused
}

void Balancer::cyclic()
{
    // Zyklischer Code hier einfügen
    unsigned long currentTime = millis();

    // Mess-Timer: alle Sekunde
    if (currentTime - lastMeasureTime >= 1000)
    {
        lastMeasureTime = currentTime;
        cellVoltages[cellIndex] = readAnalogInput();

        switch (balanceState)
        {
        case STATE_IDLE:
            balanceState = STATE_MEASSURE_0;
            Serial.println(F("State changed to STATE_MEASSURE_0"));
            break;
        case STATE_MEASSURE_0:
            balanceState = STATE_MEASSURE_1;
            setCellIndex(1);
            Serial.println(F("State changed to STATE_MEASSURE_1"));
            break;
        case STATE_MEASSURE_1:
            balanceState = STATE_BALANCING_0;
            setCellIndex(0);
            Serial.println(F("State changed to STATE_BALANCING_0"));
            break;
        case STATE_BALANCING_0:
            switchLoadResistor(calculateBalanceNeeded(0, 1));
            break;

        case STATE_BALANCING_1:
            switchLoadResistor(calculateBalanceNeeded(1, 0));
            break;

        default:
            switchLoadResistor(false);
            break;
        }
        printLineStatus();
        setUpdateDisplay(true);
    }

    long elapsedTime = ((long)currentTime - lastBalanceTime) / 1000; // in Sekunden
    if (elapsedTime >= cycleTime)
    {
        lastBalanceTime = currentTime;
        Serial.println(F("Balancing batteries...")); // Platzhalter-Ausgabe

        switch (balanceState)
        {

        case STATE_BALANCING_0:
            balanceState = STATE_BALANCING_1;
            setCellIndex(1);
            Serial.println(F("State changed to STATE_BALANCING_1"));
            break;

        case STATE_BALANCING_1:
            balanceState = STATE_BALANCING_0;
            setCellIndex(0);
            Serial.println(F("State changed to STATE_BALANCING_0"));
            break;
        default:
            //
            break;
        }
    }
}

float Balancer::readAnalogInput()
{
    int value = analogRead(ANALOG_INPUT_PIN);
    float voltage = (value / 1023.0) *5*3/13.21*13.14; // Annahme: 5V Referenzspannung mit Spannungsteiler 1/3
    Serial.print(F("Analog A0: "));
    Serial.print(value);
    Serial.print(":");
    Serial.print(voltage);
    Serial.println("V");
    return voltage;
}

float Balancer::getCellVoltage(int cellIndex)
{
    if (cellIndex < 0 || cellIndex >= 2)
    {
        Serial.println(F("Invalid cell index"));
        return 0.0; // Ungültiger Index
    }
    return getCellVoltage(cellIndex);
}

void Balancer::setCellIndex(byte index)
{
    cellIndex = index;
    Serial.print(F("New cell index: "));
    Serial.println(cellIndex);
    digitalWrite(pinArray[CELL_SELECT_INDEX], cellIndex); // select cell
}

void Balancer::switchLoadResistor(bool state)
{
    // Load resistor control code here
    isBalancing = state;                                            // Status, ob gerade balanciert wird
    digitalWrite(pinArray[LOADRESISTOR_SELECT_INDEX], isBalancing); // select cell
    int ledBrightness = isBalancing ? 32 : 0; //0..255
    analogWrite(LED_BUILTIN, ledBrightness); //show on led
    Serial.print(F("Load resistor:"));
    Serial.println(isBalancing ? " ON" : " OFF");
}

bool Balancer::calculateBalanceNeeded(byte index1, byte index2)
{
    voltageDiff = (cellVoltages[index1] - cellVoltages[index2]) * 1000.0; // in mV
    Serial.print(F("Batteries Voltage Difference: "));
    Serial.print(voltageDiff);
    Serial.println(" mV");
    return voltageDiff > bandwithVoltage;
}

void Balancer::printLineStatus()
{
    String status = F("Balancer Status:");
    Serial.println(status);
    status = "Bat 0 Voltage: ";
    status += getCellVoltageString(0);
    Serial.println(status);
    status = F("Bat 1 Voltage: ");
    status += getCellVoltageString(1);
    Serial.println(status);
    status = F("Current State: ");
    status += getState();
    Serial.println(status);
    status = F("Is Balancing: ");
    status += getBalancingMode() + "\n";
    Serial.println(status);
}

String Balancer::getBalancingMode()
{
    return String(isBalancing ? "ON" : "OFF");
}

String Balancer::getState()
{
    String status;
    switch (balanceState)
    {
    case STATE_IDLE:
        status = F("IDLE");
        break;
    case STATE_BALANCING_0:
        status = F("BALANCING 1");
        break;
    case STATE_BALANCING_1:
        status = F("BALANCING 2");
        break;
    case STATE_MEASSURE_0:
        status = F("MEASSURE 1");
        break;
    case STATE_MEASSURE_1:
        status = F("MEASSURE 2");
        break;
    default:
        status = "...";
        break;
    }
    return status;
}

String Balancer::getCellVoltageString(byte index)
{
    if (index >= 2)
    {
        return F("Invalid cell index");
    }
    return String(cellVoltages[index]);
}

String Balancer::getDifferenceString()
{
    return String((int)voltageDiff/10*10); // rounded to 10mV
}