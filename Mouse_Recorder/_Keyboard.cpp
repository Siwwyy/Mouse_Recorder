#include "_Keyboard.hpp"

using namespace std;

_Keyboard::_Keyboard():
	dwMousePosition({}),
	keyboard_code(NULL)
{

}

_Keyboard::_Keyboard(const DWORD keyboard_code):
	keyboard_code(keyboard_code)
{
}

void _Keyboard::button_press()
{
	keybd_event(((BYTE)keyboard_code), NULL, NULL, NULL);
}

void _Keyboard::show_obj() const
{
	std::cout << "[ X: " << dwMousePosition.X << " | Y: " << dwMousePosition.Y << " ] " << static_cast<char>(keyboard_code) << '\n';
}

void _Keyboard::Set_keyboard_code(const DWORD keyboard_code)
{
	this->keyboard_code = keyboard_code;
}

void _Keyboard::Set_dwMousePosition(const SHORT X, const SHORT Y)
{
	this->dwMousePosition.X = X;
	this->dwMousePosition.Y = Y;
}

DWORD _Keyboard::get_keyboard_code() const
{
	return this->keyboard_code;
}

SHORT _Keyboard::get_dwMousePosition_X() const
{
	return this->dwMousePosition.X;
}

SHORT _Keyboard::get_dwMousePosition_Y() const
{
	return this->dwMousePosition.Y;
}

_Keyboard::~_Keyboard()
{
	keyboard_code = NULL;
}