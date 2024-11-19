#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <netinet/in.h>

class Client
{
	int sockfd, port;
	struct sockaddr_in server_addr;
	bool isConnect;
protected:
	void logError(const char* msg);
public:
	Client();
	void connectTo(const sockaddr_in& server_addr);
	void sendMessage(const char* msg);
	~Client();
};

#endif // !_CLIENT_H_
