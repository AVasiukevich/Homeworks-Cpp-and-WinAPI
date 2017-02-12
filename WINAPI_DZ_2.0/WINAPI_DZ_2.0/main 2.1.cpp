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
		MessageBox(0, TEXT("��������� ����� � ��������� �� 1 �� 100!"), TEXT("������!"), MB_OK | MB_ICONEXCLAMATION);
		do
		{
			tstring number = TEXT("�� �������� �����: ") + to_tstring(rand() % 101);
			repeat = MessageBox(0, number.c_str(), TEXT("�������?"), MB_YESNO | MB_ICONQUESTION);
			++count;
		} while (repeat == 7);
		tstring count_str = TEXT("����� �������: ") + to_tstring(count);
		MessageBox(0, count_str.c_str(), TEXT("����� �������!"), MB_OK | MB_ICONINFORMATION);

		repeat = MessageBox(0, TEXT("������ ������� ��� ���?"), TEXT("��������?"), MB_YESNO | MB_ICONQUESTION);
	} while (repeat == 6);

	return 0;
}