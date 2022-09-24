#include "Listener.h"

Listener::Listener(Controller *controller)
// : rfid(new CardReader(new SPI(10, 3000000))), controller(new Controller()) //초기화 1 //-> mfrc522 *rfid = rfid;
{
    rfid = new CardReader(new SPI(10, 3000000));
    // controller = new Controller();
    this->controller = controller;
    modeButton = new ManageButton(29, "ModeButton");
    manageButton = new ManageButton(28, "ManageButton");
    clockCheck = new ClockCheck("clockUpdate");
    piezo = new Piezo(6);
    // this->rfid = rfid; //초기화 2 //초기화 1이 더 좋은 방법
}

Listener::~Listener()
{

}

void Listener::checkEvent()
{
    if(checkRFID()){
        controller->updateEvent(rfid->getCardNumber());
    }
    if(modeButton->checkButton()){
        controller->updateEvent(modeButton->getButtonData());
    }
    if(manageButton->checkButton()){
        controller->updateEvent(manageButton->getButtonData());
    }

    if(clockCheck->isUpdate())
    {
        controller->updateEvent(clockCheck->getClockData());
    }
}

bool Listener::checkRFID()
{
    static unsigned int prevCheckTime = 0;
    if(millis() - prevCheckTime < 1000){
        return false;
    }
    prevCheckTime = millis();

    if(rfid->isCard()){
        piezo->Beep(3);
        return true;
    }
    return false;
}