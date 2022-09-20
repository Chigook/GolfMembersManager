#include "Controller.h"
#include <iostream>

Controller::Controller()
{
    monitor = new Monitor();
}

Controller::~Controller()
{

}

void Controller::updateEvent(DeviceData data)
{
    std::cout << data.devName << " : ";
    for (const auto &data : data.devData){
        std::cout<< data << " "; //<< std::hex 넣으면 16진수
    }
    std::cout << std::endl;
}