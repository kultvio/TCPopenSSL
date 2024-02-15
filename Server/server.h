#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <WinSock2.h>
#include <unordered_map>
#include <string>
#include <cassert>
#pragma comment(lib, "ws2_32.lib")
#define SIZE 1024
#define MAX_CONNECTIONS 100

namespace TCPserver
{
	class Server
	{
	private:
		WSADATA wsa;
		SOCKET serversocket;
		SOCKET connections[MAX_CONNECTIONS];
		int counter = 0;
		std::string ipaddress;
		int port;
		char buffer[SIZE];
		std::string message;
		SOCKADDR_IN addr;
		int addrlength;
		int reclength;
	public:
		Server(int, std::string);
		~Server();
	public:
		void start();
		//void stop(); 
		void init();
		void connect();
		void Send(int i);
	};
}

