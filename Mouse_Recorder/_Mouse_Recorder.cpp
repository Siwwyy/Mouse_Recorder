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
		//GetCursorPos(&Cursor_Pos);
		//mouse_event(Mouse.get_dwFlags(), Mouse.get_dx(), Mouse.get_dy(), Mouse.get_dwData(), Mouse.get_dwExtraInfo());
		//mouse_moves.emplace_back(std::make_pair(Cursor_Pos.x, Cursor_Pos.y));
		if (GetAsyncKeyState(FROM_LEFT_1ST_BUTTON_PRESSED))
		{
			GetCursorPos(&Cursor_Pos);
			Mouse.Set_dx(Cursor_Pos.x);
			Mouse.Set_dy(Cursor_Pos.y);
			Mouse.Set_dwFlags(((DWORD)FROM_LEFT_1ST_BUTTON_PRESSED));
		}
		else if (GetAsyncKeyState(RIGHTMOST_BUTTON_PRESSED))
		{
			GetCursorPos(&Cursor_Pos);
			Mouse.Set_dx(Cursor_Pos.x);
			Mouse.Set_dy(Cursor_Pos.y);
			Mouse.Set_dwFlags(((DWORD)RIGHTMOST_BUTTON_PRESSED));
		}
		else
		{
			GetCursorPos(&Cursor_Pos);
			Mouse.Set_dx(Cursor_Pos.x);
			Mouse.Set_dy(Cursor_Pos.y);
		}
		/*Mouse_Event(Recorder,H_IN);
		if (Recorder.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			Mouse.Set_dx(Recorder.dwMousePosition.X);
			Mouse.Set_dy(Recorder.dwMousePosition.Y);
			Mouse.Set_dwFlags(((DWORD)FROM_LEFT_1ST_BUTTON_PRESSED));
		}*/
		//if (Recorder.dwMousePosition == MOUSE_EVENT)
		//{
		//	if (InRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
		//	{
		//		GetCursorPos(&Cursor_Pos);
		//		//Mouse.Set_dx(Cursor_Pos.x);
		//		Mouse.Set_dx(InRec.Event.MouseEvent.dwMousePosition.X);
		//		//	Mouse.Set_dy(Cursor_Pos.y);
		//		Mouse.Set_dy(InRec.Event.MouseEvent.dwMousePosition.Y);
		//		cout << InRec.Event.MouseEvent.dwMousePosition.X << "," <<
		//			InRec.Event.MouseEvent.dwMousePosition.Y << "  " << flush;
		//	}
		//	else if (InRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
		//		//else if (InRec.Event.MouseEvent.dwEventFlags == FROM_LEFT_1ST_BUTTON_PRESSED)
		//	{
		//		Mouse.Set_dwFlags(InRec.Event.MouseEvent.dwEventFlags);
		//		cout << InRec.Event.MouseEvent.dwMousePosition.X << "," <<
		//			InRec.Event.MouseEvent.dwMousePosition.Y << "  " << flush;
		//	}
		//	else if (InRec.Event.MouseEvent.dwEventFlags == FROM_LEFT_2ND_BUTTON_PRESSED)
		//	{
		//		Mouse.Set_dwFlags(InRec.Event.MouseEvent.dwEventFlags);
		//	}
		//	else if (InRec.Event.MouseEvent.dwEventFlags == FROM_LEFT_3RD_BUTTON_PRESSED)
		//	{
		//		Mouse.Set_dwFlags(InRec.Event.MouseEvent.dwEventFlags);
		//	}
		//}
	//	GetNumberOfConsoleInputEvents(H_IN, &event);
		//while (event > 0)
		//{
		//	//use my idea from zadanie3 in JPROGIII folder
		//	ReadConsoleInput(H_IN, &InRec, 1, &NumRead);
			//if (InRec.EventType == MOUSE_EVENT)
			//{
			//	if (InRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
			//	{
			//		GetCursorPos(&Cursor_Pos);
			//		//Mouse.Set_dx(Cursor_Pos.x);
			//		Mouse.Set_dx(InRec.Event.MouseEvent.dwMousePosition.X);
			//		//	Mouse.Set_dy(Cursor_Pos.y);
			//		Mouse.Set_dy(InRec.Event.MouseEvent.dwMousePosition.Y);
			//		cout << InRec.Event.MouseEvent.dwMousePosition.X << "," <<
			//			InRec.Event.MouseEvent.dwMousePosition.Y << "  " << flush;
			//	}
			//	else if (InRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
			//		//else if (InRec.Event.MouseEvent.dwEventFlags == FROM_LEFT_1ST_BUTTON_PRESSED)
			//	{
			//		Mouse.Set_dwFlags(InRec.Event.MouseEvent.dwEventFlags);
			//		cout << InRec.Event.MouseEvent.dwMousePosition.X << "," <<
			//			InRec.Event.MouseEvent.dwMousePosition.Y << "  " << flush;
			//	}
			//	else if (InRec.Event.MouseEvent.dwEventFlags == FROM_LEFT_2ND_BUTTON_PRESSED)
			//	{
			//		Mouse.Set_dwFlags(InRec.Event.MouseEvent.dwEventFlags);
			//	}
			//	else if (InRec.Event.MouseEvent.dwEventFlags == FROM_LEFT_3RD_BUTTON_PRESSED)
			//	{
			//		Mouse.Set_dwFlags(InRec.Event.MouseEvent.dwEventFlags);
			//	}
			//}
		//}
	//	GetNumberOfConsoleInputEvents(H_IN, &event);
		/*while (event > 0)
		{
			if (InRec.EventType == MOUSE_EVENT)
			{
				if (InRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
				{
					GetCursorPos(&Cursor_Pos);
					Mouse.Set_dx(Cursor_Pos.x);
					Mouse.Set_dy(Cursor_Pos.y);
				}
				else if (InRec.Event.MouseEvent.dwEventFlags == FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					Mouse.Set_dwFlags(InRec.Event.MouseEvent.dwEventFlags);
				}
				else if (InRec.Event.MouseEvent.dwEventFlags == FROM_LEFT_2ND_BUTTON_PRESSED)
				{
					Mouse.Set_dwFlags(InRec.Event.MouseEvent.dwEventFlags);
				}
				else if (InRec.Event.MouseEvent.dwEventFlags == FROM_LEFT_3RD_BUTTON_PRESSED)
				{
					Mouse.Set_dwFlags(InRec.Event.MouseEvent.dwEventFlags);
				}
			}
		}*/
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
		for (size_t i = 0; i < mouse_moves.size(); ++i)
		{
			//SetCursorPos(mouse_moves[i].get_dx(), mouse_moves[i].get_dy());
			//mouse_event(mouse_moves[i].get_dwFlags(), mouse_moves[i].get_dx(), mouse_moves[i].get_dy(), NULL, NULL);
			//mouse_event(mouse_moves[i].get_dwFlags(), mouse_moves[i].get_dx(), mouse_moves[i].get_dy(), NULL, NULL);
			//SetCursorPos(mouse_moves[i].first, mouse_moves[i].second);
			//SetCursorPos(mouse_moves[i].first, mouse_moves[i].second);
			/*if (mouse_moves[i].get_dx() != 0 || mouse_moves[i].get_dy() != 0)
			{
				SetCursorPos(mouse_moves[i].get_dx(), mouse_moves[i].get_dy());
			}*/
			//std::cout << mouse_moves[i].get_dx() << ' ' << mouse_moves[i].get_dy() << '\n';
		/*	mouse_moves[i].show_obj();
			if (is_pressed_LBM == true)
			{
				SetCursorPos(mouse_moves[i].get_dx(), mouse_moves[i].get_dy());
				mouse_moves[i].left_mouse_click_up();
			}
			else if (is_pressed_RBM == true)
			{
				SetCursorPos(mouse_moves[i].get_dx(), mouse_moves[i].get_dy());
				mouse_moves[i].right_mouse_click_up();
			}*/
			if (mouse_moves[i].get_dx() != 0 || mouse_moves[i].get_dy() != 0)
			{
				SetCursorPos(mouse_moves[i].get_dx(), mouse_moves[i].get_dy());
				if (mouse_moves[i].get_dwFlags() == 1)
				{
					//mouse_moves[i].right_mouse_click_down();
					is_pressed_LBM = true;
					is_pressed_RBM = false;
					mouse_moves[i].left_mouse_click();
					//mouse_moves[i].left_mouse_click_up();
				}
				else if (mouse_moves[i].get_dwFlags() == 2)
				{
					//mouse_moves[i].left_mouse_click_down();
					is_pressed_LBM = false;
					is_pressed_RBM = true;
					mouse_moves[i].right_mouse_click();
					//mouse_moves[i].right_mouse_click_up();
				}
				else
				{
					is_pressed_LBM = false;
					is_pressed_RBM = false;
					//mouse_moves[i].left_mouse_click_down();
					//mouse_moves[i].right_mouse_click_down();
				}
			}
			//if (is_pressed_LBM == true)
			//{
			//	//mouse_moves[i].left_mouse_click();
			//}
			//else if (is_pressed_RBM == true)
			//{
			////	mouse_moves[i].right_mouse_click();
			//}
			//else
			//{
			//	
			//}
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		//turn off the used buttons
		//mouse_moves[mouse_moves.size() - 1].left_mouse_click_down();
		//mouse_moves[mouse_moves.size() - 1].right_mouse_click_down();
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