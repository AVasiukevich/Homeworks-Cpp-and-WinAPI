#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <string> 
#include <ctime>

typedef std::basic_string<TCHAR> tstring;
#ifdef UNICODE 
#define to_tstring std::to_wstring 
#endif

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	srand(static_cast<unsigned int>(time(0)));
	int repeat = 0;
	do
	{
		int count = 0;
		MessageBox(0, TEXT("Remember the numbers ranging from 1 to 100!"), TEXT("Start!"), MB_OK | MB_ICONEXCLAMATION);
		do
		{
			tstring number = TEXT("Number: ") + to_tstring(rand() % 101);
			repeat = MessageBox(0, number.c_str(), TEXT("Guessed?"), MB_YESNO | MB_ICONQUESTION);
			++count;
		} while (repeat == 7);
		tstring count_str = TEXT("Number of attempts: ") + to_tstring(count);
		MessageBox(0, count_str.c_str(), TEXT("Number of attempts!"), MB_OK | MB_ICONINFORMATION);

		repeat = MessageBox(0, TEXT("Want to play again?"), TEXT("Repeat?"), MB_YESNO | MB_ICONQUESTION);
	} while (repeat == 6);

	return 0;
}