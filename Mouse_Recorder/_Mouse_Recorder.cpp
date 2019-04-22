#include "_Mouse_Recorder.hpp"

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

bool _Mouse_Recorder::Mouse_Event(_MOUSE_EVENT_RECORD & krec, const HANDLE & _HANDLE_PARAM)
{
	DWORD cc;
	INPUT_RECORD InRec{};

	for (;;)
	{
		ReadConsoleInput(_HANDLE_PARAM, &InRec, 1, &cc);
		if (InRec.EventType == MOUSE_EVENT && ((_MOUSE_EVENT_RECORD&)InRec.Event).dwButtonState)
		{
			krec = (_MOUSE_EVENT_RECORD&)InRec.Event;
			return true;
			//std::cout << 'd';
		}
		
	}
	return false;
}

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

SHORT _Mouse_Recorder::get_cmd_cursor_position_x() const
{
	return this->CORD.X;
}

SHORT _Mouse_Recorder::get_cmd_cursor_position_y() const
{
	return this->CORD.Y;
}

LONG _Mouse_Recorder::get_cursor_position_x() const
{
	return this->Cursor_Pos.x;
}

LONG _Mouse_Recorder::get_cursor_position_y() const
{
	return this->Cursor_Pos.y;
}

_Mouse_Recorder::_Mouse_Recorder() :
	mouse_moves(0),
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
			Record();
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
	SetForegroundWindow(Hwnd);
	SetActiveWindow(Hwnd);
	SetFocus(Hwnd);
	_MOUSE_EVENT_RECORD Recorder;
	bool record = true;
	while (record == true)
	{
		if (GetAsyncKeyState(VK_RSHIFT))
		{
			record = false;
		}
		Clock();
		if (GetAsyncKeyState(FROM_LEFT_1ST_BUTTON_PRESSED))
		{
			GetCursorPos(&Cursor_Pos);
			Mouse.Set_dwMousePosition(Cursor_Pos.x, Cursor_Pos.y);
			Mouse.Set_dwButtonState(((DWORD)FROM_LEFT_1ST_BUTTON_PRESSED));
		}
		else if (GetAsyncKeyState(RIGHTMOST_BUTTON_PRESSED))
		{
			GetCursorPos(&Cursor_Pos);
			Mouse.Set_dwMousePosition(Cursor_Pos.x, Cursor_Pos.y);
			Mouse.Set_dwButtonState(((DWORD)RIGHTMOST_BUTTON_PRESSED));
		}
		else if (GetAsyncKeyState(DOUBLE_CLICK))
		{
			GetCursorPos(&Cursor_Pos);
			Mouse.Set_dwMousePosition(((SHORT)Cursor_Pos.x), ((SHORT)Cursor_Pos.y));
			Mouse.Set_dwEventFlags(((DWORD)DOUBLE_CLICK));
		}
		else
		{
			GetCursorPos(&Cursor_Pos);
			Mouse.Set_dwMousePosition(((SHORT)Cursor_Pos.x), ((SHORT)Cursor_Pos.y));
		}
		mouse_moves.emplace_back(Mouse);
	}
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
	if (mouse_moves.size() < 1)
	{
		std::cout << "Mouse wasnt be recorder yet" << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(3));	//sleep for 1 second
	}
	else
	{
		bool is_pressed_LBM = false;		//if is pressed left button mouse
		bool is_pressed_RBM = false;		//if is pressed right button mouse
		bool double_click_blocker = false;
		for (size_t i = 0; i < mouse_moves.size(); ++i)
		{
			mouse_moves[i].show_obj();
			if (mouse_moves[i].get_dwMousePosition_X() != 0 || mouse_moves[i].get_dwMousePosition_Y() != 0)
			{
				SetCursorPos(mouse_moves[i].get_dwMousePosition_X(), mouse_moves[i].get_dwMousePosition_Y());
				if (i <= (mouse_moves.size() - 2))
				{
					if (mouse_moves[i].get_dwMousePosition_X() == mouse_moves[i + 1].get_dwMousePosition_X() && mouse_moves[i].get_dwMousePosition_Y() == mouse_moves[i + 1].get_dwMousePosition_Y())
					{
						if (mouse_moves[i].get_dwButtonState() == 1 && mouse_moves[i + 1].get_dwButtonState() == 1 && double_click_blocker == false)
						{
							double_click_blocker = true;
							std::cout << 'd' << '\n';
							mouse_moves[i].double_click();
							continue;
						}
					}
					else
					{
						double_click_blocker = false;
					}
				}
				if (mouse_moves[i].get_dwButtonState() == 1)
				{
					is_pressed_LBM = true;
					is_pressed_RBM = false;
					mouse_moves[i].left_mouse_click();
				}
				else if (mouse_moves[i].get_dwButtonState() == 2)
				{
					is_pressed_LBM = false;
					is_pressed_RBM = true;
					mouse_moves[i].right_mouse_click();
				}
				else
				{
					is_pressed_LBM = false;
					is_pressed_RBM = false;
				}
			}
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		//turn off the used buttons
		//mouse_moves[mouse_moves.size() - 1].left_mouse_click_down();
		//mouse_moves[mouse_moves.size() - 1].right_mouse_click_down();
		system("pause");
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