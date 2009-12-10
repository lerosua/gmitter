/*
 * =====================================================================================
 *
 *       Filename:  httputil.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年12月09日 10时24分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#ifndef HTTP_UTILS_HEADER_INC_
#define HTTP_UTILS_HEADER_INC_

//#define _AFXDLL

#include <afxinet.h>
#include <iostream>
#include <string>

using namespace std;

namespace HttpUtils
{

	bool httpGet(LPCTSTR host,int nPort,LPCTSTR urlstr, LPCTSTR auth,const char* output_file_name, long* bytes_read);
	bool httpPost(LPCTSTR host,int nPort,LPCTSTR urlstr, LPCTSTR auth,const char* post_str, char* back_str);
	bool HttpDownFIle(LPCTSTR FileURL, LPCTSTR saveFile);



}

#endif

