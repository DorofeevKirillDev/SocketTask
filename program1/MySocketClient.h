// class for client side, receiving is not implemented
// example:
// 	MySocketClient mySocket;
// 	mySocket.connect_srv();
// 	std::queue<int> myQueue;
// 	myQueue.push(5);
// 	mySocket.send_queue(myQueue);
#pragma once
#include <queue>
#include "MySocket.h"

class MySocketClient: public MySocket{
public:
	MySocketClient();
	void connect_srv();//connect to server
	void send_queue(std::queue<int>&);
private:
	void reconnect_srv();
};
