#include "Controller.h"
#include <iostream>

Controller::Controller(MembersManageService *membersManageService)
{
    monitor = new Monitor();
    // membersManageService = new MembersManageService();
    this->membersManageService = membersManageService;
    
}

Controller::~Controller()
{

}

void Controller::updateEvent(DeviceData data)
{
    if(data.devName == "CardReader"){
        int cardNumber[5];
        for(int i =0; i < 5; i++)
        {
            cardNumber[i] = data.devData[i];
        }
        membersManageService->checkCardNumber(cardNumber);
    }
    if(data.devName == "ManageButton"){
        membersManageService->ManageMember("ManageButton");
    }
    if (data.devName == "ModeButton"){
        membersManageService->updateStateEvent("ModeButton");
    }
    if(data.devName == "clockUpdate"){
        membersManageService->updateStateEvent("clockUpdate");
    }
}