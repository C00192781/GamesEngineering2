#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

int buf, p = 0, c = 0;
static int counter;
// const int required for int a[]
const int n = 5; 

// a mutual exclusion object (mutex) is a program object that allows multiple program threads to share the same resource, 
// such as file access, but not simultaneously.
// When a program is started, a mutex is created with a unique name.
// After this stage, any thread that needs the resource must lock the mutex from other threads while it is using the resource.
// The mutex is set to unlock when the data is no longer needed or the routine is finished.
static mutex m_lock;

// Producers are said to be busy waiting or spinning
void Producer()
{
	int a[n] = { 10, 20, 30, 40, 50 };
	bool run = true;
	while (run == true)
	{
		// calling thread locks mutex
		//m_lock.lock();

		counter = counter + 1;
		cout << "Counter: " << counter << endl;
		while (p < n)
		{
			cout << "ID:" << this_thread::get_id() << endl;
			this_thread::sleep_for(chrono::seconds(2));
			// await (p == c)
			// in Consumer(), waiting until c = c + 1 adds up to same value as p
			while (!p == c)
			{
				//cout << "spinning" << endl;
			}
			buf = a[p];
			//cout << a[p] << " deposited in buffer" << endl;
			p += 1; 

			//m_lock.unlock();
		}
		cout << "Production Finished" << endl;
		run = false;
	}	
}


void Consumer()
{
	int b[n];
	bool run = true;
	while (run == true)
	{
		//m_lock.lock();
		while (c < n)
		{
			cout << "ID:" << this_thread::get_id() << endl;
			this_thread::sleep_for(chrono::seconds(1));
			// await (p > c)
			// in Producer(), waiting until p = p + 1 adds up to a higher value than p
			while (p <= c)
			{
				//cout << "spinning" << endl;
			}
			b[c] = buf;
			//cout << buf << " deposited in b[]" << endl;
			c += 1;
			//m_lock.lock();
		}
		cout << "Consumption Finished" << endl;
		run = false;
	}
}


void fun()
{
	while (true)
	{
		m_lock.lock();
		counter += 1;
		cout << "Counter: " << counter << endl;
		cout << "Process ID: " << this_thread::get_id() << endl;
		this_thread::sleep_for(chrono::seconds(1));
		m_lock.unlock();
	}
}

int main()
{
	//thread t1(fun);
	//thread t2(fun);
	//t1.join();
	//t2.join();

	thread producer(Producer);
	thread consumer(Consumer);
	producer.join();
	consumer.join();
	cin.get();
}