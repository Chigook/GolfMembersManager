#ifndef CONTROLLER_H
#define CONTROLLER_H

#pragma once
#include "Monitor.h"
#include "DeviceData.h"
#include "MembersManageService.h"

class Controller
{
private:
    Monitor *monitor;
    MembersManageService *membersManageService;

public:
    Controller(MembersManageService *membersManageService);
    ~Controller();
    void updateEvent(DeviceData data);

};

#endif