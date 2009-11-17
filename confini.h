/*
 * =====================================================================================
 *
 *       Filename:  confini.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月17日 09时35分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */


#ifndef CONF_INI_HEADER_H_
#define CONF_INI_HEADER_H_


#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class ConfIni
{

	public:
		ConfIni();
		~ConfIni();
	public:
		static void init();
		static void load();
		static void save();

		static wstring getAccount(){ return _account;}
		static wstring getPassword(){ return _password;}
		static bool isRememberPassword(void) { return _remember_password > 0; };
		static void setAccount(const wstring& account) { _account = account; };
		static void setPassword(const wstring& password) { _password = password; };
		static void setRememberPassword(bool remember_password) { _remember_password = remember_password ? 1 : 0; };

		static wstring getTwitterApi() { return _twitter_api;}
		static void setTwitterApi(const wstring& twitter_api){_twitter_api = twitter_api;}

		static unsigned long getUpdateInterval(){return _update_interval;};
		static void setUpdateInterval(unsigned long inter_){ _update_interval = inter_;};

	private:
		static wstring _account;
		static wstring _password;
		static wstring _twitter_api;
		static unsigned long _remember_password;
		static unsigned long _update_interval;

















};
#endif
