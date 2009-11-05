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
#define MZ_IDC_TOOLBAR3 101
#define MZ_IDC_CAPTION 107
#define MZ_IDC_API_EDIT 108
#define MZ_IDC_BTN_SAVE 109
#define MZ_IDC_BTN_TEXT 110


class SettingWnd:public CMzWndEx
{
	MZ_DECLARE_DYNAMIC(SettingWnd);
	public:
	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);

	protected:
	UiToolbar_Text m_Toolbar;
	UiEdit* m_pEdit;
	UiCaption m_Caption;
	UiButton	m_BtnSP;
	UiStatic	m_BSP_Text;
	UiSingleLineEdit m_Api;
	
};

#endif   /* ----- #ifndef SETTINGWND_FILE_HEADER_INC  ----- */

