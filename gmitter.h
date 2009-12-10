/*
 * =====================================================================================
 * 
 *       Filename:  gmitter.h
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

#ifndef  GMITTER_FILE_HEADER_INC
#define  GMITTER_FILE_HEADER_INC

#include <string>
#include <windows.h>
#include "httputils.h"

using namespace std;
class GMitter
{
public:
	GMitter();
	bool Login(const std::string& account,const std::string& password,const std::string& source_="");
	bool fakeLogin(const std::string& account,const std::string& password);
	void SetStatus(const std::string& msg);
	void SetStatus(const std::wstring& wmsg);
	std::string toPercent(std::string str);
	bool GetNetStatus();
	bool sGet(std::string req="");
	bool sPost(std::string where="",std::string params="");
	void UpdateStatus(const std::string& mid="");
	void UpdateMentions(const std::string& id_="");
	void UpdateDM(const std::string& id_="");
	void UpdatePublic();
	void SetApi(const std::string& api_);
private:
	std::string tw_uname;
	std::string tw_pass;
	std::string tw_version;
	std::string tw_host;
	std::string tw_api;
	std::string tw_source;
	int tw_request; // set get/post request
	static int status;
	/** net status,0 is ok,~0 is fail*/
	static bool netstat;








};


#endif   /* ----- #ifndef GMITTER_FILE_HEADER_INC  ----- */

