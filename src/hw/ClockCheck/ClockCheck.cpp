#include "ClockCheck.h"

ClockCheck::ClockCheck(std::string state)
{
    prevSec = 0;
    clockData.devName = state;
}

ClockCheck::~ClockCheck()
{

}

bool ClockCheck::isUpdate()
{
    time_t curSec = time(NULL);
    if(curSec == prevSec){
        return false;
    }
    else{
        prevSec = curSec;
        return true;
    }
    return false;
}


DeviceData ClockCheck::getClockData()
{
    clockData.devData.clear();
    clockData.devData.push_back(1);

    return clockData;

}