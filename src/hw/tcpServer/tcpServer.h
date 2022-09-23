#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#pragma once

class tcpServer
{
private:
    int serverSocket_fd;
    int clientSocket_fd;
    int portNum;
    bool clientState;

    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size;


public:
    tcpServer(int port);
    ~tcpServer();
    int getServerSocket();
    int getClientSocket();
    bool getClientState();
    void setClientState(bool state);
    void createSocket();
    int waitAccept();
    int recvData(char *recvBuff, size_t size);
    int sendData(char *sendBuff, size_t size);
    void closeSocket(int socket);
};

#endif