#include "App.h"
#include <sstream>

//Window Proccess

#define TOWSTR(str) std::wstring(str.begin(), str.end())




int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR pCmdLine,
	int nCmdShow
)
{
	try
	{
		return App{ pCmdLine }.Go();
	}
	catch (const MyException& e)
	{
		MessageBox(nullptr, CHARTOWCHAR(e.what()), CHARTOWCHAR(e.GetType()), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, CHARTOWCHAR(e.what()), L"Standar Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...) 
	{
		MessageBox(nullptr, L"No Details Available", L"Uknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	
	return -1;
}


