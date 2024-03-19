#pragma once
#include <string>

#define STRTOWSTR(str) std::wstring(str.begin(), str.end())
#define WSTRTOSTR(wstr) std::string(wstr.begin(), wstr.end())

#define CHARTOWCHAR(cstr) Window::CharToWChar(cstr)