#include "_Mouse.hpp"

using namespace std;

_Mouse::_Mouse():
	dwMousePosition({}),
	dwButtonState(NULL),
	dwControlKeyState(NULL),
	dwEventFlags(NULL)
{

}

void _Mouse::show_obj() const
{
	std::cout << "[ X: " << dwMousePosition.X << " | Y: " << dwMousePosition.Y << " ] " << dwButtonState << ' ' << dwControlKeyState << ' ' << dwEventFlags << '\n';
}

void _Mouse::right_mouse_click_up()
{
	INPUT Input = { 0 };

	// right up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}

void _Mouse::right_mouse_click_down()
{
	INPUT Input = { 0 };

	// right down
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));
}

void _Mouse::left_mouse_click_up()
{
	INPUT Input = { 0 };

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}

void _Mouse::left_mouse_click_down()
{
	INPUT Input = { 0 };

	// left down
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));
}

void _Mouse::left_mouse_click()
{
	INPUT Input = { 0 };

	// left down
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}

void _Mouse::right_mouse_click()
{
	INPUT Input = { 0 };

	// left down
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}

void _Mouse::double_click()
{
	//double times one single click to create a double click event
	INPUT Input = { 0 };

	// left down
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
	

	// left down
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}

void _Mouse::move_mouse(const DWORD dx, const DWORD dy) const
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = LONG(dx);
	Input.mi.dy = LONG(dy);
	::SendInput(1, &Input, sizeof(INPUT));
	//try (GetSystemMetrics(SM_CXSCREEN) -1);
}

void _Mouse::Set_dwMousePosition(const SHORT X, const SHORT Y)
{
	this->dwMousePosition.X = X;
	this->dwMousePosition.Y = Y;
}

void _Mouse::Set_dwButtonState(const DWORD dwButtonState)
{
	this->dwButtonState = dwButtonState;
}

void _Mouse::Set_dwControlKeyState(const DWORD dwControlKeyState)
{
	this->dwControlKeyState = dwControlKeyState;
}

void _Mouse::Set_dwEventFlags(const DWORD dwEventFlags)
{
	this->dwEventFlags = dwEventFlags;
}

SHORT _Mouse::get_dwMousePosition_X() const
{
	return dwMousePosition.X;
}

SHORT _Mouse::get_dwMousePosition_Y() const
{
	return dwMousePosition.Y;
}

DWORD _Mouse::get_dwButtonState() const
{
	return dwButtonState;
}

DWORD _Mouse::get_dwControlKeyState() const
{
	return dwControlKeyState;
}

DWORD _Mouse::get_dwEventFlags() const
{
	return dwEventFlags;
}

_Mouse::~_Mouse()
{
	dwMousePosition.X = 0;
	dwMousePosition.Y = 0;
	dwButtonState = 0;
	dwControlKeyState = 0;
	dwEventFlags = 0;
}