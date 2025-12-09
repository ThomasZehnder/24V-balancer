# 24V-Balancer

24 Volt lifepo balancer for two 12 Volt batteries.

Arduino UNano V3.0 with OLED display.

DC/DC converter 24V /5V galvanic separated

## IOs

| Component | Pin | Function | (test board)
|-----------|-----|----------|-----------
| Switch 1 | D11 | Mode Switch Pull Up 1| Key left
| Switch 2 | D12 | Mode Switch Pull Up 1| Key right
| Relay 1 | D5 | Switch between battery 1 and 2 | red led
| Relay 2 | D6 | Turn on load (external pin) | yellow led
| Analog In | A0 | Voltage measurement | poti
| OLED SLC | A5 | OLED SLC | OLED SLC
| OLED SDA | A4 | OLED SDA | OLED SDA

## Mode

| Switch 1| Switch 2| Function
|-----------|-----|----------
| OFF | OFF | Voltage measurement
| ON  | OFF | Balance
| OFF | ON  | Discharge to 75%
| ON  | ON  | Discharge to 50%

## Analog in

    Battery Mesasure = A0 

    Resistor 1k/2k --> 15V --> 5V

## Quick Reference Table Votages

| State of Charge | Approx. Voltage (Resting)
|-----------|-----
| 100% | 13.4–13.6 V
| 90%  | 13.3 V
| 75%  | 13.1–13.2 V
| 50%  | ~13.0 V
| 25%  | 12.8–12.9 V
| 0% (usable) | ≈ 12.0–12.2 V
| BMS shutdown | 10.5–11.0 V (under load)

## Serial Settings

115200 Baud

## REPO

<https://github.com/ThomasZehnder/24V-balancer>
