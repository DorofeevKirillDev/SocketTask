#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "MySocketServer.h"

MySocketServer::MySocketServer(){
	sock = sockfd;
	while (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0){// if the port is busy
			sleep(1);// waiting for socket
	}
	sock = connect_cl();
}

MySocketServer::~MySocketServer(){
	close(sock);
}

// connect to client, also for reconnection
int MySocketServer::connect_cl()
{
	int new_sock;
	if (listen(sockfd, SOMAXCONN) == -1){
		perror("listen ERROR");
		exit(2);
	}
	if ((new_sock = accept(sockfd, NULL, NULL)) == -1){
		perror("accept ERROR");
		exit(3);
	}
	return new_sock;
}

void MySocketServer::receive()
{
	char message[message_size];
	while (1)
		{
			while (receiveAll(message, message_size, 0)){// if there is some connection problem
				sleep(1);
				sock = connect_cl();
			}
			printResult(std::string(message, 0, message_size));
		}
}

void MySocketServer::printResult(const std::string result) const
{
	unsigned long long res = std::stoi(result);
	if ((res > 99) && (res % 32) == 0){
		std::cout << "Received value: " << res << std::endl;
	}
	else{
		std::cout << "ERROR"<< std::endl;
	}
}
