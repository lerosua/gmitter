/*
 * =====================================================================================
 * 
 *       Filename:  saywnd.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  2009��11��01�� 21ʱ19��29�� CST
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
#define MZ_IDC_STATUS_TOOLBAR 151
#define MZ_IDC_CAPTION_TOP 157
#define MZ_IDC_EDIT4 158
#define MZ_IDC_CAPTION_BOTTOM 159
#define MZ_IDC_POST_SCROLLWIN 160


class MainWnd;
class SayWnd:public CMzWndEx
{
	MZ_DECLARE_DYNAMIC(SayWnd);
	public:
	SayWnd(MainWnd&);
	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnChar(TCHAR chCharCOde, LPARAM lKeyData);
	
	protected:
	UiToolbar_Text m_Toolbar;
	UiEdit m_pEdit;
	UiCaption m_CaptionTop;
	UiCaption m_CaptionBottom;
	UiScrollWin m_ScrollWin;
	private:
	MainWnd& m_pwnd;
	
};

#endif   /* ----- #ifndef SAYWND_FILE_HEADER_INC  ----- */

