#ifndef LISTENER_H
#define LISTENER_H

#include <string.h>
#include "CardReader.h"
#include "Controller.h"
#include "Monitor.h"

class Listener
{
private:
    CardReader *rfid;
    Controller *controller;
    uint8_t rfidData[16];

public:
    Listener();
    ~Listener();
    void checkEvent();
    bool checkRFID();

};

#endif