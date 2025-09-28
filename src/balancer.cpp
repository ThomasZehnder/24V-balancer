#include "balancer.hpp"
#include "Arduino.h"

#define ANALOG_INPUT_PIN A0 // Define the analog input pin

void Balancer::setup() {
    // Initialisierungscode hier einfügen
    startTime = millis();
    lastBalanceTime = startTime;
    lastMeasureTime = startTime; // Mess-Timer initialisieren
    balanceState = STATE_IDLE;
    cellIndex = 0;
    cellVoltages[0] = 0.0;
    cellVoltages[1] = 0.0;
}

void Balancer::cyclic() {
    // Zyklischer Code hier einfügen
    unsigned long currentTime = millis();

        // Mess-Timer: alle 1 Sekunde
    if (currentTime - lastMeasureTime >= 1000) {
        lastMeasureTime = currentTime;
        cellVoltages[cellIndex] = readAnalogInput();
    }

    long elapsedTime = ((long)currentTime - lastBalanceTime) / 1000; // in Sekunden
    if (elapsedTime >= cycleTime) {
        lastBalanceTime = currentTime;
        Serial.println("Balancing cells..."); // Platzhalter-Ausgabe
        
    }
}

int Balancer::readAnalogInput() {
    int value = analogRead(ANALOG_INPUT_PIN);
    float voltage = (value / 1023.0) * 15.0; // Annahme: 5V Referenzspannung mit Spannungsteiler 1/3
    Serial.print("Analog A0: ");
    Serial.print(voltage);
    Serial.println("V");
    return voltage;
}