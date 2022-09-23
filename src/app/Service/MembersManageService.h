#ifndef MEMBERSMANAGESERVICE_H
#define MEMBERSMANAGESERVICE_H

#pragma once

#include <string>
#include <cstring>
#include <vector>
#include <wiringPi.h>
#include <iostream>
#include "MembersEntity.h"
#include "MemberInfo.h"
#include "ComDev.h"
#include "LCD.h"

enum {CARD_READER, CARD_REGISTER};

class MembersManageService
{
private:
    MembersEntity *membersEntity;
    std::vector<MemberInfo> vecMembersList;
    ComDev *comDev;
    LCD *lcd;
    int membersManagerState;
    int count;
    time_t curTime;
    char buff[30];

public:
    MembersManageService(ComDev *comDev, LCD *lcd);
    ~MembersManageService();
    void updateStateEvent(std::string devName);
    void checkCardNumber(int *cardNum);
    void StateLcd();
    void StateClock();
};

#endif