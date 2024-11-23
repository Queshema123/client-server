#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <netinet/in.h>

#include "logger.h"

class Client
{
	int sockfd;
	struct sockaddr_in server_addr;
	bool isConnect;
	Logger errors;
protected:
	void logError(const char* msg);
public:
	Client();
	void connectTo(const sockaddr_in& server_addr);
	void connectTo(int family, int addr, int host_port);
	void sendMessage(const char* msg);
	~Client();
};

#endif // !_CLIENT_H_
