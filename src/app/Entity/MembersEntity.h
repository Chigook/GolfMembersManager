#ifndef MEMBERSENTITY_H
#define MEMBERSENTITY_H

#pragma once

#include <vector>
#include <iostream>
#include "MemberInfo.h"

class MembersEntity
{
private:
    std::vector<MemberInfo> vecMembersList;     //vector의 자료 형태
    MemberInfo memberInfo;
    FILE *fpDBData;

public:
    MembersEntity();
    ~MembersEntity();
    void loadMembersInfo();
    // void addMemberInfo(MemberInfo member);
    // void delMemberInfo(MemberInfo member);
    // void makeDBMembersInfo();
void printMemberInfo();


};

#endif