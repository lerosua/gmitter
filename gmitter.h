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
#include "happyhttp.h"

using namespace std;
class GMitter
{
public:
	GMitter();
	bool Login(const std::string& account,const std::string& password);
	void SetStatus(const std::string& msg);
	void SetStatus(const std::wstring& wmsg);
	std::string toPercent(std::string str);
	static void OnBegin(const happyhttp::Response* r, void* userdata);
	static void OnComplete(const happyhttp::Response* r, void* userdata) ;
	static void OnData(const happyhttp::Response* r, void* userdata, const unsigned char* data, int n) ;
	bool GetNetStatus();
	void sGet(std::string req="");
	void sPost(std::string where="",std::string params="");
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
	int tw_request; // set get/post request
	static int status;
	/** net status,0 is ok,~0 is fail*/
	static bool netstat;








};


#endif   /* ----- #ifndef GMITTER_FILE_HEADER_INC  ----- */

