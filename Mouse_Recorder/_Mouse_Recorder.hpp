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
	//using clock = std::chrono::steady_clock;
	//std::chrono::high_resolution_clock::time_point m_start;			//"zmienna" ktora bedzie trzymac czas startowy		(czesc struktury steady_clock, przestrzeni nazw chrono)
	//std::chrono::high_resolution_clock::time_point m_stop;			//"zmienna" ktora bedzie trzymac czas koncowy		(czesc struktury steady_clock, przestrzeni nazw chrono)
	using clock = std::chrono::steady_clock;
	clock::time_point m_start;
	COORD CORD;						//Obiekt struktury COORD, w ktorym znajduja sie koordynaty X i Y do ustawienia kursora
	HANDLE H_OUT, H_IN;				//Zmienna przechowujace uchywyt do outputu oraz inputu okna
	POINT Cursor_Pos;						//current cursor position
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PRIVATE
	*/
	void SetCursorPosition(const short _X_AXIS, const short _Y_AXIS);	//Metoda ustawiajaca pozycje kursora
	void Clock_Format() const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY PRIVATE
	*/
	LONG get_cursor_position_x() const;
	LONG get_cursor_position_y() const;
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
	void Erase_Row(const short CORD_X, const short CORD_Y);
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