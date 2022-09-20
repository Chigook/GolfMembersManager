#ifndef CONTROLLER_H
#define CONTROLLER_H

#pragma once
#include "Monitor.h"
#include "DeviceData.h"

class Controller
{
private:
    Monitor *monitor;

public:
    Controller();
    ~Controller();
    void updateEvent(DeviceData data);


};

#endif