# 24 V Balancer (2x12V)
Arduino UNano V3.0 mit OLED display
DC/DC Wandler 24V /5V galvanisch getrennt.

<img src="images/arduino-serial-ui.jpg" alt="arduino-ui-test-board" width="400"/>




## Verbindung über Console 

### Debuggen
UART Settings: 115200 Baud, SERIAL_8N1 (the default)


# Serial Kommandos
## Auswahl Modus



    0,1,2,3 = select led, command is modal
    x = off
    o = on

    f = flash sequence 10 times fast (only for test usefull)

    h = this help

    s [0-9] /CR/LF = set hysterese in mV

## Setzen der Hysterese


## Display Commands
To access the display to send texts to the display start with '@', this will forward all characters to the display.  
With '#' and '|' you can change between small an big font.  
'&' will clear the display.  
To switch back to control the led use '^'.   

    ^ = switch to led command
    @ = switch to oled output
    # = big font
    | = small font
    & = clear display
    \ = new line
    


  
# Wiring
## led's
    Led0 = BUILD IN LED
    Led1 = D5
    Led2 = D6
    Led3 = D7

## key's
    Key0 = 11; //D11;
    Key1 = 12; //D12;

## OLED Display Wiring
### ESP8266
> NodeMCU 1.0  
> Flash Size: 4M(3M SPIFFS)  

    I2C Bus:
    SCK = D1 = GPIO 5
    SDA = D2 = GPIO 4

### Arduino Nano
> Old Boot loader !!!  
> "board": "arduino:avr:nano"  
> "configuration": "cpu=atmega328old"  

    I2C Bus:
    SDA = A4
    SCL = A5




# TIPS for beginners
## work with GIT
    push --> commit to GIT   
    pull --> get from GIT

use commandos in VScode :-)
