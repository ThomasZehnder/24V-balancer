#pragma once
#include "24V-balancer.hpp"

const int NUMBER_OF_CELLS = 2;           // Anzahl der Zellen
const int CELL_SELECT_INDEX = 1;         // Pin zum Auswählen der Zelle
const int LOADRESISTOR_SELECT_INDEX = 2; // Pin zum Schalten des Lastwiderstands

enum BalancerMode
{
    MODE_MEASSURE,
    MODE_BALANCE,
    Mode_UNLOAD_75,
    Mode_UNLOAD_50
};

#define VOLTAGELIMIT_75 13.10f // Voltage limit for 75% unload
#define VOLTAGELIMIT_50 13.00f // Voltage limit for 50% unload
#define VOLTAGELIMIT_25 12.80f // Voltage limit for 25% unload


class Balancer
{
    enum BalancerState
    {
        STATE_IDLE,
        STATE_MEASSURE_0,
        STATE_MEASSURE_1,
        STATE_DISCHARGE_0,
        STATE_DISCHARGE_1
    };

private:
    BalancerState balanceState;          // Status des Balancers
    float cellVoltages[NUMBER_OF_CELLS]; // Array für Zellenspannungen
    byte cellIndex;                      // Index der aktuellen Zelle
    void setCellIndex(byte index);
    void switchLoadResistor(bool enable = true);

    bool calculateBalanceNeeded(byte index1, byte index2);

    bool isBalancing = false; // Status, ob gerade balanciert wird

    float readAnalogInput(); // Read the analog input voltage in Volts

    BalancerMode mode = MODE_MEASSURE;

    BalancerMode readModeInputs();

    bool voltagesUpperLimit(float limitVoltage);
    float voltageLimit = 0.0f;

    bool updateDisplay = false; // only set when display should be updated

    float voltageDiff = 0.0; // voltage difference between cells

    unsigned long startTime = 0;       // time when balancer started
    unsigned long lastMeasureTime = 0; // time when last meassurment was done
    long elapsedTime = 0;              // time in state
    unsigned long lastBalanceTime = 0; // last time balancing started

public:
    void setup();
    void cyclic();

    BalancerMode getMode();
    String getModeString();

    float getCellVoltage(byte cellIndex); // Abrufen der Zellenspannung
    void printLineStatus();               // Gesamt Status als String aus Serial ausgeben
    String getBalancingMode();
    String getState();                       // Status als String
    String getCellVoltageString(byte index); // Zellenspannungen als String
    bool getUpdateDisplay() const { return updateDisplay; }
    void setUpdateDisplay(bool value) { updateDisplay = value; }
    String getDifferenceString();
    String getCycleTimeString() { return (String(cycleTime)); };
    String getElapsedTimeString() { return (String(elapsedTime)); };
    String getVoltageLimitString() { return String(voltageLimit, 2); };
};

extern Balancer balancer;
