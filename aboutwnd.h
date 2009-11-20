/*
 * =====================================================================================
 *
 *       Filename:  aboutwnd.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月20日 11时36分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#ifndef _ABOUT_WND_H_
#define _ABOUT_WND_H_

#define MZ_IDC_ABOUTWND_LOGO	300
#define MZ_IDC_ABOUTWND_TOOLBAR 301
#define MZ_IDC_ABOUTWND_TEXT    302


#include <mzfc_inc.h>

class AboutWnd: public CMzWndEx
{

	MZ_DECLARE_DYNAMIC(AboutWnd);
	public:
		AboutWnd();
		~AboutWnd();
	public:
		virtual BOOL OnInitDialog();
		virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
	private:
		  UiPicture	   m_Logo;
		  UiToolbar_Text m_Toolbar;
		  UiStatic	   m_text;








};

MZ_IMPLEMENT_DYNAMIC(AboutWnd)

#endif
