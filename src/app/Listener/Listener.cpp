#include "Listener.h"

Listener::Listener(mfrc522 *rfid)
    : rfid(rfid) //초기화 1 //-> mfrc522 *rfid = rfid;
{
    // this->rfid = rfid; //초기화 2 //초기화 1이 더 좋은 방법
}

Listener::~Listener()
{

}

void Listener::checkEvent()
{
    //uint8_t byte;
    if(rfid->mfrc522_request(PICC_REQALL, rfidData) == CARD_FOUND){
        rfid->mfrc522_get_card_serial(rfidData);
        for(int i = 0; i <5; i++)
        printf("%02x", rfidData[i]);
    }
}