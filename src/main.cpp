#include <iostream>
#include "mfrc522.h"
#include "Listener.h"

int main(void)
{
    mfrc522 rfid(new SPI(10, 3000000)); //SPI(pin number, 통신속도3MHz)
    Listener *listener = new Listener(&rfid);

    while (1)
    {
        listener->checkEvent();
        delay(1000);
        printf("hihi\n");
    }
}
