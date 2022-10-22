#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include "MySocketClient.h"

MySocketClient::MySocketClient(){
	sock = sockfd;
}

void MySocketClient::connect_srv(){
	connect(sock, (struct sockaddr *) &addr, sizeof(addr));
}

// if there is some problem with program 2 (server),creats new socket
void MySocketClient::reconnect_srv()
{
	close(sock);
	sock = socket(_namespace, _style, _protocol);
	connect(sock, (struct sockaddr*) &addr, sizeof(addr));
}

void MySocketClient::send_queue(std::queue<int>& sum_buffer)
{
	while (!sum_buffer.empty())
	{
		const unsigned int size_ = 3;//max sum of string = 9*64 = 576
		char sum_cstr[size_];//c string that contains the value of sum
		std::string sum_str;
		unsigned int sum_str_size;
		sum_str = std::to_string(sum_buffer.front());
		sum_str_size = sum_str.size();
		strcpy(sum_cstr, (sum_str).c_str());
		memset(sum_cstr + sum_str_size, '\0', size_ - sum_str_size);// the value of sum and null terminators
		if (sendAll(sum_cstr, size_, 0) == 1){//if there is some connection problem
			reconnect_srv();
			return;
		}
		else{
			sum_buffer.pop();
		}
	}
}

