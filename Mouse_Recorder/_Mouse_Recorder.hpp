/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *							Greetings for everyone!
*/
#ifndef _MOUSE_RECORDER_H_
#define _MOUSE_RECORDER_H_

#include <iostream>
//#include <windows.h>
#include <string.h>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <stdio.h>

/////////////////////////////////////////////
/*
	OWN HEADERS
*/
#include "_Mouse.hpp"
#include "_Keyboard.hpp"
/////////////////////////////////////////////


class _Mouse_Recorder
{
private:
	//////////////////////////////////////////////////////////////////////////////
	/*
		ZMIENNE PRIVATE
	*/
	static _Mouse Mouse;
	static _Keyboard Keyboard;
	__int16 minute, second;
	static bool recorder;
	//std::vector<std::pair<_Mouse,_Keyboard>> mouse_moves;
	//std::vector<std::pair<_Mouse,_Keyboard>> mouse_moves;
	static std::vector<std::pair<_Mouse,_Keyboard>> mouse_moves;
	using clock = std::chrono::steady_clock;
	clock::time_point m_start;




	COORD CORD;						//Obiekt struktury COORD, w ktorym znajduja sie koordynaty X i Y do ustawienia kursora
	HANDLE H_OUT, H_IN;				//Zmienna przechowujace uchywyt do outputu oraz inputu okna
	HWND Hwnd;
	bool record = true;
	/*LRESULT * ptr_keyboard;
	LRESULT * ptr_mouse;*/
//	HHOOK mouseHook;
	//new 
				//current cursor position
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PRIVATE
	*/
	void SetCursorPosition(const short _X_AXIS, const short _Y_AXIS);	//Metoda ustawiajaca pozycje kursora
	void Clock_Format() const;
	//LRESULT __stdcall MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam);

	//constexpr LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	//constexpr LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);

	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY PRIVATE
	*/
	SHORT get_cmd_cursor_position_x() const;
	SHORT get_cmd_cursor_position_y() const;
	//LONG get_cursor_position_x() const;
	//LONG get_cursor_position_y() const;
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