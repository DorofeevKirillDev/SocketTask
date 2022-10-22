// program 2, receives data from program 1, checks whether it corresponds conditions or not
// if it corresponds, prints the data, prints "ERROR" otherwise
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "MySocketServer.h"


int main()
{
	MySocketServer mySocket;
	mySocket.receive();
    return 0;
}
