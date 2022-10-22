// base class for sending and receiving data
// uses loopback interface and TCP protocol by default
#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


class MySocket{
public:
	MySocket(int namespace_ = AF_INET, int style = SOCK_STREAM,//SOCK_STREAM = TCP
			int protocol = 0, uint16_t host = 4025);
	~MySocket ();
protected:
	int sockfd, sock = -1;
	int _namespace;
	int _style;
	int _protocol;
	uint16_t _host;
	struct sockaddr_in addr;
	bool receiveAll(const void* buf,
				const size_t& size, const int flags);
	bool sendAll(const void* buf,
				const size_t& size, const int flags);
};

