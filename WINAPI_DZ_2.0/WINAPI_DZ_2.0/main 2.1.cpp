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
		MessageBox(0, TEXT("Загадайте число в диапазоне от 1 до 100!"), TEXT("Начало!"), MB_OK | MB_ICONEXCLAMATION);
		do
		{
			tstring number = TEXT("Вы загадали число: ") + to_tstring(rand() % 101);
			repeat = MessageBox(0, number.c_str(), TEXT("Угадали?"), MB_YESNO | MB_ICONQUESTION);
			++count;
		} while (repeat == 7);
		tstring count_str = TEXT("Число попыток: ") + to_tstring(count);
		MessageBox(0, count_str.c_str(), TEXT("Число попыток!"), MB_OK | MB_ICONINFORMATION);

		repeat = MessageBox(0, TEXT("Хотите сыграть еще раз?"), TEXT("Повторим?"), MB_YESNO | MB_ICONQUESTION);
	} while (repeat == 6);

	return 0;
}