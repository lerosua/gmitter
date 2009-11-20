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
#define MZ_IDC_POST_TOOLBAR 151
#define MZ_IDC_POST_CATION_TOP 157
#define MZ_IDC_POST_EDIT 158
#define MZ_IDC_POST_CAPTION_BOTTOM 159
#define MZ_IDC_POST_SCROLLWIN 160
#define MZ_IDC_POST_CLEAR	161


class MainWnd;
class SayWnd:public CMzWndEx
{
	MZ_DECLARE_DYNAMIC(SayWnd);
	public:
	SayWnd(MainWnd&);
	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnChar(TCHAR chCharCOde, LPARAM lKeyData);
	void SetText(const std::wstring& str_);
	
	protected:
	UiToolbar_Text m_Toolbar;
	UiEdit m_pEdit;
	UiCaption m_CaptionTop;
	UiCaption m_CaptionBottom;
	UiScrollWin m_ScrollWin;
	//UiButton_Image m_btn_clear;
	UiButton m_btn_clear;

	private:
	MainWnd& m_pwnd;
	
};

#endif   /* ----- #ifndef SAYWND_FILE_HEADER_INC  ----- */

