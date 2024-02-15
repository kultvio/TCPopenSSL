#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include "WinSock2.h"
#pragma warning(disable:4996)
int main()
{
    std::string ipaddress = "127.0.0.1";
    int port = 8288;
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

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if(connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0)
    {
        std::cout << "Error: failed connect to server! \n";
        return 1;
    }

    std::cout << "Connect success \n";
    char msg[256];
    while (true)
    {
        recv(Connection, msg, sizeof(msg), NULL);
        std::cout << msg;
    }
   
    

    system("pause");
    return 0;
}