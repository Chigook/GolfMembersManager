#ifndef LISTENER_H
#define LISTENER_H

#include <string.h>
#include "CardReader.h"
#include "Controller.h"
#include "Monitor.h"
#include "ManageButton.h"
#include "ClockCheck.h"
#include "Piezo.h"

class Listener
{
private:
    CardReader *rfid;
    ManageButton *modeButton;
    Controller *controller;
    uint8_t rfidData[16];
    ClockCheck *clockCheck;
    Piezo *piezo;

public:
    Listener(Controller *controller);
    ~Listener();
    void checkEvent();
    bool checkRFID();

};

#endif