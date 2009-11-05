/*
 * =====================================================================================
 * 
 *       Filename:  gmitter.h
 * 
 *    Description:  twitter api的核心部�? * 
 *        Version:  1.0
 *        Created:  2009�?1�?2�?19�?2�?5�?CST
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
#include "happyhttp.h"

using namespace std;
class GMitter
{
public:
	GMitter();
	void SetStatus(std::string msg);
	std::string toPercent(std::string str);
	void OnBegin(const happyhttp::Response* r, void* userdata);
	void OnComplete(const happyhttp::Response* r, void* userdata) ;
private:
	std::string tw_uname;
	std::string tw_pass;
	std::string tw_version;
	int status;








};


#endif   /* ----- #ifndef GMITTER_FILE_HEADER_INC  ----- */

