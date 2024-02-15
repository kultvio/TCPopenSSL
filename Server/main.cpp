// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//



#include "server.h"

int main()
{
    TCPserver::Server server(8288, "127.0.0.1");
    server.start();

    return 0;
}

