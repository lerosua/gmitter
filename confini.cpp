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
#include "base64.h"

ConfIni::ConfIni()
{

}

ConfIni::~ConfIni()
{

}

void ConfIni::init()
{
	std::ifstream file(rcFile);
	if(!file){
	    save();
    }
    else{
	    load();
    }


}

void ConfIni::load()
{
	
    ifstream rc_File;
    rc_File.open(rcFile, ifstream::in);
    if (rc_File.is_open()) {
        while (!rc_File.eof()) {
            string str;
            getline(rc_File, str);
            if (!str.empty())
                parseString(str);
        }
	rc_File.close();
    }

}

void ConfIni::save()
{
    ofstream rc_File;
    rc_File.open(rcFile, ifstream::out);
    if (rc_File.is_open()) {
        rc_File << "Username = " << base64_encode(ws2s(_account)) << endl;
	if(_remember_password)
		rc_File << "Password = " << base64_encode(ws2s(_password)) << endl;
	else
		rc_File << "Password = " <<endl;

	rc_File << "Twitter_api = "<<ws2s(_twitter_api)<<endl;
        rc_File.close();
    }

}
void ConfIni::parseString(string str) {
    size_t pos;
    pos = str.find(' ');
    pos = str.find(' ', pos + 1);
    if (str.find("Username") == 0)
        _account = s2ws(base64_decode(str.substr(pos + 1, str.length() - pos)));
    if (str.find("Password") == 0)
        _password = s2ws(base64_decode(str.substr(pos + 1, str.length() - pos)));
    if (str.find("Twitter_api") == 0)
	_twitter_api = s2ws(str.substr(pos+1,str.length()-pos));
    if (str.find("remember_password") == 0)
	    _remember_password = str.substr(pos+1,str.length()-pos) =="true"?1:0;
    if (str.find("update_interval") == 0){
	    std::string str_inter_;
	    str_inter_ = str.substr(pos+1,str.length()-pos);
    }
}


wstring ConfIni::_account=L"";
wstring ConfIni::_password=L"";
wstring ConfIni::_twitter_api=L"http://li2z.cn/t/";
int ConfIni::_remember_password=1;
int ConfIni::_update_interval=3;  //3 mintue;
int ConfIni::_page_count=30;




