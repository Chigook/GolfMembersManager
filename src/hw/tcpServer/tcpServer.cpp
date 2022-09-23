#include "tcpServer.h"

tcpServer::tcpServer(int port)
{
    portNum = port;
    clientState = false;
    createSocket();
}

tcpServer::~tcpServer()
{
    close(serverSocket_fd);
}

int tcpServer::getServerSocket()
{
    return serverSocket_fd;
}

int tcpServer::getClientSocket()
{
    return clientSocket_fd;
}

void tcpServer::createSocket()
{
     /* 서버 소켓 생성 */
    if((serverSocket_fd = socket(AF_INET, SOCK_STREAM,0)) < 0)        /* AF_INET : 인터넷, SOCK_STREAM : TCP, SOCK_DGRAM : UDP*/
    {
        perror("socket()");     /* perror : buffer를 거치지 않고 바로 화면에 출력하는 기능 */
        return;              /* return에서 0은 정상, 0이 아닌 값은 에러 */
    }

    /* Server 종료 후 OS가 일정시간 Server의 IP를 bind 진행(bind error를 띄우는 시간을 없애는 설정) */
    int option = 1;
    setsockopt(serverSocket_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));       /* bind없이 재사용 하겠다고 선언 */

    /* 주소 구조체에 주소 지정 */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;              /* 인터넷 */
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);       /* INADDR_ANY : 내가 갖고 있는 Local IP 모두 다 할당. all Local ip assign */
    serv_addr.sin_port = htons(portNum);        /* 사용할 포트번호 5100번 지정 */

    /* bind 함수를 사용하여 서버 소켓의 주소 설정 */
    if(bind(serverSocket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <0)
    {
        perror("bind()");
        return;
    }

    /* 동시에 접속하는 클라이언트의 처리를 위한 대기 큐를 설정*/
    if(listen(serverSocket_fd, 8) < 0)
    {
        perror("listen()");
        return;
    }
}

int tcpServer::waitAccept()
{
    char mesg[BUFSIZ];

    /* 클라이언트가 접속하면 접속을 허용하고 클라이언트 소켓 생성 */
    client_addr_size = sizeof(client_addr);
    clientSocket_fd = accept(serverSocket_fd, (struct sockaddr *)&client_addr, &client_addr_size);
    if (clientSocket_fd < 0)
    {
        perror("accept() error\n");
        return -1;
    }

    /* 네트워크 주소를 문자열로 변경 */
    inet_ntop(AF_INET, &client_addr.sin_addr, mesg, BUFSIZ); /* inet_ntop : network을 문자열로 변경 시킨다 */
    printf("Client is connected : %s\n", mesg);

    return clientSocket_fd;
}

int tcpServer::recvData(char *recvBuff, size_t size)
{
    int len = read(clientSocket_fd, recvBuff, size);
    return len;
}

int tcpServer::sendData(char *sendBuff, size_t size)
{
    if(!getClientState()){
        return -1;
    }

    int len = write(clientSocket_fd, sendBuff, size);
    return len;
}

void tcpServer::closeSocket(int socket)
{
    close(socket);
}

bool tcpServer::getClientState()
{
    return clientState;
}

void tcpServer::setClientState(bool state)
{
    clientState = state;
}