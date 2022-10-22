// server side, sending is not implemented
// example:
//	MySocketServer mySocket;
//	mySocket.receive();
#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "MySocket.h"

class MySocketServer: public MySocket{
public:
	MySocketServer();//creates server socket
	~MySocketServer();
	void receive();//massage is an array of size = message_size
	void printResult(const std::string result) const;
private:
	const size_t message_size = 3;
	int connect_cl();//connect to client, also for reconnection
};
