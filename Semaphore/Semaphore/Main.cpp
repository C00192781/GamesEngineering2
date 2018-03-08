#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;

int p = 0, c = 0;
const int n = 5; 

int buf[n];

// variables for front and back of the queue
int front = 0;
int rear = 0;

int emptySem = 5;
int full = 0;

int mutexD = 1;
int mutexF = 1;

std::mutex mx;
std::condition_variable emptyCondition;
std::condition_variable fullCondition;


void V(int &sem)
{
	sem += 1;
}

void P(int &sem)
{
	while (sem <= 0)
	{

	}
	sem -= 1;
}



// Producers are said to be busy waiting
void Producer()
{
	bool run = true;
	while (run == true)
	{
		while (p < n)
		{
			cout << "ID:" << this_thread::get_id() << endl;

			while (!p == c)
			{
				// waiting/spinning
			}

			//produce data 
			int data = rand() % 101;

			// await empty > 0
			P(emptySem);

			mx.lock();

			// wait until no other producer is in the process of making changes
			P(mutexD);

			buf[rear] = data;

			// increment rear
			rear = (rear + 1) % n;

			// signal that the producer isn't altering buffer data anymore
			V(mutexD);

			mx.unlock();

			// signal that the data has been added
			V(full);

			std::cout << "Data deposited in buffer: " << data << std::endl;

			this_thread::sleep_for(chrono::milliseconds(2000));

			p += 1;
		}

		cout << "Production Finished" << endl;
		run = false;
	}	
}


void Consumer()
{
	bool run = true;
	while (run == true)
	{
		while (c < n)
		{
			cout << " " << "ID:" << this_thread::get_id() << endl;

			while (p <= c)
			{
				// waiting/spinning
			}

			// will hold the data received
			int result;

			// await full > 0
			P(full);

			mx.lock();

			// wait until no other consumer is in the process of making changes
			P(mutexF);

			// fetch message
			result = buf[front];

			front = (front + 1) % n;

			// signal that the consumer isn't receiving buffer data anymore
			V(mutexF);

			mx.unlock();

			// signal that the data has read
			V(emptySem);

			this_thread::sleep_for(chrono::milliseconds(1000));

			c += 1;
		}
		cout << "Consumption Finished" << endl;
		run = false;
	}
}


int main()
{
	thread producer(Producer);
	thread consumer(Consumer);
	producer.join();
	consumer.join();
	cin.get();
}