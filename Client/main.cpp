#include "Client.h"

int main()
{
	TCPserver::Client client(8288, "127.0.0.1");
	client.start();
	return 0;
}