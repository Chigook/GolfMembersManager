#include "GolfMembershipManager.h"

GolfMembershipManager::GolfMembershipManager()
//mfrc522 *rfid = new mfrc522(new SPI(10, 3000000)) == SPI(pin number, 통신속도3MHz)
{
    // rfid = new mfrc522(new SPI(10, 3000000));
    // listener = new Listener();
    // this->listener = listener;
}

GolfMembershipManager::~GolfMembershipManager()
{

}

void GolfMembershipManager::run()
{
    while(1)
    {
        listener->checkEvent();
        delay(10);
    }
}