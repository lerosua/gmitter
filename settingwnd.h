/*
 * =====================================================================================
 * 
 *       Filename:  settingwnd.h
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

#ifndef  SETTINGWND_FILE_HEADER_INC
#define  SETTINGWND_FILE_HEADER_INC

#include <mzfc_inc.h>
#define MZ_IDC_SCROLLWIN 900
#define MZ_IDC_TOOLBAR3 901
#define MZ_IDC_CAPTION 907
#define MZ_IDC_API_EDIT 908
#define MZ_IDC_BTN_SAVE 909
#define MZ_IDC_BTN_TEXT 910
#define MZ_IDC_BTN_API  911
#define MZ_IDC_CAPTION_API 912


class SettingWnd:public CMzWndEx
{
	MZ_DECLARE_DYNAMIC(SettingWnd);
	public:
	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);

	protected:
	UiScrollWin m_ScrollWin;
	UiToolbar_Text m_Toolbar;
	UiEdit* m_pEdit;
	// login setting
	UiCaption m_Caption;
	UiButton	m_BtnSP;
	UiStatic	m_BSP_Text;
	UiCaption m_CaptionApi;
	UiSingleLineEdit m_Api;
	UiCaption m_CaptionInterval;
	
	
};

#endif   /* ----- #ifndef SETTINGWND_FILE_HEADER_INC  ----- */

