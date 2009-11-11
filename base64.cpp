/*
  Copyright (c) 2005-2009 by Jakob Schroeter <js@camaya.net>
  This file is part of the gloox library. http://camaya.net/gloox

  This software is distributed under a license. The full license
  agreement can be found in the file LICENSE in this distribution.
  This software may not be copied, modified, sold or distributed
  other than expressed in the named license agreement.

  This software is distributed without any warranty.
 */



#include "base64.h"

using namespace std;

static const std::string alphabet64("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
static const char pad = '=';
static const char np = (char) std::string::npos;
static char table64vals[] = {
    62, np, np, np, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, np, np, np, np, np,
    np, np, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, np, np, np, np, np, np, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
};

inline char table64(unsigned char c) {
    return ( c < 43 || c > 122) ? np : table64vals[c - 43];
}

string base64_encode(const string& input) {
    string encoded;
    char c;
    const unsigned int length = input.length();

    encoded.reserve(length * 2);

    for (unsigned int i = 0; i < length; ++i) {
        c = (input[i] >> 2) & 0x3f;
        encoded += alphabet64[c];

        c = (input[i] << 4) & 0x3f;
        if (++i < length)
            c |= ((input[i] >> 4) & 0x0f);
        encoded += alphabet64[c];

        if (i < length) {
            c = (input[i] << 2) & 0x3c;
            if (++i < length)
                c |= (input[i] >> 6) & 0x03;
            encoded += alphabet64[c];
        } else {
            ++i;
            encoded += pad;
        }

        if (i < length) {
            c = input[i] & 0x3f;
            encoded += alphabet64[c];
        } else {
            encoded += pad;
        }
    }

    return encoded;
}

string base64_decode(const string& input) {
    char c, d;
    const unsigned int length = input.length();
    string decoded;

    decoded.reserve(length);

    for (std::string::size_type i = 0; i < length; ++i) {
        c = table64(input[i]);
        ++i;
        d = table64(input[i]);
        c = (c << 2) | ((d >> 4) & 0x3);
        decoded += c;
        if (++i < length) {
            c = input[i];
            if (pad == c)
                break;

            c = table64(input[i]);
            d = ((d << 4) & 0xf0) | ((c >> 2) & 0xf);
            decoded += d;
        }

        if (++i < length) {
            d = input[i];
            if (pad == d)
                break;

            d = table64(input[i]);
            c = ((c << 6) & 0xc0) | d;
            decoded += c;
        }
    }

    return decoded;
}

std::string ws2s(const wstring& inputws)
{ 
        return WChar2Ansi(inputws.c_str()); 
}

std::string ws2s_utf8(const wstring& inputws)
{ 
        return WChar2UTF8(inputws.c_str()); 
}

std::wstring s2ws(const string& s)
{
     return Ansi2WChar(s.c_str(),s.size());
}

std::string WChar2Ansi(LPCWSTR pwszSrc)
{
         int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
 
         if (nLen<= 0) return std::string("");
 
         char* pszDst = new char[nLen];
         if (NULL == pszDst) return std::string("");
 
         WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
         pszDst[nLen -1] = 0;
 
         std::string strTemp(pszDst);
         delete [] pszDst;
 
         return strTemp;
}

std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen)
 
{
    int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);
    if(nSize <= 0) return NULL;
 
         WCHAR *pwszDst = new WCHAR[nSize+1];
    if( NULL == pwszDst) return NULL;
 
    MultiByteToWideChar(CP_ACP, 0,(LPCSTR)pszSrc, nLen, pwszDst, nSize);
    pwszDst[nSize] = 0;
 
    if( pwszDst[0] == 0xFEFF)                    // skip Oxfeff
        for(int i = 0; i < nSize; i ++) 
                            pwszDst[i] = pwszDst[i+1]; 
 
    wstring wcharString(pwszDst);
         delete pwszDst;
 
    return wcharString;
}


BOOL WCharToMByte_UTF8(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwMaxSize)
{
	size_t dwSize = WideCharToMultiByte(CP_UTF8,NULL,lpcwszStr,-1,NULL,0,NULL,FALSE);
	if(dwSize > dwMaxSize)
	{
		return FALSE;
	}
	WideCharToMultiByte(CP_UTF8,NULL,lpcwszStr,-1,lpszStr,dwSize,NULL,FALSE);
	return TRUE;
}


std::string WChar2UTF8(LPCWSTR pwszSrc)
{
         int nLen = WideCharToMultiByte(CP_UTF8, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
 
         if (nLen<= 0) return std::string("");
 
         char* pszDst = new char[nLen];
         if (NULL == pszDst) return std::string("");
 
         WideCharToMultiByte(CP_UTF8, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
         pszDst[nLen -1] = 0;
 
         std::string strTemp(pszDst);
         delete [] pszDst;
 
         return strTemp;
}
