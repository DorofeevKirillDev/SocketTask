#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <queue>
#include <string>
#include "Parallel.h"
#include "MySocketClient.h"

Parallel::Parallel()
{
	sem_init(&sem_put, 0, 1);
	sem_init(&sem_get, 0, 0);
	sem_init(&sem_mutex, 0, 1);
}

// main thread will wait for 2 new threads
Parallel::~Parallel()
{
	pthread_join(thr_put, NULL);
	pthread_join(thr_get, NULL);
}

void Parallel::createThreads()
{
	pthread_create(&thr_put, NULL, _start_getCin, this);
	pthread_create(&thr_get, NULL, _start_getBuf, this);
}

// uses as an argument at pthread_create
void* Parallel::_start_getCin(void* arg)
{
	((Parallel*)arg)->getCin();
	return NULL;
}

// uses as an argument at pthread_create
void* Parallel::_start_getBuf(void* arg)
{
	Parallel* par = (Parallel*)arg;
	par->getBuf();
	return NULL;
}

// gets input from cin, parses, puts to buffer
void Parallel::getCin()
{
	while (1)
	{
		parseInput();
		sem_wait(&sem_put);
		sem_wait(&sem_mutex);
		//critical section
		buffer = new_str;

		sem_post(&sem_get);
		sem_post(&sem_mutex);
	}
}

// gets string from buffer and sends to program 2 (server)
void Parallel::getBuf()
{
	std::string buf_str;
	int sum = 0;
	mySocket.connect_srv();//connection problem doesn't affect cin or cout
	while (1)
	{
		sem_wait(&sem_get);
		sem_wait(&sem_mutex);
		//critical section
		buf_str = buffer;
		buffer.clear();

		sem_post(&sem_put);
		sem_post(&sem_mutex);
		std::cout << buf_str << std::endl;
		sum = getSum(buf_str);//sum of numbers in string
		sum_buffer.push(sum);//not a critical section
		mySocket.send_queue(sum_buffer);
	}
}

int Parallel::getSum(std::string str)
{
	unsigned int sum = 0;
	for(unsigned int i = 0; i < str.size(); i++)
	{
		if (isdigit(str[i])){
			sum += int(str[i] - '0');
		}
	}
	return sum;
}


void Parallel::parseInput()
{
	std::cin >> new_str;
	while (!((new_str.length() <= 64) && _is_digit(new_str))){//get string until conditions are true
		std::cin >> new_str;
	}
	sort(new_str.rbegin(), new_str.rend());//sort in descending order
	replace_if(new_str.begin(), new_str.end(),
			[](char ch) {return ((int(ch) % 2) == 0); }, 'K');//if even, replace with 'K'
	for (unsigned int i = 0; i < new_str.size(); i++)
	{
			if (new_str[i] == 'K'){
				new_str.insert(++i, 1, 'B');//insert one 'B' after 'K'
			}
	}
}

bool Parallel::_is_digit(std::string str) const
{
	return all_of(str.begin(), str.end(),
			[](char ch){ return isdigit(ch);});
}


