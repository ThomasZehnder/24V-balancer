#include "balancer.hpp"
#include "Arduino.h"

#define ANALOG_INPUT_PIN A0 // Define the analog input pin
#define MODE_PIN_1 11    // Define mode input pin 1
#define MODE_PIN_2 12    // Define mode input pin 2

void Balancer::setup()
{
    // Initialisierungscode hier einfügen
    startTime = millis();
    lastBalanceTime = startTime;
    lastMeasureTime = startTime; // Mess-Timer initialisieren
    balanceState = STATE_IDLE;
    cellIndex = 0;
    analogReference(DEFAULT); // Use internal 5V reference, AREF pin unused

    pinMode(MODE_PIN_1, INPUT_PULLUP);
    pinMode(MODE_PIN_2, INPUT_PULLUP);  

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

        mode = readModeInputs();

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

    
    // reduce cycletime in case of not balancing
    long localCycleTime;
    if (!isBalancing)
    {
        localCycleTime = 2; // 2s
    }
    else
    {
        localCycleTime = cycleTime; 
    }

    elapsedTime = ((long)currentTime - lastBalanceTime) / 1000; // in Sekunden
    if (elapsedTime >= localCycleTime)
    {
        lastBalanceTime = currentTime;
        Serial.println(F("Balancing batteries...")); 

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
BalancerMode Balancer::getMode()
{   bool input1 = digitalRead(MODE_PIN_1); // Mode pin 1
    bool input2 = digitalRead(MODE_PIN_1); // Mode pin 2
    if (!input1 && !input2)
    {
        mode = MODE_MEASSURE;
    }
    else if (!input1 && input2)
    {
        mode = MODE_BALANCE;
    }
    else if (input1 && !input2)
    {
        mode = Mode_UNLOAD_75;
    }
    else // if (input1 && input2)
    {
        mode = Mode_UNLOAD_50;
    }

    return mode;
}
String Balancer::getModeString()
{
    const char* modes[] = {"MEASSURE", "BALANCE", "UNLOAD_75", "UNLOAD_50"};
    return String(modes[mode]);
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

float Balancer::getCellVoltage(byte cellIndex)
{
    if (cellIndex >= NUMBER_OF_CELLS)
    {
        Serial.println(F("Invalid cell index"));
        return 0.0; 
    }
    return cellVoltages[cellIndex];
}

void Balancer::setCellIndex(byte index)
{
    if (cellIndex >= NUMBER_OF_CELLS)
    {
        Serial.println(F("Invalid cell index"));
    }    
    cellIndex = index;
    Serial.print(F("New cell index: "));
    Serial.println(cellIndex);
    digitalWrite(pinArray[CELL_SELECT_INDEX], cellIndex == 1 ? LOW : HIGH); // select cell inverted logic
}

void Balancer::switchLoadResistor(bool state)
{
    isBalancing = state;                                           
    digitalWrite(pinArray[LOADRESISTOR_SELECT_INDEX], isBalancing); // select cell
    digitalWrite(LED_BUILTIN, isBalancing); //show on build led
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
    status = F("Balancer Mode: ");
    status += getModeString() + "\n";
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
    if (index >= NUMBER_OF_CELLS)
    {
        return F("Invalid cell index");
    }
    return String(cellVoltages[index]);
}

String Balancer::getDifferenceString()
{
    return String((int)voltageDiff/10*10); // rounded to 10mV
}