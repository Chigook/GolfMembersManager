#ifndef CLOCKCHECK_H
#define CLOCKCHECK_H

#include <time.h>
#include <string>
#include "DeviceData.h"

#pragma once

class ClockCheck
{
private:
    time_t prevSec;
    DeviceData clockData;


public:
    ClockCheck(std::string state);
    ~ClockCheck();
    bool isUpdate();
    DeviceData getClockData();
};

#endif