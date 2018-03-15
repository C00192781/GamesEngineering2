#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

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

//wont't work
//just put everything in the class

//void P(Semaphore * sem)
//{
//	std::unique_lock<std::mutex> lk(sem->mx);
//
//	while (sem->semCount)
//	{
//		sem->cv.wait(lk);
//	}
//	sem->semCount--;
//
//}
//
//void V(Semaphore * sem)
//{
//	std::unique_lock<std::mutex> lk(sem->mx);
//
//
//	sem->semCount++;
//	lk.unlock();
//	sem->cv.notify_one();
//}





Semaphore rw;
Semaphore mutexR;
int nr = 0;

const int n = 5;
int buf[n];

int bufferStep;



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
		std::cout << "Data in database" << std::endl;
		for (int i = 0; i < n; i++)
		{
			std::cout << i << ": " << buf[i] << std::endl;
		}

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

		buf[bufferStep] = rand() % 101;
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

	reader.join();
	writer.join();
	cin.get();
}

