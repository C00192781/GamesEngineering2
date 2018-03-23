#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int p = 0, c = 0;


//int rw = 1;
//int nr = 0;

//int count;


//void V(int &sem)
//{
//	sem += 1;
//}
//
//void P(int &sem)
//{
//
//
//
//	while (sem <= 0)
//	{
//
//	}
//	sem -= 1;
//}


class Semaphore
{
public:
	int semCount;
	std::mutex mx;
	std::condition_variable cv;


	Semaphore()
	{
		semCount = 1;
	}


	void P()
	{
		std::unique_lock<std::mutex> lk(mx);
		
		while (semCount <= 0)
		{
			cv.wait(lk);
		}
		semCount--;

	}

	void V()
	{
		std::unique_lock<std::mutex> lk(mx);
		semCount++;
		lk.unlock();
		cv.notify_one();
	}

};



Semaphore rw;
Semaphore mutexR;
int nr = 0;

const int n = 5;
int buf[n];

int bufferStep;

int getRandomValue()
{
	srand(time(NULL));
	int random;

	random = rand() % 101;

	return random;
}

void Reader()
{
	bool run = true;
	while (run == true)
	{
		//P(&mutexR);
		mutexR.P();
		
		nr = nr + 1;


		if (nr == 1)
		{
			rw.P();
		}

		//if first, get lock
		//V(&mutexR);
		mutexR.V();
	


		// read database
		std::cout << "Reading Data" << std::endl;
		//for (int i = 0; i < n; i++)
		//{
		//	std::cout << i << ": " << buf[i] << std::endl;
		//}

		// 	P(&mutexR);
		mutexR.P();
	

		nr = nr - 1;
		if (nr == 0)
		{
			// V(&rw);
			rw.V();
		}

		// if last, release lock
		// V(&mutexR);
		mutexR.V();
		

		this_thread::sleep_for(chrono::milliseconds(2000));
	}
}



void Writer()
{
	bool run = true;
	
	while (run == true)
	{

		//P(&rw);
		rw.P();
		// write the database

		this_thread::sleep_for(chrono::milliseconds(1000));

		buf[bufferStep] = getRandomValue();
		std::cout << "Value written to database: " << buf[bufferStep] << std::endl;
		bufferStep = (bufferStep + 1) % n;
		
		//V(&rw);
		rw.V();
		

		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}


int main()
{
	thread reader(Reader);
	thread writer(Writer);
	thread reader2(Reader);
	thread writer2(Writer);
	thread reader3(Reader);
	thread writer3(Writer);

	reader.join();
	writer.join();
	reader2.join();
	writer2.join();
	reader3.join();
	writer3.join();
	cin.get();
}

