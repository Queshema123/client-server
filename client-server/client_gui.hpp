#include <iostream> 
#include "client.h"
#include <sys/types.h>
#include <sys/socket.h>

void start()
{
	Client client;
	client.connectTo(AF_INET, INADDR_ANY, 9090);
	std::string msg;
	while (std::cin)
	{
		std::cout << '>';
		std::getline(std::cin, msg);
		std::cout << '>' << client.sendMessage(msg.c_str()) << '\n';
	}
}