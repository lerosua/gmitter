#ifndef BASE_64_HH_
#define BASE_64_HH_

#include <string>
#include <windows.h>

using namespace std;

//std::string base64_encode(unsigned char const* , unsigned int len);
//std::string base64_decode(std::string const& s);
string base64_encode(const string& input);
string base64_decode(const string& input);
std::wstring s2ws(const std::string& s);
std::string ws2s(const std::wstring& ws);
std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen);
std::string WChar2Ansi(LPCWSTR pwszSrc);

#endif
