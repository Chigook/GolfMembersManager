#include "MembersManageService.h"

MembersManageService::MembersManageService(ComDev *comDev)
{
    membersEntity = new MembersEntity();
    membersManagerState = CARD_READER;
    count = 100001;
    this->comDev = comDev;
    // lcd = new LCD();
}

MembersManageService::~MembersManageService()
{
}

void MembersManageService::updateStateEvent(std::string devName)
{
    switch(membersManagerState)
    {
        case CARD_READER :
            if(devName == "ModeButton")
            {
                membersManagerState = CARD_REGISTER;
                printf("changed to CARD_REGISTER STATE\n");
            }
        break;

        case CARD_REGISTER :
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
            // lcd->WriteStringXY(0, 0, "CARD_READER     ");
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
            // lcd->WriteStringXY(0, 0, "CARD_REGISTER   ");
            MemberInfo tempMember;
            tempMember.id = count;
            printf("이름을 입력하세요:");
            scanf("%s", &tempMember.name);
            printf("주소를 입력하세요:");
            scanf("%s", &tempMember.address);
            printf("연락처를 입력하세요:");
            scanf("%s", &tempMember.phoneNumber);
            memcpy(tempMember.cardNum, cardNum, sizeof(tempMember.cardNum));
    
            membersEntity->addMemberInfo(tempMember);
            printf("Member Registered!:)\n");
            count++;

        break;
    }
}