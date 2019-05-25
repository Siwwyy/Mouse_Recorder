/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *							Greetings for everyone!
*/
#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <iostream>
#include <windows.h>
#include <string.h>


class _Mouse
{
private:
	//////////////////////////////////////////////////////////////////////////////
	/*
		ZMIENNE PRIVATE
	*/
	COORD dwMousePosition;
	DWORD dwButtonState;
	DWORD dwControlKeyState;
	DWORD dwEventFlags;
	//////////////////////////////////////////////////////////////////////////////
public:
	//////////////////////////////////////////////////////////////////////////////
	/*
		KONSTRUKTORY PUBLIC
	*/
	_Mouse();
	_Mouse(const SHORT X, const SHORT Y);
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	void show_obj() const;
	void right_mouse_click_up();
	void right_mouse_click_down();
	void left_mouse_click_up();
	void left_mouse_click_down();
	void left_mouse_click();
	void right_mouse_click();
	void double_click();
	void move_mouse(const DWORD dx, const DWORD dy) const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY PUBLIC
	*/
	void Set_dwMousePosition(const SHORT X, const SHORT Y);
	void Set_dwButtonState(const DWORD dwButtonState);
	void Set_dwControlKeyState(const DWORD dwControlKeyState);
	void Set_dwEventFlags(const DWORD dwEventFlags);
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
	SHORT get_dwMousePosition_X() const;
	SHORT get_dwMousePosition_Y() const;
	DWORD get_dwButtonState() const;
	DWORD get_dwControlKeyState() const;
	DWORD get_dwEventFlags() const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		DESTRUKTOR
	*/
	virtual ~_Mouse();
};

#endif /* _MOUSE_H_ */