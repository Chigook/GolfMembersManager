#ifndef MEMBERSMANAGESERVICE_H
#define MEMBERSMANAGESERVICE_H

#pragma once

#include <string>
#include <cstring>
#include "MembersEntity.h"
#include "MemberInfo.h"

enum {CARD_READER, CARD_REGISTER};

class MembersManageService
{
private:
    int membersManagerState;
    MembersEntity *membersEntity;

public:
    MembersManageService();
    ~MembersManageService();
    void updateStateEvent(std::string devName);
    void checkCardNumber(int *cardNum);
};

#endif