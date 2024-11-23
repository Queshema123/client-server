#include "client.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#include <iostream>

Client::Client() :
	isConnect{false}, errors("", "client_errors")
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		logError("Can't create socket in Client");
		throw std::runtime_error("Can't create socket in Client");
	}
}

void Client::connectTo(const sockaddr_in& server_addr)
{
	if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		logError("Can't connect to Server in Client");
		isConnect = false;
		return;
	}
	isConnect = true;
}

void Client::connectTo(int family, int addr, int host_port)
{
	struct sockaddr_in server_addr;
	bzero((char*)&server_addr, sizeof(server_addr));
	server_addr.sin_family = family;
	server_addr.sin_addr.s_addr = family;
	server_addr.sin_port = htons(host_port);

	if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		logError("Can't connect to Server in Client");
		isConnect = false;
		return;
	}
	isConnect = true;
}

void Client::sendMessage(const char* msg)
{
	if (!isConnect)
		return;

	int n = write(sockfd, msg, strlen(msg));
	if (n < 0)
	{
		logError("Can't send message to Server in Client");
		return;
	}
}

Client::~Client()
{
	close(sockfd);
}

void Client::logError(const char* msg)
{
	errors.log(msg, Logger::Tag::Error);
}