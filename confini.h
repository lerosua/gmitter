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

		static void parseString(string str) ;
		static wstring getAccount(){ return _account;}
		static wstring getPassword(){ return _password;}
		static string  getSource() { return _twitter_source;}
		static void setSource(const wstring& source_){ _twitter_source = ws2s(source_) ;}
		static bool isRememberPassword(void) { return _remember_password > 0; };
		static void setAccount(const wstring& account) { _account = account; };
		static void setPassword(const wstring& password) { _password = password; };
		static void setRememberPassword(bool remember_password) { _remember_password = remember_password ? 1 : 0; };

		static wstring getTwitterApi() { return _twitter_api;}
		static void setTwitterApi(const wstring& twitter_api){_twitter_api = twitter_api;}

		static int getUpdateInterval(){return _update_interval;};
		static void setUpdateInterval(int inter_){ _update_interval = inter_;};

		static int getPageCount() { return _page_count; }
		static void setPageCount(int count_){ _page_count = count_ ; }
		static string int2string(int num_);
	private:
		static wstring _account;
		static wstring _password;
		static wstring _twitter_api;
		static string _twitter_source;
		static int _remember_password;
		static int _update_interval;
		static int _page_count;


};
#endif
