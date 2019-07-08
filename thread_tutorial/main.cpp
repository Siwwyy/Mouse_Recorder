/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *							Greetings for everyone!
*/
#include <iostream>
#include <windows.h>
#include <string.h>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

void foo1(void)
{
	std::cout << "From foo1" << endl;
}

void foo2(void)
{
	std::cout << "From foo2" << endl;
}



std::mutex                       g_mutex;
std::vector<std::exception_ptr>  g_exceptions;

void throw_function()
{
	throw std::exception("something wrong happened");
}

//void func()
//{
//	try
//	{
//		throw_function();
//	}
//	catch (...)
//	{
//		std::lock_guard<std::mutex> lock(g_mutex);
//		g_exceptions.push_back(std::current_exception());
//	}
//}


//std::mutex g_lock;
//
//void func()
//{
//	g_lock.lock();
//
//	std::cout << "entered thread " << std::this_thread::get_id() << std::endl;
//	std::this_thread::sleep_for(std::chrono::seconds(rand() % 10));
//	std::cout << "leaving thread " << std::this_thread::get_id() << std::endl;
//
//	g_lock.unlock();
//}


template <typename T>
class container
{
	std::recursive_mutex  _lock;
	std::vector<T> _elements;
public:
	void add(T element)
	{
		_lock.lock();
		_elements.push_back(element);
		_lock.unlock();
	}

	void addrange(int num, ...)
	{
		va_list arguments;

		va_start(arguments, num);

		for (int i = 0; i < num; i++)
		{
			_lock.lock();
			add(va_arg(arguments, T));
			_lock.unlock();
		}

		va_end(arguments);
	}

	void dump()
	{
		_lock.lock();
		for (auto e : _elements)
			std::cout << e << std::endl;
		_lock.unlock();
	}
};

void func(container<int>& cont)
{
	cont.addrange(3, rand(), rand(), rand());
}

int main(int argc, char * argv[])
{
	//std::thread foo1_thread(foo1);
	////std::thread foo2_thread(foo2);
	////foo1_thread.join();
	//foo1_thread.detach();

	/*if (foo1_thread.joinable())
	{
		foo1_thread.join();
	}*/
	//g_exceptions.clear();

	//std::thread t(func);
	//t.join();

	//for (auto& e : g_exceptions)
	//{
	//	try
	//	{
	//		if (e != nullptr)
	//		{
	//			std::rethrow_exception(e);
	//		}
	//	}
	//	catch (const std::exception& e)
	//	{
	//		std::cout << e.what() << std::endl;
	//	}
	//}
	//srand((unsigned int)time(0));

	//std::thread t1(func);
	//std::thread t2(func);
	//std::thread t3(func);

	//t1.join();
	//t2.join();
	//t3.join();
	/*std::cout << foo1 << ' ' << &foo1 << endl;*/


	srand((unsigned int)time(0));

	container<int> cont;

	std::thread t1(func, std::ref(cont));
	std::thread t2(func, std::ref(cont));
	std::thread t3(func, std::ref(cont));

	t1.join();
	t2.join();
	t3.join();

	cont.dump();


	system("pause");
	return EXIT_SUCCESS;
}