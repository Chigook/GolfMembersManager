#ifndef COMDEV_H
#define COMDEV_H

#pragma once

#include "tcpServer.h"
#include <string>
#include <cstring>
#include <thread>

class ComDev
{
private:
    tcpServer *cardTcpServer;


public:
    ComDev(tcpServer *cardTcpServer);
    ~ComDev();
    void sendData(int *cardNum);
    void sendData(std::string Name);
    void writeData(std::string Name);


};

#endif