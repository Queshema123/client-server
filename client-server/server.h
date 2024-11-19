#ifndef _SERVER_H_
#define _SERVER_H_

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <vector>
#include <thread>

class Server
{
	int sockfd, port, clients_cnt;
	struct sockaddr_in server_addr;
	bool isListen;
	std::vector<std::thread> thread_pool;
protected:
	void addMessage(const char* msg);
	void logError(const char* msg);
	void clientInteraction(int client_socket);
public:
	Server();
	void start();
	void end();
	inline const sockaddr_in& getServerAdress() { return server_addr; }
	~Server();
};

#endif // !_SERVER_H_
