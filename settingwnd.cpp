/*
 * =====================================================================================
 *
 *       Filename:  settingwnd.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月01日 21时29分50秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  Cyclone
 *
 * =====================================================================================
 */

#include "settingwnd.h"


BOOL SettingWnd::OnInitDialog()
{
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }

    m_Caption.SetID(MZ_IDC_CAPTION);
    m_Caption.SetPos(0,0,GetWidth(),100);
    //m_Caption.SetText(L"Setting");
    m_Caption.SetText(L"设置");
    AddUiWin(&m_Caption);

    m_BSP_Text.SetID(MZ_IDC_BTN_TEXT);
    m_BSP_Text.SetPos(MZM_MARGIN_MAX,100,100,80);
    m_BSP_Text.SetDrawTextFormat(DT_LEFT|DT_VCENTER);
    m_BSP_Text.SetText(L"保存密码");
    AddUiWin(&m_BSP_Text);

    m_BtnSP.SetID(MZ_IDC_BTN_SAVE);
    m_BtnSP.SetPos(GetWidth()-150,100,120, 80);
    m_BtnSP.SetButtonType(MZC_BUTTON_SWITCH);
    m_BtnSP.SetButtonMode(MZC_BUTTON_MODE_HOLD);
    AddUiWin(&m_BtnSP);

    m_Api.SetPos(MZM_MARGIN_MAX,190,     GetWidth()-MZM_MARGIN_MAX*4,50);
    m_Api.SetID(MZ_IDC_API_EDIT); //you must set an unique ID for a edit control
    //m_Api.SetTip(L"Account:");	// set the tips text
    m_Api.SetTip(L"API地址");	// set the tips text
    m_Api.SetTextColor(RGB(255,0,0)); // you could also set the color of text
    AddUiWin(&m_Api);


    m_Toolbar.SetID(MZ_IDC_TOOLBAR3);
    m_Toolbar.SetPos(0,GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR,GetWidth(),MZM_HEIGHT_TEXT_TOOLBAR);
    m_Toolbar.SetButton(0,true,true,L"Cannel");
    m_Toolbar.SetButton(0,true,true,L"取消");
    //m_Toolbar.SetButton(2,true,true,L"Save");
    m_Toolbar.SetButton(2,true,true,L"保存");
    AddUiWin(&m_Toolbar);
    
    return TRUE;

}

void SettingWnd::OnMzCommand(WPARAM wParam,LPARAM lParam)
{

    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
	    case MZ_IDC_TOOLBAR3:
	    {
		    int nIndex=lParam;
		    if(nIndex==0){
			    /*退出发送窗口*/
			    EndModal(ID_CANCEL);
			    return;
		    }
		    if(2==nIndex){
			    /*发送处理*/
			    CMzString str(256);
			    wsprintf(str.C_Str(),L"The system Save the configure");

			MzMessageBoxEx(m_hWnd, str.C_Str(), L"", MB_OK, false);
			    EndModal(ID_OK);

		    }
	    }
	    break;

	}
}


