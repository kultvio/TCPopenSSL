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


namespace TCPserver
{

	class Client
	{
	private:
		WSADATA wsa;
		SOCKET Connection;
		std::string ipaddress;
		int port;
		char buffer[SIZE];
		std::string message;
		SOCKADDR_IN addr;
		int addrlength;
		int reclength;
	public:
		Client(int port, std::string ipaddress);
		~Client();
	public:
		void start();
		//void stop(); 
		void init();
		void connectToServer();
		void getMessage();

	};
}
