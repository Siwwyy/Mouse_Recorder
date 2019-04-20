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

LONG _Mouse_Recorder::get_cursor_position_x() const
{
	return Cursor_Pos.x;
}

LONG _Mouse_Recorder::get_cursor_position_y() const
{
	return Cursor_Pos.y;
}

_Mouse_Recorder::_Mouse_Recorder() :
	minute(0),
	second(0)
{
	/*t = time(0);
	now = localtime(&t);*/
	H_OUT = GetStdHandle(STD_OUTPUT_HANDLE);
	H_IN = GetStdHandle(STD_INPUT_HANDLE);
}

void _Mouse_Recorder::Record()
{
	//seconds = now->tm_sec;
	//minutes = now->tm_min;
//	m_start = high_resolution_clock::now();
	m_start = clock::now();
	bool record = true;
	while (record == true)
	{
		
		
		Clock();
		/*std::cin.get();*/
	//	system("cls");
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
	SetCursorPosition(get_cursor_position_x() + 1, get_cursor_position_y() + 1);
	Clock_Format();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	Erase_Row(get_cursor_position_x() + 1, get_cursor_position_y() + 1);
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