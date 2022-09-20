#include <iostream>
#include "mfrc522.h"
#include "Listener.h"
#include "GolfMembershipManager.h"
#include "MembersEntity.h"

int main(void)
{
    // GolfMembershipManager golfMembershipManager;
    // golfMembershipManager.run();
    MembersEntity membersEntity;

    return 0;
}
/*














    mfrc522 rfid(new SPI(10, 3000000)); //SPI(pin number, 통신속도3MHz)
    Listener *listener = new Listener(&rfid);

    while (1)
    {
        listener->checkEvent();
        delay(1000);
        printf("hihi\n");
    }
}
*/