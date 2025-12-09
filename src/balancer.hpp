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
        STATE_MEASSURE_0,
        STATE_MEASSURE_1,
        STATE_BALANCING_0,
        STATE_BALANCING_1
    };

private:
    BalancerState balanceState;          // Status des Balancers
    float cellVoltages[NUMBER_OF_CELLS]; // Array für Zellenspannungen
    byte cellIndex;                      // Index der aktuellen Zelle
    void setCellIndex(byte index);
    void switchLoadResistor(bool state);

    bool calculateBalanceNeeded(byte index1, byte index2);

    bool isBalancing = false; // Status, ob gerade balanciert wird

    float readAnalogInput(); // Read the analog input voltage in Volts

    bool updateDisplay = false; // only set when display should be updated

    float voltageDiff = 0.0; // voltage difference between cells

    unsigned long startTime = 0;       // time when balancer started
    unsigned long lastMeasureTime = 0; // time when last meassurment was done
    long elapsedTime = 0;              // time in state
    unsigned long lastBalanceTime = 0; // last time balancing started

public:
    void setup();
    void cyclic();

    float getCellVoltage(byte cellIndex); // Abrufen der Zellenspannung
    void printLineStatus();               // Gesamt Status als String aus Serial ausgeben
    String getBalancingMode();
    String getState();                       // Status als String
    String getCellVoltageString(byte index); // Zellenspannungen als String
    bool getUpdateDisplay() const { return updateDisplay; }
    void setUpdateDisplay(bool value) { updateDisplay = value; }
    String getDifferenceString();
    String getElapsedTimeString() { return (String(elapsedTime)); };
};

extern Balancer balancer;
