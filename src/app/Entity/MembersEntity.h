#ifndef MEMBERSENTITY_H
#define MEMBERSENTITY_H

#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include "MemberInfo.h"
#include "LCD.h"

class MembersEntity
{
private:
    std::vector<MemberInfo> vecMembersList;     //vector의 자료 형태
    MemberInfo memberInfo;
    FILE *fpDBData;
    LCD *lcd;

public:
    MembersEntity();
    ~MembersEntity();
    void loadMembersInfo();
    void addMemberInfo(MemberInfo member);
    bool delMemberInfo(int *cardNum);
    void makeMemoryToDB();
    void printMemberInfo(int index);
    void printMemberInfo(std::string name);
    void printMemberInfo(int *cardNum);
    bool findMemberInfo(std::string name);
    bool findMemberInfo(int *cardNum);


};

#endif