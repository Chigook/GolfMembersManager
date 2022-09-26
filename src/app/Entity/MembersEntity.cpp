#include "MembersEntity.h"

MembersEntity::MembersEntity()
{
    loadMembersInfo();
    lcd = new LCD();
}

MembersEntity::~MembersEntity()
{

}

void MembersEntity::loadMembersInfo()
{
    fpDBData = fopen("memberLists.bin", "r");       //fopen : 해당 파일에 접근하겠다, r : read, w:write, r+:read/write
    if (fpDBData == NULL)
    {
        fprintf(stderr, "file open error!\n");
        return;
    }
    while (fread(&memberInfo, sizeof(MemberInfo), 1, fpDBData))     //memberInfo의 주소값, 사이즈, 1번 읽는다, fpDBData를->읽은 값만큼 return)
    {
        vecMembersList.push_back(memberInfo);
    }
    fclose(fpDBData);       //file 열고 항상 닫아주는 작업 필요
}

void MembersEntity::printMemberInfo(int index)
{
    if(index > (int)vecMembersList.size())
    {
        fprintf(stderr, "Out of Range member count!\n");
        return;
    }
    printf("%04d, %s, %s, %s, %0x-%0x-%0x-%0x-%0x\n",
    vecMembersList[index].id,
    vecMembersList[index].name,
    vecMembersList[index].address,
    vecMembersList[index].phoneNumber,
    vecMembersList[index].cardNum[0],
    vecMembersList[index].cardNum[1],
    vecMembersList[index].cardNum[2],
    vecMembersList[index].cardNum[3],
    vecMembersList[index].cardNum[4]);
}



void MembersEntity::printMemberInfo(std::string name)
{
    for(const auto &member : vecMembersList) {
        if(strcmp(member.name, name.c_str()) == 0)
        {
            printMemberInfo(member.id);
            return;
        }
    }
}

void MembersEntity::printMemberInfo(int *cardNum)
{
    for(const auto &member : vecMembersList) {
        if(memcmp (member.cardNum, cardNum, sizeof(member.cardNum)) == 0)
        {
            printf("%04d, %s, %s, %s, %0x-%0x-%0x-%0x-%0x\n",
                   member.id,
                   member.name,
                   member.address,
                   member.phoneNumber,
                   member.cardNum[0],
                   member.cardNum[1],
                   member.cardNum[2],
                   member.cardNum[3],
                   member.cardNum[4]);
            return;
        }
    }
}


bool MembersEntity::findMemberInfo(std::string name)
{

    for(const auto &member : vecMembersList) {
        if(strcmp(member.name, name.c_str()) == 0)
        {
            // printMemberInfo(member.id);
            return true;
        }
    }
    return false;
}

bool MembersEntity::findMemberInfo(int *cardNum)
{
    for(const auto &member : vecMembersList) {
        if(memcmp (member.cardNum, cardNum, sizeof(member.cardNum)) == 0)
        {
            return true;
        }
    }
    return false;
}

void MembersEntity::addMemberInfo(MemberInfo member)
{
    vecMembersList.push_back(member); //memory를 관리하는 vector(배열)의 맨 뒤쪽에 넣는 과정
}

bool MembersEntity::delMemberInfo(int *cardNum)
{
    // vecMembersList.clear() // erase all the elements
    // itrMember = vecMembersList.begin();     //vecMembersLists의 제일 앞(begin)의 주소를 itrMember에 삽입
    // itrMember = vecMembersList.end();    
    
    std::vector<MemberInfo>::iterator itrMember;

    for(itrMember = vecMembersList.begin(); itrMember != vecMembersList.end(); itrMember++)      //itrMember가 처음부터 vecMembersLists의 제일 뒤와 값이 같지 않으면 차례대로 증가한다
    {
        if (memcmp(itrMember->cardNum, cardNum, sizeof(itrMember->cardNum)) == 0)
        {
            vecMembersList.erase(itrMember);
            return true;
        }
    }
    return false;
}

bool MembersEntity::delMemberInfo(std::string name)
{
    std::vector<MemberInfo>::iterator itrMember;

    for(itrMember = vecMembersList.begin(); itrMember != vecMembersList.end(); itrMember++)      //itrMember가 처음부터 vecMembersLists의 제일 뒤와 값이 같지 않으면 차례대로 증가한다
    {
        if (strcmp(itrMember->name, name.c_str()) == 0)
        {
            vecMembersList.erase(itrMember);
            return true;
        }
    }
    return false;
}

void MembersEntity::makeMemoryToDB()
{
    /*
    file open
    vecMembersList의 배열을 하나씩 read
    vecMembersList값을 file에 vecMembersLists 끝까지 write
    file close
    */

    fpDBData = fopen("memberLists.bin", "w");       //fopen : 해당 파일에 접근하겠다, r : read, w:write, r+:read/write
    FILE *fpDBData2 = fopen("memberLists.txt", "w");
    if (fpDBData == NULL)
    {
        fprintf(stderr, "file open error!\n");
        return;
    }

    for(const auto &member : vecMembersList){
        fwrite(&member, sizeof(member), 1, fpDBData);     //memberInfo의 주소값, 사이즈, 1번 읽는다, fpDBData를->읽은 값만큼 return)
        fprintf(fpDBData2, "%05d, %s\n", member.id, member.name);
    }
    fclose(fpDBData);       //file 열고 항상 닫아주는 작업 필요
    fclose(fpDBData2);
}