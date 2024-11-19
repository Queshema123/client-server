#include "server.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include <stdexcept>
#include <iostream>

Server::Server() :
	clients_cnt{ 5 }, port{ 9090 }, isListen{ false }
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		logError("Can't create socket in Server");
		throw std::runtime_error("Can't create socket in Server");
	}
	bzero((char*)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		logError("Can't bind socket and server in Server");
		throw std::runtime_error("Can't bind socket and server in Server");
	}
}

void Server::start()
{
	isListen = true;

	while (isListen)
	{
		struct sockaddr_in cli_addr;
		listen(sockfd, clients_cnt);
		socklen_t clilen{ sizeof(cli_addr) };
		int newsocfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
		if (newsocfd < 0)
		{
			logError("Can't accept client in Server::start");
			continue;
		}
		std::thread client_connection(&Server::clientInteraction, this, newsocfd);
		thread_pool.push_back(std::move(client_connection));
	}
	
}

void Server::end()
{
	isListen = false;
}

Server::~Server()
{
	close(sockfd);
}

void Server::addMessage(const char* msg)
{
	std::cout << msg << '\n';
}

void Server::logError(const char* msg)
{
	std::cerr << msg << '\n';
}

void Server::clientInteraction(int client_socket)
{
	constexpr int size{ 256 };
	char buff[size];
	int readed_bytes{ read(client_socket, buff, size) };
	while (readed_bytes > 0 && client_socket > 0 && isListen)
	{
		addMessage(buff);
		bzero(buff, size);
		readed_bytes = read(client_socket, buff, size);
	}
	close(client_socket);
}