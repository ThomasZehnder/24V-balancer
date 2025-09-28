#pragma once
#include "24V-balancer.hpp"

const int NUMBER_OF_CELLS = 2;           // Anzahl der Zellen
const int CELL_SELECT_INDEX = 1;         // Pin zum Auswählen der Zelle
const int LOADRESISTOR_SELECT_INDEX = 2; // Pin zum Schalten des Lastwiderstands

class Balancer
{
    enum BalancerState
    {
        STATE_IDLE,
        STATE_BALANCING_0,
        STATE_BALANCING_1
    };

private:
    unsigned long startTime;             // Startzeitpunkt
    unsigned long lastBalanceTime;       // Letzter Balancierzeitpunkt
    unsigned long lastMeasureTime;       // Letzter Messzeitpunkt
    BalancerState balanceState;          // Status des Balancers
    float cellVoltages[NUMBER_OF_CELLS]; // Array für Zellenspannungen
    byte cellIndex;                      // Index der aktuellen Zelle
    void incrementCellIndex();
    void switchLoadResistor(bool state);

public:
    void setup();
    void cyclic();
    int readAnalogInput(); // Renamed from readAnalogInputs to readAnalogInput

    float getCellVoltage(int cellIndex); // Beispielmethode zum Abrufen der Zellenspannung
};