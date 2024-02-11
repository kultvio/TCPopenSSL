// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include "WinSock2.h"
int main()
{
    WSADATA WSdata;
    if (WSAStartup(MAKEWORD(2, 2), &WSdata) == SOCKET_ERROR)
    {
        std::cout << "Couldn't init WSA!";
        return 1;
    }
    
    return 0;
}

