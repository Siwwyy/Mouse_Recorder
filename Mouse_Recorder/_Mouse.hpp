/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *							Greetings for everyone!
*/
#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <iostream>
#include <windows.h>
#include <string.h>

#pragma warning(disable : 4996);	//disable this warning, for localtime();

class _Mouse
{
private:
	//////////////////////////////////////////////////////////////////////////////
	/*
		ZMIENNE PRIVATE
	*/
	DWORD dwFlags;
	DWORD dx;
	DWORD dy;
	DWORD dwData;
	ULONG_PTR dwExtraInfo;
	//////////////////////////////////////////////////////////////////////////////
public:
	//////////////////////////////////////////////////////////////////////////////
	/*
		KONSTRUKTORY PUBLIC
	*/
	_Mouse();
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
	void move_mouse(const DWORD dx, const DWORD dy) const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY PUBLIC
	*/
	void Set_Mouse(const DWORD dwFlags, const DWORD dx, const DWORD dy, const DWORD dwData, const ULONG_PTR dwExtraInfo);
	void Set_dwFlags(const DWORD dwFlags);
	void Set_dx(const DWORD dx);
	void Set_dy(const DWORD dy);
	void Set_dwData(const DWORD dwData);
	void Set_dwExtraInfo(const ULONG_PTR dwExtraInfo);
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
	const DWORD & get_dwFlags() const;
	const DWORD & get_dx() const;
	const DWORD & get_dy() const;
	const DWORD & get_dwData() const;
	const ULONG_PTR & get_dwExtraInfo() const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		DESTRUKTOR
	*/
	virtual ~_Mouse();
};

#endif /* _MOUSE_H_ */