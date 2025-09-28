#pragma once
#include "24V-balancer.hpp"

class Balancer
{
    enum BalancerState
    {
        STATE_IDLE,
        STATE_BALANCING
    } ;

private:
    unsigned long startTime;       // Startzeitpunkt
    unsigned long lastBalanceTime; // Letzter Balancierzeitpunkt
    BalancerState balanceState;    // Status des Balancers

public:
    void setup();
    void cyclic();
};