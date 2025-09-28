#include "balancer.hpp"
#include "Arduino.h"

void Balancer::setup() {
    // Initialisierungscode hier einfügen
    startTime = millis();
    lastBalanceTime = startTime;
    balanceState = STATE_IDLE;
}

void Balancer::cyclic() {
    // Zyklischer Code hier einfügen
    unsigned long currentTime = millis();
    long elapsedTime = ((long)currentTime - lastBalanceTime) / 1000; // in Sekunden
    if (elapsedTime >= cycleTime) {
        lastBalanceTime = currentTime;
        // Hier den Balanciercode einfügen
        // Zum Beispiel: balanceCells();
        Serial.println("Balancing cells..."); // Platzhalter-Ausgabe

    }
    //Serial.println("Balancer cyclic check at " + String(elapsedTime) + " seconds");
}