#include "server.h"
#pragma warning(disable:4996)

TCPserver::Server::Server(int port, std::string ipaddress)
{
	this->port = port;
	this->ipaddress = ipaddress;
	addrlength = sizeof(addr);
}

TCPserver::Server::~Server()
{
}

void TCPserver::Server::start()
{
	init();
	connect();
	while (true)
	{
		Sleep(5000);
		for (int i = 0; i < counter; i++)
		{
			Send(i);
		}
		
	}
}

void TCPserver::Server::init()
{
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ipaddress.c_str());

	if (WSAStartup(MAKEWORD(2, 1), &wsa) == SOCKET_ERROR)
	{
		std::cout << "Couldn't init WSA!";
		exit(EXIT_FAILURE);
	}

	serversocket = socket(AF_INET, SOCK_STREAM, NULL);
	bind(serversocket, (SOCKADDR*)&addr, addrlength);
	listen(serversocket, SOMAXCONN);
}

void TCPserver::Server::connect()
{
	SOCKET newConnection;
	newConnection = accept(serversocket, (SOCKADDR*)&addr, &addrlength);
	if (newConnection == 0)
	{
		std::cout << "Error to connect";
	}
	else
	{
		connections[counter] = newConnection;
		std::cout << "Client connected! \n";
		counter++;
	}
}

void TCPserver::Server::Send(int i)
{
	
	char msg[256] = "aaaaaaaaaaaaaaaaaaaaa";
	send(connections[i], msg, sizeof(msg), NULL);
}
