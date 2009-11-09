/*
 * =====================================================================================
 * 
 *       Filename:  saywnd.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  2009年11月01日 21时19分29秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  Cyclone
 * 
 * =====================================================================================
 */

#ifndef  SAYWND_FILE_HEADER_INC
#define  SAYWND_FILE_HEADER_INC

#include <mzfc_inc.h>
#define MZ_IDC_TOOLBAR4 141
#define MZ_IDC_CAPTION4 147
#define MZ_IDC_EDIT4 148


//class MainWnd;
class SayWnd:public CMzWndEx
{
	MZ_DECLARE_DYNAMIC(SayWnd);
	public:
	//SayWnd(MainWnd&);
	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
	
	protected:
	UiToolbar_Text m_Toolbar;
	UiEdit m_pEdit;
	UiCaption m_Caption;
	private:
	//MainWnd& m_pwnd;
	
};

#endif   /* ----- #ifndef SAYWND_FILE_HEADER_INC  ----- */

