#include "_Mouse_Recorder.hpp"

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

_Mouse_Recorder::_Mouse_Recorder() :
	m_start(),
	m_stop(),
	minute(0),
	second(0)
{
	/*t = time(0);
	now = localtime(&t);*/
}

void _Mouse_Recorder::Record()
{
	//seconds = now->tm_sec;
	//minutes = now->tm_min;
	m_start = high_resolution_clock::now();
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
	m_stop = high_resolution_clock::now();
	second = duration_cast<seconds>(clock::now() - m_start).count();
	if (second % 5 == 0 && second > 0)
	{
		++minute;
		/*m_start.*/
		second = 0;
	}
	cout << "Elapsed time: " << minute << ':' << second << '\n';
	//
	//if ((m_stop - m_start).count() == 5)
	//{
	//	++minutes;
	//}
	////cout << "It took me equal: " << duration_cast<seconds>(m_stop - m_start).count() << " seconds" << endl;
	//cout << "Elapsed time: " << minutes << ':' << duration_cast<seconds>(m_stop - m_start).count() << '\n';
	////system("cls");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	//std::chrono::steady_clock::time_point Restart();
}

_Mouse_Recorder::~_Mouse_Recorder()
{

}