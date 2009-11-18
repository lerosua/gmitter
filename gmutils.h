/*
 * =====================================================================================
 *
 *       Filename:  gmutil.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月17日 13时32分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#ifndef GM_UTILS_HEADER_H_
#define  GM_UTILS_HEADER_H_

#include <mzfc_inc.h>
#include <string>

#define MZ_IDC_POPMENU_REPLY  500
#define MZ_IDC_POPMENU_RT     501
#define MZ_IDC_POPMENU_DM 502
#define MZ_IDC_POPMENU_RETURN   503

using namespace std;

class GMUtils
{

public:
	GMUtils();
	~GMUtils();

public:
	static int popup_menu_status(HWND hparentwnd, const wstring& user_id);
	//static void edit_post_status_wnd(HWND hparentwnd,MainWnd* mwnd,const wstring& str_);


};




#endif


