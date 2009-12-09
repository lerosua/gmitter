/*
 * =====================================================================================
 *
 *       Filename:  gmitter.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  Cyclone
 *
 * =====================================================================================
 */

#include "gmitter.h"
#include "base64.h"
#include <fstream>

bool GMitter::netstat=false;
int GMitter::status = 0;
GMitter::GMitter()
{
	tw_uname="";
	tw_pass="";
	tw_version="1.0";
	tw_request=0;
	tw_source="twidroid";
}
bool GMitter::fakeLogin(const std::string& account,const std::string& password)
{
	tw_uname=account;
	tw_pass = password;

	return true;
}



bool GMitter::Login(const std::string& account,const std::string& password,const std::string& source_)
{
	tw_uname=account;
	tw_pass = password;
	if(!source_.empty())
		tw_source=source_;

	std::string res=tw_api+"/account/verify_credentials.json";
	return sGet(res.c_str());

}

bool GMitter::GetNetStatus()
{
	
	return true;
}
string GMitter::toPercent(std::string str) {
    string ret;
    static const char HEX[17] = "0123456789ABCDEF";
    string incSymb = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int b = 0, e;

    while ((e = str.find_first_not_of(incSymb, b)) != string::npos) {
        ret.append(str, b, e - b);

        ret += '%';
        ret += HEX[(str[e] >> 4) & 0xF];
        ret += HEX[(str[e] >> 0) & 0xF];

        b = e + 1;
    }
    ret.append(str, b, str.length() - b);

    return ret;
}
void GMitter::SetStatus(const std::wstring& wmes)
{
	std::string mes=ws2s_utf8(wmes);
	SetStatus(mes);


}

void GMitter::SetStatus(const std::string& mes)
{

	std::string url_ = tw_api+"/statuses/update.xml";
	string params = "status=" + toPercent(mes)+ "&source="+tw_source;

	sPost(url_,params);

}


bool GMitter::sPost(std::string where,std::string params)
{

    string enc;
    string tmp;
    tmp = tw_uname + ':' + tw_pass;
    enc=base64_encode(tmp);
    string auth="Authorization: Basic ";
    auth+=enc;

    return HttpUtils::httpPost(s2ws(tw_host).c_str(),80, s2ws(where).c_str(), s2ws(auth).c_str(),params.c_str(),NULL);

 }

void GMitter::UpdateStatus(const std::string& mid)
{
	if(mid.empty()){
		std::string res=tw_api+"/statuses/friends_timeline.json?count=30";
		sGet(res.c_str());
		return;
	}
	std::string res=tw_api+"/statuses/friends_timeline.json?since_id=";
	res+=mid;
	sGet(res.c_str());

}
void GMitter::UpdateDM(const std::string& id_)
{

	if(id_.empty()){
		std::string res=tw_api+"/direct_messages.json?count=30";
		sGet(res.c_str());
		return;
	}
	std::string res=tw_api+"/direct_messages.json?since_id=";
	res+=id_;
	sGet(res.c_str());

}

void GMitter::UpdatePublic()
{

	std::string res=tw_api+"/statuses/public_timeline.json";
	sGet(res.c_str());

}
void GMitter::UpdateMentions(const std::string& id_)
{

	if(id_.empty()){
		std::string res=tw_api+"/statuses/mentions.json?count=30";
		sGet(res.c_str());
		return;
	}
	std::string res=tw_api+"/statuses/mentions.json?since_id=";
	res+=id_;
	sGet(res.c_str());

}

bool GMitter::sGet(std::string req)
{

    string enc;
    string tmp;
    tmp = tw_uname + ':' + tw_pass;
    enc=base64_encode(tmp);
    string auth="Authorization: Basic ";
    auth+=enc;
    long len;
    return HttpUtils::httpGet(s2ws(tw_host).c_str(),80, s2ws(req).c_str(),s2ws(auth).c_str(), updateFile, &len);
#if 0
    conn.putheader("Authorization", "Basic " + enc);

    conn.putheader("Accept", "*/*");
	conn.putheader("Accept-Charset", "utf-8");
    conn.putheader("User-Agent", "_gmitter_");
	conn.putheader("X-Twitter-Client", "_gmitter_");
	conn.putheader("X-Twitter-Client-Version", tw_version);
	conn.putheader("X-Twitter-Client-URL", "http://lerosua.org/gmitter");
	conn.putheader("Connection", "close");
	conn.putheader("Content-Type", "application/x-www-form-urlencoded");
	conn.endheaders();

	while (conn.outstanding())
		conn.pump();
#endif
}



void GMitter::SetApi(const std::string& api_)
{
	/** http://li2z.cn/t/ */
    size_t pos;
    size_t zpos;
    std::string str_;

    pos = 7;
    zpos = api_.find("http://");
    if(zpos==std::string::npos)
	    pos++;
    str_ = api_.substr(pos,api_.length()-pos);
    pos= str_.find("/");

    tw_host= str_.substr(0,pos);
    tw_api= str_.substr(pos,str_.length()-pos);
    
}
