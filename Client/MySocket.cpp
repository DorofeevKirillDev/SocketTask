#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include "MySocket.h"



MySocket::MySocket(int namespace_ /*= AF_INET*/,
			int style /*= SOCK_STREAM*/,
			int protocol /*= 0*/, uint16_t host /*= 4025*/)
{
	_namespace = namespace_;
	_style = style;
	_protocol = protocol;
	_host = host;
	sockfd = socket(namespace_, style, protocol);//socket descriptor, using TCP
	if(sockfd < 0){
		perror("ERROR opening socket");
		exit(-1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(host);//some random port
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}

MySocket::~MySocket (){
	close(sockfd);
}

//receive hole message of size = size
bool MySocket::receiveAll(const void* buf,
					const size_t& size, const int flags)
{
	char* buffer = (char*)buf;
	size_t bytes_res= 0;
	size_t new_bytes = 0;
	while (bytes_res < size){
		new_bytes = recv(sock, buffer + bytes_res, size - bytes_res, 0);
		if (new_bytes <= 0 || new_bytes > size){//if there is some connection problem
			return 1;
		}
		bytes_res += new_bytes;
	}
	return 0;
}

//send hole message of size = size_
bool MySocket::sendAll(const void* buf,
		const size_t& size, const int flags)
{
	char* buffer = (char*)buf;
	size_t bytes_sent = 0;
	size_t new_bytes = 0;
	while (bytes_sent < size){
		new_bytes = send(sock, buffer + bytes_sent, size - bytes_sent, flags);
		if (new_bytes < 0 || new_bytes > size){//if there is some connection problem
			return 1;
		}
		bytes_sent += new_bytes;
	}
	return 0;
}
