#include <iostream>
#include <thread>
#include <cstring>
#include <wiringPi.h>
#include "GolfMembershipManager.h"
#include "Listener.h"
#include "Controller.h"
#include "MembersManageService.h"
#include "MembersEntity.h"
#include "tcpServer.h"
#include "ComDev.h"
#include "I2C.h"
#include "LCD.h"
#include "ClockCheck.h"
#include "Piezo.h"
#include "ServoMotor.h"

void serverThread(tcpServer *server)
{
    char recvBuff[BUFSIZ];
    int recvLen;

    MembersEntity *membersEntity = new MembersEntity();
    ServoMotor *servomotor = new ServoMotor(0);

    while (server->waitAccept() > 0)
    {
        server->setClientState(true);
        while((recvLen = server->recvData(recvBuff, sizeof(recvBuff))) > 0)
        {
            if(membersEntity->findMemberInfo(recvBuff)){
                membersEntity->printMemberInfo(recvBuff);
            }
            if(strcmp(recvBuff, "open") == 0){
                servomotor->servomotor_open2sec();
            }
            recvBuff[recvLen] = '\0';
            server->sendData(recvBuff, recvLen);
            printf("received : %s\n", recvBuff);
        }
        server->closeSocket(server->getClientSocket());
        server->setClientState(false);
        printf("close client socket\n");
    }
}

int main(void)
{
    LCD lcd(new I2C("/dev/i2c-1", 0x27));
    tcpServer *cardTcpServer = new tcpServer(5100);
    ComDev *comDev = new ComDev(cardTcpServer);
    MembersManageService *memberManageservice = new MembersManageService(comDev, &lcd);
    Controller *controller = new Controller(memberManageservice);
    Listener *listener = new Listener(controller);

    std::thread threadFunc(serverThread, cardTcpServer);


    // GolfMembershipManager golfMembershipManager;
    // golfMembershipManager.run();

    while(1)
    {

        listener->checkEvent();
        memberManageservice->StateLcd();
    }
    
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