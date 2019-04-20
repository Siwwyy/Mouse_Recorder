#include "_Mouse_Recorder.hpp"

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

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
	bool record = true;
	while (record == true)
	{
		if (GetAsyncKeyState(VK_RSHIFT))
		{
			record = false;
		}
		Clock();
		GetCursorPos(&Cursor_Pos);
		mouse_moves.emplace_back(std::make_pair(Cursor_Pos.x, Cursor_Pos.y));
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
		for (size_t i = 0; i < mouse_moves.size(); ++i)
		{
			SetCursorPos(mouse_moves[i].first, mouse_moves[i].second);
			std::this_thread::sleep_for(std::chrono::seconds(1));
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