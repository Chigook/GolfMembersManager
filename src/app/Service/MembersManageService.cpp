#include "MembersManageService.h"
using namespace std;

MembersManageService::MembersManageService(ComDev *comDev, LCD *lcd)
{
    membersEntity = new MembersEntity();
    membersManagerState = CARD_READER;
    this->comDev = comDev;
    this->lcd = lcd;
    count = 100000;
    curTime = 0;
    buff[30] = {0,};
    wiringPiSetup();
}

MembersManageService::~MembersManageService()
{
}

void MembersManageService::updateStateEvent(std::string devName)
{
    
    switch(membersManagerState)
    {
        case CARD_READER :
            StateClock();
            if(devName == "ModeButton")
            {
                membersManagerState = CARD_REGISTER;
                printf("changed to CARD_REGISTER STATE\n");
            }
        break;

        case CARD_REGISTER :
            StateClock();
            if (devName == "ModeButton")
            {
                membersManagerState = LOOK_FOR_MEMEBER;
                printf("changed to LOOK_FOR_MEMEBER STATE\n");
            }

        break;

         case LOOK_FOR_MEMEBER :
            StateClock();
            if (devName == "ModeButton")
            {
                membersManagerState = DELETE_MEMBER;
                printf("changed to DELETE_MEMBER STATE\n");
            }

        break;

        case DELETE_MEMBER :
            if (devName == "ModeButton")
            {
                membersManagerState = CARD_READER;
                printf("changed to CARD_READER STATE\n");
            }
        break;
    }
}

void MembersManageService::checkCardNumber(int *cardNum)
{
    MemberInfo tempMember;
    switch(membersManagerState)
    {
        case CARD_READER :
            if(membersEntity->findMemberInfo(cardNum)){
                printf("Registered Member!:)\n");
                membersEntity->printMemberInfo(cardNum);
                comDev->sendData(cardNum);
            }
            else{
                printf("Not Registered Member!:(\n");
            }
        break;

        case CARD_REGISTER :
            tempMember.id = count;
            printf("이름을 입력하세요:");
            cin.getline(tempMember.name, 20, '\n');
            // scanf("%s", tempMember.name);
            printf("주소를 입력하세요:");
            cin.getline(tempMember.address, 40, '\n');
            // scanf("%s", tempMember.address);
            printf("연락처를 입력하세요(ex.010-0000-0000):");
            cin.getline(tempMember.phoneNumber, 15, '\n');
            // scanf("%s", &tempMember.phoneNumber);
            memcpy(tempMember.cardNum, cardNum, sizeof(tempMember.cardNum));
    
            membersEntity->addMemberInfo(tempMember);
            
            printf("Member Registered!:)\n");
            
            count++;

        break;

        case DELETE_MEMBER:
            if(membersEntity->delMemberInfo(cardNum)){
            comDev->sendData(cardNum);
            printf("Finished to delete a Member!:)\n");
            }
            else
            {
                printf("Can't delete a Member!:(\n");
            }
            break;
    }
}

void MembersManageService::ManageMember(std::string Name)
{
    MemberInfo tempMember;

    switch(membersManagerState)
    {

    case LOOK_FOR_MEMEBER:
        if (Name == "ManageButton")
        {
            printf("이름을 입력하세요:");
            cin.getline(tempMember.name, 20, '\n');
            if (membersEntity->findMemberInfo(tempMember.name))
            {
                membersEntity->printMemberInfo(tempMember.name);
                comDev->sendData(tempMember.name);
                printf("Finished to look for a Member!:)\n");
            }
            else
            {
                printf("Can't look for a Member!:(\n");
            }
        }
        break;

    case DELETE_MEMBER:
        if (Name == "ManageButton")
        {
            printf("이름을 입력하세요:");
            cin.getline(tempMember.name, 20, '\n');
            if (membersEntity->delMemberInfo(tempMember.name))
            {
                comDev->sendData(tempMember.name);
                printf("Finished to delete a Member!:)\n");
            }
            else
            {
                printf("Can't delete a Member!:(\n");
            }
        }
        break;
    }
}

void MembersManageService::StateLcd()
{
    // char buff[30];

    switch(membersManagerState)
    {
        case CARD_READER :
            sprintf(buff, " READER  ");
            lcd->WriteStringXY(0, 8, buff);
        break;

        case CARD_REGISTER :
            sprintf(buff, "REGISTER");
            lcd->WriteStringXY(0, 8, buff);
        break;

        case LOOK_FOR_MEMEBER :
            sprintf(buff, "LOOK_FOR");
            lcd->WriteStringXY(0, 8, buff);
        break;

        case DELETE_MEMBER :
            sprintf(buff, " DELETE ");
            lcd->WriteStringXY(0, 8, buff);
        break;
    }

}

void MembersManageService::StateClock()
{
    // char buff[30];
    curTime = time(NULL);
    struct tm *timeDate = localtime(&curTime);
    sprintf(buff, "%02d:%02d:%02d", timeDate->tm_hour, timeDate->tm_min, timeDate->tm_sec);
    lcd->WriteStringXY(0, 0, buff);
}