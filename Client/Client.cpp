﻿#include <iostream>
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
    while (true)
    {
        sendPacket();
    }
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
    std::cout << "Connected to Server: Success. \n";
    HANDLE hThread = CreateThread(NULL, 0, ClientHandler, this, 0, NULL);

}

bool TCPserver::Client::ProcessPacket(Packet packetType)
{
    switch (packetType)
    {
    case P_ChatMessage:
        if (!processChatMessagePacket()) return false;
        break;
    default:
        return false;
        break;
    }
    return true;
}

bool TCPserver::Client::processChatMessagePacket()
{
    int msgSize;
    recv(Connection, (char*)&msgSize, sizeof(int), NULL);
    char* msg = new char[msgSize + 1];
    msg[msgSize] = '\0';
    recv(Connection, msg, msgSize, NULL);
    std::cout << "New message: ";
    std::cout << msg << "\n";

    delete[] msg;
    return true;
}


DWORD __stdcall TCPserver::Client::ClientHandler(LPVOID lpParam)
{
    Client* client = static_cast<Client*>(lpParam);
    while (true)
    {
        client->recieveMessage();
    }
    return 0;
}

void TCPserver::Client::recieveMessage()
{
    Packet packetType;
    recv(Connection, (char*)&packetType, sizeof(Packet), NULL);
    if (!ProcessPacket(packetType)) std::cout << "Failed to receive message" << std::endl;
}

bool TCPserver::Client::sendChatPacket()
{
    Packet packetType = P_ChatMessage;
    
    std::cout << "Enter a chat message: ";
    std::string msg;
    std::getline(std::cin, msg);
    int msgSize = msg.size();
    send(Connection, (char*)&packetType, sizeof(Packet), NULL);
    send(Connection, (char*)&msgSize, sizeof(int), NULL);
    send(Connection, msg.c_str(), msgSize, NULL);
    
    return true;
}

void TCPserver::Client::sendPacket()
{
    std::cout << "\nSelect packet type: " << std::endl;
    std::cout << "1: " << "Chat Message" << std::endl;
    
    int packetTypeIndex; 
    std::cin >> packetTypeIndex;
    std::cin.ignore();
    packetTypeIndex--;

    switch (packetTypeIndex)
    {
    case P_ChatMessage:
        sendChatPacket();
        break;
    default:
        std::cout << "Unknown packet type" << std::endl;
        break;
    }
    
}
