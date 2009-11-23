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
#include "confini.h"
#include <sstream>
using namespace std;

BOOL SettingWnd::OnInitDialog()
{
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }

    m_ScrollWin.SetID(MZ_IDC_SETTINGWND_SCROLLWIN);
    m_ScrollWin.SetPos(0,0,GetWidth(),GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR);
    m_ScrollWin.EnableScrollBarV(true);
    AddUiWin(&m_ScrollWin);


    int y =0;
    m_Caption.SetID(MZ_IDC_SETTINGWND_CAPTION);
    m_Caption.SetPos(0,y,GetWidth(),MZM_HEIGHT_CAPTION);
    //m_Caption.SetText(L"Setting");
    m_Caption.SetText(L"设置");
    m_ScrollWin.AddChild(&m_Caption);

    y+= MZM_HEIGHT_CAPTION;
    
    m_BSP_Text.SetID(MZ_IDC_SETTINGWND_BTN_TEXT);
    m_BSP_Text.SetPos(MZM_MARGIN_BIG,y,GetWidth()/2-MZM_MARGIN_BIG,MZM_HEIGHT_BUTTONEX);
    m_BSP_Text.SetDrawTextFormat(DT_LEFT|DT_VCENTER);
    m_BSP_Text.SetText(L"保存密码");
    m_ScrollWin.AddChild(&m_BSP_Text);

    m_BtnSP.SetID(MZ_IDC_SETTINGWND_BTN_SAVE);
    m_BtnSP.SetPos(GetWidth()-150,y,150, MZM_HEIGHT_BUTTONEX);
    m_BtnSP.SetButtonType(MZC_BUTTON_SWITCH);
    m_BtnSP.SetButtonMode(MZC_BUTTON_MODE_HOLD);
    m_BtnSP.EnableNotifyMessage(true);
    m_ScrollWin.AddChild(&m_BtnSP);

    y+=MZM_HEIGHT_BUTTONEX;
    
    m_CaptionApi.SetID(MZ_IDC_SETTINGWND_CAPTION_API);
    m_CaptionApi.SetPos(0,y,GetWidth(),MZM_HEIGHT_CAPTION);
    m_ScrollWin.AddChild(&m_CaptionApi);

    y+=MZM_HEIGHT_CAPTION;

    m_Api.SetPos(MZM_MARGIN_MAX,y, GetWidth()-MZM_MARGIN_MAX*2,MZM_HEIGHT_BUTTONEX);
    m_Api.SetID(MZ_IDC_SETTINGWND_API_EDIT); //you must set an unique ID for a edit control
    //m_Api.SetTip(L"Account:");	// set the tips text
    m_Api.SetTip(L"API地址");	// set the tips text
    m_Api.SetTextColor(RGB(255,0,0)); // you could also set the color of text
    m_Api.EnableNotifyMessage(true);
    m_Api.SetSipMode(IM_SIP_MODE_WEB_LETTER);
    m_ScrollWin.AddChild(&m_Api);

    m_Btn_inter.SetPos(0,y,GetWidth(),MZM_HEIGHT_BUTTONEX);
    m_Btn_inter.SetID(MZ_IDC_SETTINGWND_BTN_INTER);
    m_Btn_inter.SetText(L"update time interval");
	wstringstream temp;
	temp << ConfIni::getUpdateInterval() << L"条";
    m_Btn_inter.SetText2(temp.str().c_str());
    m_Btn_inter.SetButtonType(MZC_BUTTON_LINE_BOTTOM);
    m_Btn_inter.EnableNotifyMessage(true);
    m_ScrollWin.AddChild(&m_Btn_inter);

	ImagingHelper* imgArrow = ImagingHelper::GetImageObject(GetMzResModuleHandle(), MZRES_IDR_PNG_ARROW_RIGHT, true);
	m_Btn_inter.SetImage2(imgArrow);
	m_Btn_inter.SetImageWidth2(imgArrow->GetImageWidth());
	m_Btn_inter.SetShowImage2(true);

    y+=MZM_HEIGHT_BUTTONEX;

    m_Btn_pagecount.SetPos(0,y,GetWidth(),MZM_HEIGHT_BUTTONEX);
    m_Btn_pagecount.SetID(MZ_IDC_SETTINGWND_BTN_PAGECOUNT);
    m_Btn_pagecount.SetText(L"Page Count");
    wstringstream temp_page;
    temp_page<<ConfIni::getPageCount()<<L"条";
    m_Btn_pagecount.SetText2(temp_page.str().c_str());
    m_Btn_pagecount.SetButtonType(MZC_BUTTON_LINE_BOTTOM);
    m_Btn_pagecount.EnableNotifyMessage(true);
    m_ScrollWin.AddChild(&m_Btn_pagecount);

    m_Toolbar.SetID(MZ_IDC_SETTINGWND_TOOLBAR);
    m_Toolbar.SetPos(0,GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR,GetWidth(),MZM_HEIGHT_TEXT_TOOLBAR);
    //m_Toolbar.SetButton(0,true,true,L"Cannel");
    m_Toolbar.SetButton(0,true,true,L"取消");
    //m_Toolbar.SetButton(2,true,true,L"Save");
    m_Toolbar.SetButton(2,true,true,L"保存");
    AddUiWin(&m_Toolbar);
    
    if(ConfIni::isRememberPassword())
	    m_BtnSP.SetState(MZCS_BUTTON_PRESSED);
    m_Api.SetText(ConfIni::getTwitterApi().c_str());
    return TRUE;

}

void SettingWnd::OnMzCommand(WPARAM wParam,LPARAM lParam)
{

    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
	    case MZ_IDC_SETTINGWND_TOOLBAR:
	    {
		    int nIndex=lParam;
		    if(nIndex==0){
			    /*退出发送窗口*/
			    EndModal(ID_CANCEL);
			    return;
		    }
		    if(2==nIndex){
			    ConfIni::setRememberPassword(MZCS_BUTTON_NORMAL != m_BtnSP.GetState());
			    ConfIni::setTwitterApi(m_Api.GetText().C_Str());
			    ConfIni::save();
			    
			    CMzString str(256);
			    wsprintf(str.C_Str(),L"配置保存中");
			MzAutoMsgBoxEx(m_hWnd, str.C_Str());
			    EndModal(ID_OK);

		    }
	    }
	    break;
	    case MZ_IDC_SETTINGWND_BTN_INTER:
	    {
		RECT rcWork = MzGetWorkArea();
		m_setInterWnd.set_select(ConfIni::getUpdateInterval());
		m_setInterWnd.CreateModalDialog(rcWork.left, rcWork.top, GetWidth(), GetHeight(), m_hWnd);
		m_setInterWnd.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_RIGHT_TO_LEFT_PUSH);
		m_setInterWnd.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);

			int nRet = m_setInterWnd.DoModal();
			ConfIni::setUpdateInterval(nRet);
			update_inter_count();

	    }
	    break;
	    case MZ_IDC_SETTINGWND_BTN_PAGECOUNT:
	    {
		RECT rcWork = MzGetWorkArea();
		m_pagecountwnd.set_select(ConfIni::getPageCount());
		m_pagecountwnd.CreateModalDialog(rcWork.left, rcWork.top, GetWidth(), GetHeight(), m_hWnd);
		m_pagecountwnd.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_RIGHT_TO_LEFT_PUSH);
		m_pagecountwnd.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);
		    int nRet= m_pagecountwnd.DoModal();
		    ConfIni::setPageCount(nRet);
		    update_page_count();
	    }
	    break;

	}
}


void SettingWnd::update_inter_count()
{
	wstringstream temp;
	temp << ConfIni::getUpdateInterval() << L"分钟";
	m_Btn_inter.SetText2(temp.str().c_str());
	m_Btn_inter.Invalidate();
	m_Btn_inter.Update();

}
void SettingWnd::update_page_count()
{
	wstringstream temp;
	temp <<ConfIni::getPageCount()<<L"条";
	m_Btn_pagecount.SetText2(temp.str().c_str());
	m_Btn_pagecount.Invalidate();
	m_Btn_pagecount.Update();
}
