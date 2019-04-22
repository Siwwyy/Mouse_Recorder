#include "_Mouse.hpp"

using namespace std;

_Mouse::_Mouse():
	dwFlags(0),
	dx(0),
	dy(0),
	dwData(0),
	dwExtraInfo(0)
{

}

void _Mouse::show_obj() const
{
	std::cout << dwFlags << ' ' << dx << ' ' << dy << ' ' << dwData << ' ' << dwExtraInfo << '\n';
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

void _Mouse::Set_Mouse(const DWORD dwFlags, const DWORD dx, const DWORD dy, const DWORD dwData, const ULONG_PTR dwExtraInfo)
{
	this->dwFlags = dwFlags;
	this->dx = dx;
	this->dy = dy;
	this->dwData = dwData;
	this->dwExtraInfo = dwExtraInfo;
}

void _Mouse::Set_dwFlags(const DWORD dwFlags)
{
	this->dwFlags = dwFlags;
}

void _Mouse::Set_dx(const DWORD dx)
{
	this->dx = dx;
}

void _Mouse::Set_dy(const DWORD dy)
{
	this->dy = dy;
}

void _Mouse::Set_dwData(const DWORD dwData)
{
	this->dwData = dwData;
}

void _Mouse::Set_dwExtraInfo(const ULONG_PTR dwExtraInfo)
{
	this->dwExtraInfo = dwExtraInfo;
}

const DWORD & _Mouse::get_dwFlags() const
{
	return this->dwFlags;
}

const DWORD & _Mouse::get_dx() const
{
	return this->dx;
}

const DWORD & _Mouse::get_dy() const
{
	return this->dy;
}

const DWORD & _Mouse::get_dwData() const
{
	return this->dwData;
}

const ULONG_PTR & _Mouse::get_dwExtraInfo() const
{
	return this->dwExtraInfo;
}

_Mouse::~_Mouse()
{
	dwFlags = 0;
	dx = 0;
	dy = 0;
	dwData = 0;
	dwExtraInfo = 0;
}