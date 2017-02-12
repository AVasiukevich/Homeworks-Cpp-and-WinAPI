//#include <windows.h>
//#include <tchar.h>
//#include <iostream>
//#include <string> 
//
//typedef std::basic_string<TCHAR> tstring;
//#ifdef UNICODE 
//#define to_tstring std::to_wstring 
//#endif
// 
//INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
//{
//	int size = 0;
//	tstring resume[3] = { TEXT("Bush Arnold"), TEXT("Date of Birth: 07.01.1981"), TEXT("Professional skills: Hibernate, Spring") };
//	for (int i = 0; i < 3; ++i)
//	{
//		size += resume[i].size();
//		if (i == 2)
//		{
//			tstring title = TEXT("Average number of characters: ") + to_tstring(size / 3);
//			MessageBox(0, resume[i].c_str(), title.c_str(), MB_OK);
//		}
//		else
//			MessageBox(0, resume[i].c_str(), TEXT("Resume!"), MB_OK);
//	}
//	return 0;
//}