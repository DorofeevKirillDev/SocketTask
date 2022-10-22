// provides parallel execution of two functions (getCin and getBuf)
// solves producer-consumer problem by using semaphores
// example:
// 	Parallel myParallel;
// 	myParallel.createThreads();
#pragma once
#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include "MySocketClient.h"

class Parallel{
public:
	Parallel();
	~Parallel();
	void createThreads();
private:
	std::string buffer;
	std::queue<int> sum_buffer;
	pthread_t thr_put;
	pthread_t thr_get;
	sem_t sem_put;
	sem_t sem_get;
	sem_t sem_mutex;//semaphore for mutual exclusion
	MySocketClient mySocket;
	std::string new_str;

	void parseInput();
	static void* _start_getCin(void*);
	static void* _start_getBuf(void*);
	void getCin();//get data from cin
	void getBuf();//get string from buffer
	int getSum(std::string);
	void sendSum();//send sum to program 2
	bool _is_digit(std::string) const;

};




