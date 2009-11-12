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


GMitter::GMitter()
{
	tw_uname="pytw";
	tw_pass="bones7456";
	tw_version="0.1";
	status = 0;
	netstat=false;
}

void GMitter::Login(const std::string& account,const std::string& password)
{
	tw_uname=account;
	tw_pass = password;
}

void GMitter::OnBegin(const happyhttp::Response* r, void* userdata) {
    status = r->getstatus();
}

bool GMitter::GetNetStatus()
{
	bool net = netstat;
	netstat=false;
	
	return net;
}
void GMitter::OnComplete(const happyhttp::Response* r, void* userdata) {
    switch (status) {
        case 200:
		netstat=true;
            
            //cout << "OK" << endl;
            //saveSettings();
            break;
        case 401:
        {
            //cout << "Error: Wrong username or password." << endl;
        
		netstat=false;
            break;
        }
        case 403:
            ////cout << "Error: You have reached the limit of updating status." << endl;
                       exit(0);
            break;
        case 500:
            //cout << "Internal Server Error" << endl;
		netstat=false;
            //exit(0);
            break;

        default:
            //cout << "Twiny didn't found description of error" << endl;
            //cout << "Please send this to author: " << endl;
            //cout << r->getstatus() << " " << r->getreason() << endl;
		netstat=false;
			break;
    }


    /*
    # 1,000 total updates per day, on any and all devices (web, mobile web, phone, API, etc. )
    # 250 total direct messages per day, on any and all devices
    # 150 API requests per hour
     */
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


    string params = "status=" + toPercent(mes)+ "&source=_gmitter_";
    int len = params.length();

    string enc;
	string tmp;
    tmp = tw_uname + ':' + tw_pass;
    //enc = base64_encode(reinterpret_cast<const unsigned char*> (enc.c_str()), enc.length());
    enc=base64_encode(tmp);
    happyhttp::Connection conn("li2z.cn", 80);
    //happyhttp::Connection conn("lfeng.cn",80);
    //conn.setcallbacks(OnBegin, 0, OnComplete, 0);

    conn.putrequest("POST", "/t/statuses/update.xml");
    //conn.putrequest("POST", "/api/statuses/update.xml");
    conn.putheader("Authorization", "Basic " + enc);
    conn.putheader("Accept", "*/*");
    conn.putheader("Accept-Charset", "utf-8");
    conn.putheader("User-Agent", "_gmitter_");
	conn.putheader("X-Twitter-Client", "_gmitter_");
	conn.putheader("X-Twitter-Client-Version", tw_version);
	conn.putheader("X-Twitter-Client-URL", "http://lerosua.org/gmitter");
	conn.putheader("Connection", "close");
	conn.putheader("Content-Length", len);
	conn.putheader("Content-Type", "application/x-www-form-urlencoded");

	conn.endheaders();

	conn.send((const unsigned char*)(params.c_str()), len);

	while (conn.outstanding())
		conn.pump();
}

