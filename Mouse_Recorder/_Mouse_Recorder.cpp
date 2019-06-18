#include "_Mouse_Recorder.hpp"

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;


HHOOK keyboardHook;
HHOOK mouseHook;
POINT Cursor_Pos;

bool _Mouse_Recorder::recorder = false;
_Mouse _Mouse_Recorder::Mouse;
_Keyboard _Mouse_Recorder::Keyboard;
std::vector<std::pair<_Mouse, _Keyboard>> _Mouse_Recorder::mouse_moves{};

void _Mouse_Recorder::SetCursorPosition(const short _X_AXIS, const short _Y_AXIS)
{
	CORD.X = _X_AXIS;
	CORD.Y = _Y_AXIS;
	SetConsoleCursorPosition(H_OUT, CORD);
}

void _Mouse_Recorder::Clock_Format() const
{
	if (second < 10 && minute < 10)
	{
		cout << "Elapsed time: "  << '0' << minute << ':' << '0' << second;
	}
	else if(second >= 10 && minute < 10)
	{
		cout << "Elapsed time: " << '0' << minute << ':' << second;
	}
	else if (second < 10 && minute >= 10)
	{
		cout << "Elapsed time: " << minute << ':' << '0' << second;
	}
	else
	{
		cout << "Elapsed time: " << minute << ':' << second;
	}
}

////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK _Mouse_Recorder::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	HWND fwindow = GetForegroundWindow();
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
	if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
	{
		std::cout << ((char)(key->vkCode)) << ' ';
		if (((char)(key->vkCode)) == VK_F1)
		{
			recorder = true;
		}
		mouse_moves.emplace_back(std::make_pair(_Mouse(-1000,-1000),_Keyboard(((char)(key->vkCode)))));
	}
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK _Mouse_Recorder::mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	HWND fwindow = GetForegroundWindow();
	PMSLLHOOKSTRUCT mouse = (PMSLLHOOKSTRUCT)lParam;
	//std::cout << "[ X: " << mouse->pt.x << " | Y: " << mouse->pt.y << " |" << wParam << '\n';
	mouse_moves.emplace_back(std::make_pair(_Mouse(mouse->pt.x, mouse->pt.y, wParam), _Keyboard(-1000)));
	return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////

SHORT _Mouse_Recorder::get_cmd_cursor_position_x() const
{
	return this->CORD.X;
}

SHORT _Mouse_Recorder::get_cmd_cursor_position_y() const
{
	return this->CORD.Y;
}

_Mouse_Recorder::_Mouse_Recorder() :
	/*mouse_moves(0),*/
	minute(0),
	second(0)
{
	H_OUT = GetStdHandle(STD_OUTPUT_HANDLE);
	H_IN = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(H_IN, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);		//set the console mode to enable window mouse input and extended flags

}

void _Mouse_Recorder::Menu()
{
	char choice = ' ';
	for (;;)
	{
		SetConsoleTextAttribute(H_IN, FOREGROUND_RED | FOREGROUND_INTENSITY | 2);
		cout << "MAIN MENU" << endl;
		cout << "--------------------" << endl;
		cout << "1. Record your mouse moves" << endl;
		cout << "2. Load and open your mouse moves" << endl;
		cout << "3. Exit" << endl;

		cout << "Wybierz: " << endl;
		cin >> choice;

		switch (choice)
		{
		case '1':
		{
			SetConsoleTextAttribute(H_IN, FOREGROUND_RED | FOREGROUND_INTENSITY);
			system("cls");
		//	FreeConsole();
			Record();
			//FreeConsole();
		}
		break;

		case '2':
		{
			SetConsoleTextAttribute(H_IN, FOREGROUND_GREEN | FOREGROUND_INTENSITY | 1);
			system("cls");
			Load_Recorded_Mouse_Events();
		}
		break;

		case '3':
		{
			SetConsoleTextAttribute(H_IN, FOREGROUND_GREEN | FOREGROUND_INTENSITY | 1);
			exit(0);
		}
		break;

		SetConsoleTextAttribute(H_IN, FOREGROUND_RED | FOREGROUND_INTENSITY | 2);
		default: cout << "Nie ma takiej opcji w menu!";
		}
		system("cls");
		choice = ' ';
	}
}

void _Mouse_Recorder::Record()
{
	m_start = clock::now();
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);
	mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseHookProc, 0, 0);
	MSG message{};
	while (TRUE)
	{
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		if (recorder == true)
		{
			break;
		}
	}
	recorder = false;
	UnhookWindowsHookEx(keyboardHook);
	UnhookWindowsHookEx(mouseHook);
}

void _Mouse_Recorder::Clock()
{
	second = duration_cast<seconds>(clock::now() - m_start).count();
	if (second % 60 == 0 && second > 0)
	{
		++minute;
		m_start = clock::now();
		second = 0;
	}
	SetCursorPosition(1, 1);
	Clock_Format();
	SetCursorPosition(1, 0);
	std::cout << "To stop recording, press right shift";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	Erase_Row(1,1);
}

void _Mouse_Recorder::Load_Recorded_Mouse_Events()
{
	if (mouse_moves.size() == 0)
	{
		std::cout << "Mouse wasnt be recorder yet" << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));	//sleep for 1 second
	}
	else
	{
		bool is_pressed_LBM = false;		//if is pressed left button mouse
		bool is_pressed_RBM = false;		//if is pressed right button mouse
		bool double_click_blocker = false;
		bool wait = false;
		size_t keyboard_vector_counter = 0;
	/*	for (size_t i = 0; i < mouse_moves.size(); ++i)
		{
			mouse_moves[i].first.show_obj();
		}*/
		for (size_t i = 0; i < mouse_moves.size(); ++i)
		{
			if (mouse_moves[i].first.get_dwMousePosition_X() != -1000 && mouse_moves[i].first.get_dwMousePosition_Y() != -1000)
			{
				SetCursorPos(mouse_moves[i].first.get_dwMousePosition_X(), mouse_moves[i].first.get_dwMousePosition_Y());
				if (mouse_moves[i].first.get_dwButtonState() >= 513)
				{
					if (mouse_moves[i].first.get_dwButtonState() == 513)
					{
						//std::this_thread::sleep_for(std::chrono::milliseconds(10));
						//mouse_moves[i].first.left_mouse_click_up();
						mouse_moves[i].first.left_mouse_click();
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						//std::this_thread::sleep_for(std::chrono::milliseconds(1));
					}
					//else if (mouse_moves[i].first.get_dwButtonState() == 514)
					//{
					//	//std::this_thread::sleep_for(std::chrono::milliseconds(1));
					//	mouse_moves[i].first.left_mouse_click_down();
					//	//std::this_thread::sleep_for(std::chrono::milliseconds(1));
					//}

					if (mouse_moves[i].first.get_dwButtonState() == 516)
					{
						
						//mouse_moves[i].first.right_mouse_click_up();
						mouse_moves[i].first.right_mouse_click();
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						//std::this_thread::sleep_for(std::chrono::milliseconds(1));
					}
					//else if (mouse_moves[i].first.get_dwButtonState() == 517)
					//{
					//	//std::this_thread::sleep_for(std::chrono::milliseconds(1));
					//	mouse_moves[i].first.right_mouse_click_down();
					//	//std::this_thread::sleep_for(std::chrono::milliseconds(1));
					//}
				}
			}
			else
			{
				if (mouse_moves[i].second.get_keyboard_code() != -1000)
				{
					mouse_moves[i].second.button_press();
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		std::cout << "Loading complete" << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));	//sleep for 1 second
	}
}

void _Mouse_Recorder::Erase_Row(const short CORD_X, const short CORD_Y)
{
	SetCursorPosition(CORD_X, CORD_Y);
	for (size_t i = 0; i < 30; ++i)
	{
		std::cout << ' ';
	}
	SetCursorPosition(CORD_X, CORD_Y);
}

_Mouse_Recorder::~_Mouse_Recorder()
{
	second = 0;
	minute = 0;
}