#include <Windows.h>
#include <stdio.h>
#include <iostream>
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
int main()
{
	printf("Hooking the keyboard\n");
	printf("Hooking the mouse\n");
	//Here we set the low level hook
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);
	mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseHookProc, 0, 0);
	printf("%X\n", keyboardHook);
	printf("%X\n", mouseHook);

	MSG message{};
	while (GetMessage(&message, NULL, 0, 0)) 
	{
	/*	if (break_loop == true)
		{
			system("pause");
		}*/
		TranslateMessage(&message);
		DispatchMessage(&message);
		//break;
	}
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
		std::cout << ((char)(key->vkCode)) << ' ';
		if (((char)(key->vkCode)) == '1')
		{
			break_loop = true;
		
		}
	}
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	HWND fwindow = GetForegroundWindow();
	//MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	PMSLLHOOKSTRUCT mouse = (PMSLLHOOKSTRUCT)lParam;
	//if (pMouseStruct != NULL)
//	{
		printf("Mouse position X = %d  Mouse Position Y = %d\n", mouse->pt.x, mouse->pt.y);
	//}
	//delete pMouseStruct;
	return CallNextHookEx(mouseHook,nCode, wParam, lParam);
}