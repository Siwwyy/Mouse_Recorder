/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *							Greetings for everyone!
*/
#include <iostream>
#include <windows.h>
#include <string.h>
#include "_Mouse_Recorder.hpp"

void foo(int *tab, const size_t size)
{
	*tab = (*tab) + 1;
}

void foo1(int *tab, const size_t size)
{
	*tab = (*tab) - 1;
}

//int *p;
//int a;

int main(int argc, char * argv[])
{
	//std::cout << p << '\n';
	//std::cout << a<< '\n';
	//char abc[] = { 0x01, 0x02, 0x03,0x04 };
	//unsigned short * ptr = (unsigned short*)(void*)abc;
	//std::cout << std::hex << ptr[1] << '\n';
	//const size_t size = 6;
	//int tab[size] = { 4,2,3,4,5,6 };
	//for (size_t i = 0; i < size; ++i)
	//{
	//	std::cout << &tab[i] << ' ';
	//}
	//std::cout << '\n';
	//std::cout << *tab << '\n';
	//std::cout << '\n';
	//std::cout << &tab[0] << ' '<< tab << '\n';
	//foo(tab, size);
	//std::cout << &tab[0] << ' ' << tab[0] << '\n';
	//foo1(tab, size);
	//std::cout << &tab[0] << ' ' << tab[0] << '\n';
	/*int a = 10;
	float c = (double)a;*/
	_Mouse_Recorder Obj;
	Obj.Menu();
	system("pause");
	return EXIT_SUCCESS;
}