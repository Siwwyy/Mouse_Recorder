/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *							Greetings for everyone!
*/
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <iostream>
#include <windows.h>
#include <string.h>


class _Keyboard
{
private:
	//////////////////////////////////////////////////////////////////////////////
	/*
		ZMIENNE PRIVATE
	*/
	DWORD keyboard_code;
	COORD dwMousePosition;
	//////////////////////////////////////////////////////////////////////////////
public:
	//////////////////////////////////////////////////////////////////////////////
	/*
		KONSTRUKTORY PUBLIC
	*/
	_Keyboard();
	_Keyboard(const DWORD keyboard_code);
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	void button_press();
	void show_obj() const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY PUBLIC
	*/
	void Set_keyboard_code(const DWORD keyboard_code);
	void Set_dwMousePosition(const SHORT X, const SHORT Y);
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
	DWORD get_keyboard_code() const;
	SHORT get_dwMousePosition_X() const;
	SHORT get_dwMousePosition_Y() const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		DESTRUKTOR
	*/
	virtual ~_Keyboard();
};

#endif /* _KEYBOARD_H_ */