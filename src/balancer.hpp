#pragma once
#include "24V-balancer.hpp"

class Balancer
{
    enum BalancerState
    {
        STATE_IDLE,
        STATE_BALANCING
    };

private:
    unsigned long startTime;       // Startzeitpunkt
    unsigned long lastBalanceTime; // Letzter Balancierzeitpunkt
    unsigned long lastMeasureTime; // Letzter Messzeitpunkt 
    BalancerState balanceState;    // Status des Balancers
    float cellVoltages[2];         // Array für Zellenspannungen
    byte cellIndex;              // Index der aktuellen Zelle


public:
    void setup();
    void cyclic();
    int readAnalogInput(); // Renamed from readAnalogInputs to readAnalogInput

    float getCellVoltage(int cellIndex); // Beispielmethode zum Abrufen der Zellenspannung
};