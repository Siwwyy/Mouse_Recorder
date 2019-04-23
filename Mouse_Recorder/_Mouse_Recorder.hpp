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

/////////////////////////////////////////////
/*
	OWN HEADERS
*/
#include "_Mouse.hpp"
#include "_Keyboard.hpp"
/////////////////////////////////////////////

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
	_Mouse Mouse;
	_Keyboard Keyboard;
	__int16 minute, second;
	std::vector<_Mouse> mouse_moves;
	std::vector<_Keyboard> keyboard_event;
	using clock = std::chrono::steady_clock;
	clock::time_point m_start;
	COORD CORD;						//Obiekt struktury COORD, w ktorym znajduja sie koordynaty X i Y do ustawienia kursora
	HANDLE H_OUT, H_IN;				//Zmienna przechowujace uchywyt do outputu oraz inputu okna
	HWND Hwnd;
	POINT Cursor_Pos;						//current cursor position

	HHOOK mouseHook;

	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PRIVATE
	*/
	void SetCursorPosition(const short _X_AXIS, const short _Y_AXIS);	//Metoda ustawiajaca pozycje kursora
	void Clock_Format() const;
	//LRESULT __stdcall MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam);
	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY PRIVATE
	*/
	SHORT get_cmd_cursor_position_x() const;
	SHORT get_cmd_cursor_position_y() const;
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
	void Menu();
	void Record();
	void Clock();
	void Load_Recorded_Mouse_Events();
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