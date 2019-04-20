/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *							Greetings for everyone!
*/
#ifndef _MOUSE_RECORDER_H_
#define _MOUSE_RECORDER_H_

#include <iostream>
#include <windows.h>
#include <string.h>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>

#pragma warning(disable : 4996);	//disable this warning, for localtime();

class _Mouse_Recorder
{
private:
	//////////////////////////////////////////////////////////////////////////////
	/*
		ZMIENNE PRIVATE
	*/
	/*time_t t;
	struct tm * now;*/
	__int16 minute, second;
	using clock = std::chrono::steady_clock;
	std::chrono::high_resolution_clock::time_point m_start;			//"zmienna" ktora bedzie trzymac czas startowy		(czesc struktury steady_clock, przestrzeni nazw chrono)
	std::chrono::high_resolution_clock::time_point m_stop;			//"zmienna" ktora bedzie trzymac czas koncowy		(czesc struktury steady_clock, przestrzeni nazw chrono)
	//////////////////////////////////////////////////////////////////////////////
public:
	//////////////////////////////////////////////////////////////////////////////
	/*
		KONSTRUKTORY PUBLIC
	*/
	_Mouse_Recorder();
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	void Record();
	void Clock();
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY PUBLIC
	*/
	
	//////////////////////////////////////////////////////////////////////////////
	/*
		OPERATORY PUBLIC
	*/
	//JEDNOARGUMENTOWE
	
	//DWUARGUMENTOWE
	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY PUBLIC
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		DESTRUKTOR
	*/
	virtual ~_Mouse_Recorder();
};

#endif /* _MOUSE_RECORDER_H_ */