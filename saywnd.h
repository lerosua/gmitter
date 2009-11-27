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
#define MZ_IDC_POST_TOOLBAR_TOP 152


class MainWnd;
class SayWnd:public CMzWndEx
{
	MZ_DECLARE_DYNAMIC(SayWnd);
	public:
	SayWnd(MainWnd&);
	~SayWnd();
	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT MzDefWndProc(UINT  message,WPARAM wParam, LPARAM lParam);
	void SetText(const std::wstring& str_);
	//void onTimer(UINT_PTR nIDEvent);
	void ScreenRotate(int mode_);
	
	protected:
	UiToolbar_Text m_Toolbar;
	UiToolbar_Text m_Toolbar_Top;
	UiEdit m_pEdit;
	//UiCaption m_CaptionTop;
	//UiCaption m_CaptionBottom;
	UiScrollWin m_ScrollWin;
	//UiButton_Image m_btn_clear;
	//UiButton m_btn_clear;

	private:
	MainWnd& m_pwnd;
	int m_max_char;
	DWORD m_accMsg;
	
};

#endif   /* ----- #ifndef SAYWND_FILE_HEADER_INC  ----- */

