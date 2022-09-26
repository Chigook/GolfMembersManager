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
#include "ServoMotor.h"

enum {CARD_READER, CARD_REGISTER, LOOK_FOR_MEMEBER, DELETE_MEMBER};

class MembersManageService
{
private:
    MembersEntity *membersEntity;
    std::vector<MemberInfo> vecMembersList;
    ComDev *comDev;
    LCD *lcd;
    ServoMotor *servomotor;
    int membersManagerState;
    int count;
    time_t curTime;
    char buff[30];


public:
    MembersManageService(ComDev *comDev, LCD *lcd);
    ~MembersManageService();
    void updateStateEvent(std::string devName);
    void checkCardNumber(int *cardNum);
    void ManageMember(std::string Name);
    void StateLcd();
    void StateClock();
};

#endif