// program 1
// uses 2 threads (besides the main one): the first one gets data from cin and parse it,
// the second one sends a sum of numbers in string after parsing to program 2
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "MySocketClient.h"
#include "Parallel.h"



int main()
{
	Parallel myParallel;
	myParallel.createThreads();
    return 0;
}

