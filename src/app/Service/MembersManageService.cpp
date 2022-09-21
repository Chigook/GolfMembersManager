#include "MembersManageService.h"

MembersManageService::MembersManageService()
{
    membersEntity = new MembersEntity();
    membersManagerState = CARD_READER;
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
            if(membersEntity->findMemberInfo(cardNum)){
                printf("Registered Member!:)\n");
                membersEntity->printMemberInfo(cardNum);
            }
            else{
                printf("Not Registered Member!:(\n");
            }
        break;

        case CARD_REGISTER :
            MemberInfo tempMember;
            tempMember.id = 100001;
            strcpy(tempMember.name, "LEEHYORYN");
            strcpy(tempMember.address, "101dong 123Ho");
            strcpy(tempMember.phoneNumber, "010-9876-5432");
            memcpy(tempMember.cardNum, cardNum, sizeof(tempMember.cardNum));
            
            membersEntity->addMemberInfo(tempMember);
            printf("Member Registered!:)\n");

        break;
    }
}