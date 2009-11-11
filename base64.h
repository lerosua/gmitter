#ifndef BASE_64_HH_
#define BASE_64_HH_

#include <string>
#include <windows.h>
#include <mzfc_inc.h>

#define rcFile L"\\Disk\\Program Files\\gmitter\\gmitter.ini"
//#define _UNICODE
using namespace std;

string base64_encode(const string& input);
string base64_decode(const string& input);
std::wstring s2ws(const std::string& s);
std::string ws2s(const std::wstring& ws);
std::string ws2s_utf8(const std::wstring& ws);
std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen);
std::string WChar2Ansi(LPCWSTR pwszSrc);
std::string WChar2UTF8(LPCWSTR pwszSrc);
BOOL WCharToMByte_UTF8(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwMaxSize);

bool FileExists(TCHAR* filename);
#endif
