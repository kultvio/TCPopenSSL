#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include "WinSock2.h"
#include "Client.h"
#pragma warning(disable:4996)


TCPserver::Client::Client(int port, std::string ipaddress)
{
    this->port = port;
    this->ipaddress = ipaddress;
    addrlength = sizeof(addr);
}

TCPserver::Client::~Client()
{
}

void TCPserver::Client::start()
{
    init();
    connectToServer();
    getMessage();
}

void TCPserver::Client::init()
{
    if (WSAStartup(MAKEWORD(2, 1), &wsa) == SOCKET_ERROR)
    {
        std::cout << "Couldn't init WSA!";
        exit(EXIT_FAILURE);
    }
    addr.sin_addr.s_addr = inet_addr(ipaddress.c_str());
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
}

void TCPserver::Client::connectToServer()
{
    Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, addrlength) != 0)
    {
        std::cout << "Error: failed connect to server! \n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Connected to Server: Success.";

}

void TCPserver::Client::getMessage()
{
    while (true)
    {
        recv(Connection, buffer, sizeof(buffer), NULL);
        std::cout << buffer;
    }
}
