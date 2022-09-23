#include "MembersManageService.h"
using namespace std;

MembersManageService::MembersManageService(ComDev *comDev, LCD *lcd)
{
    membersEntity = new MembersEntity();
    membersManagerState = CARD_READER;
    count = 10000;
    this->comDev = comDev;
    this->lcd = lcd;
    curTime = 0;
    wiringPiSetup();
    buff[30] = {0,};
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
                membersManagerState = CARD_READER;
                printf("changed to CARD_READER STATE\n");
            }

        break;
    }
}

void MembersManageService::checkCardNumber(int *cardNum)
{
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
            MemberInfo tempMember;
            tempMember.id = count;
            printf("이름을 입력하세요:");
            cin.getline(tempMember.name, 20, '\n');
            // scanf("%s", tempMember.name);
            printf("주소를 입력하세요:");
            cin.getline(tempMember.address, 40, '\n');
            // scanf("%s", tempMember.address);
            printf("연락처를 입력하세요:");
            cin.getline(tempMember.phoneNumber, 15, '\n');
            // scanf("%s", &tempMember.phoneNumber);
            memcpy(tempMember.cardNum, cardNum, sizeof(tempMember.cardNum));
    
            membersEntity->addMemberInfo(tempMember);
            
            printf("Member Registered!:)\n");
            
            count++;

        break;
    }
}

void MembersManageService::StateLcd()
{
    // char buff[30];

    switch(membersManagerState)
    {
        case CARD_READER :
            sprintf(buff, "CARD_READER     ");
            lcd->WriteStringXY(0, 0, buff);
        break;

        case CARD_REGISTER :
            sprintf(buff, "CARD_REGISTER   ");
            lcd->WriteStringXY(0, 0, buff);
        break;
    }

}

void MembersManageService::StateClock()
{
    // char buff[30];
    curTime = time(NULL);
    struct tm *timeDate = localtime(&curTime);
    sprintf(buff, "%02d:%02d:%02d", timeDate->tm_hour, timeDate->tm_min, timeDate->tm_sec);
    lcd->WriteStringXY(1, 0, buff);
}