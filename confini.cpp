/*
 * =====================================================================================
 *
 *       Filename:  confini.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月17日 09时39分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#include "confini.h"

ConfIni::ConfIni()
{

}

ConfIni::~ConfIni()
{

}

void ConfIni::init()
{
    if(!FileExists(rcFile)){
	    IniCreateFile(rcFile);
	    save();
    }
    else{
	    load();
    }


}

void ConfIni::load()
{
	
	wchar_t *account = new wchar_t[64];
	IniReadString(L"Setting", L"account", &account, rcFile);
	_account = wstring(account);
	delete [] account;

	wchar_t* pass = new wchar_t[64];
	IniReadString(L"Setting",L"passowrd",&pass,rcFile);
	_password = wstring(pass);
	delete [] pass;

	IniReadInt(L"Setting", L"remember_password", &_remember_password, rcFile);
	IniReadInt(L"Setting", L"update_interval", &_update_interval,rcFile);

	wchar_t* api = new wchar_t[64];
	IniReadString(L"Setting",L"twitter_api",&api,rcFile);
	_twitter_api = wstring(api);
	delete [] api;
}

void ConfIni::save()
{

	wchar_t *account = new wchar_t[_account.length() + 1];
	memset(account, 0, sizeof(wchar_t) * (_account.length() + 1));
	_account.copy(account, _account.length());
	IniWriteString(L"Setting", L"account",account, rcFile);
	delete [] account;

	if (_remember_password)
	{
		wchar_t *password = new wchar_t[_password.length() + 1];
		memset(password, 0, sizeof(wchar_t) * (_password.length() + 1));
		_password.copy(password, _password.length());
		IniWriteString(L"Setting", L"password", password, rcFile);
		delete [] password;
	} else
	{
		IniWriteString(L"Setting", L"password", L"", rcFile);
	}

	IniWriteInt(L"Setting", L"remember_password", _remember_password, rcFile);
	IniWriteInt(L"Setting", L"update_interval",_update_interval,rcFile);


	wchar_t *twitter_api = new wchar_t[_twitter_api.length() + 1];
	memset(twitter_api, 0, sizeof(wchar_t) * (_twitter_api.length() + 1));
	_twitter_api.copy(twitter_api, _twitter_api.length());
	IniWriteString(L"Setting", L"twitter_api",_twitter_api,rcFile);
	delete [] twitter_api;


}



wstring ConfIni::_account;
wstring ConfIni::_password;
wstring ConfIni::_twitter_api;
unsigned long ConfIni::_remember_password=1;
unsigned long ConfIni::_update_interval=3;  //3 mintue;
unsigned long ConfIni::_page_count=30;

