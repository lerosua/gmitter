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
#include "setinterwnd.h"
#include "pagecountwnd.h"
#include "setsourcewnd.h"

#define MZ_IDC_SETTINGWND_SCROLLWIN 900
#define MZ_IDC_SETTINGWND_TOOLBAR 901
#define MZ_IDC_SETTINGWND_CAPTION 907
#define MZ_IDC_SETTINGWND_API_EDIT 908
#define MZ_IDC_SETTINGWND_BTN_SAVE 909
#define MZ_IDC_SETTINGWND_BTN_TEXT 910
#define MZ_IDC_SETTINGWND_BTN_API  911
#define MZ_IDC_SETTINGWND_CAPTION_API 912
#define MZ_IDC_SETTINGWND_BTN_INTER 913
#define MZ_IDC_SETTINGWND_BTN_PAGECOUNT 914
#define MZ_IDC_SETTINGWND_CAPTION_SHOW 915
#define MZ_IDC_SETTINGWND_BTN_SOURCE   916

class SettingWnd:public CMzWndEx
{
	MZ_DECLARE_DYNAMIC(SettingWnd);
	public:
	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
	void update_inter_count();
	void update_page_count();
	void update_source();

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
	UiCaption m_Captionshow;
	UiButtonEx m_Btn_inter;
	UiButtonEx m_Btn_pagecount;
	UiButtonEx m_Btn_source;

	PageCountWnd  m_pageCountWnd;
	SetInterWnd    m_setInterWnd;
	SetSourceWnd   m_setSourceWnd;
	
	
	
};

#endif   /* ----- #ifndef SETTINGWND_FILE_HEADER_INC  ----- */

