#ifndef COMDEV_H
#define COMDEV_H

#pragma once

#include "tcpServer.h"
#include <thread>

class ComDev
{
private:
    tcpServer *cardTcpServer;


public:
    ComDev(tcpServer *cardTcpServer);
    ~ComDev();
    void sendData(int *cardNum);


};

#endif