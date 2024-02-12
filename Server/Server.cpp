// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include "WinSock2.h"
#pragma warning(disable:4996)
int main()
{
    std::string ipaddress = "127.0.0.1";
    int port = 8888;
    WSADATA WSdata;
    if (WSAStartup(MAKEWORD(2, 1), &WSdata) == SOCKET_ERROR)
    {
        std::cout << "Couldn't init WSA!";
        return 1;
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr(ipaddress.c_str());
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeofaddr);
    listen(sListen, SOMAXCONN);

    SOCKET newConnetion;
    newConnetion = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

    if (newConnetion == 0)
    {
        std::cout << "Error conection";
    }
    else
    {
        std::cout << "Client connected! \n";
        char msg[256] = "aaaaaaaaaaaaaaaaaaaaa";
        send(newConnetion, msg, sizeof(msg), NULL);
    }



    return 0;
}

