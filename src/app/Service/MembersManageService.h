#ifndef MEMBERSMANAGESERVICE_H
#define MEMBERSMANAGESERVICE_H

#pragma once

#include <string>
#include <cstring>
#include <vector>
#include "MembersEntity.h"
#include "MemberInfo.h"
#include "ComDev.h"
#include "LCD.h"

enum {CARD_READER, CARD_REGISTER};

class MembersManageService
{
private:
    MembersEntity *membersEntity;
    int membersManagerState;
    std::vector<MemberInfo> vecMembersList;
    int count;
    ComDev *comDev;
    // LCD *lcd;

public:
    MembersManageService(ComDev *comDev);
    ~MembersManageService();
    void updateStateEvent(std::string devName);
    void checkCardNumber(int *cardNum);
};

#endif