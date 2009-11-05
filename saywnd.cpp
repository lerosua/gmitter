/*
 * =====================================================================================
 *
 *       Filename:  saywnd.cpp
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

#include "saywnd.h"
#include "gmitter.h"
#include "mainwnd.h"

SayWnd::SayWnd(MainWnd& wnd):m_pwnd(wnd)
{
}

BOOL SayWnd::OnInitDialog()
{
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }

    m_Caption.SetID(MZ_IDC_CAPTION);
    m_Caption.SetPos(0,0,GetWidth(),100);
    m_Caption.SetText(L"GMitter");
    AddUiWin(&m_Caption);

    m_pEdit = new UiEdit;
    m_pEdit->SetPos(5,120,470,170);
    m_pEdit->SetID(MZ_IDC_EDIT);
    m_pEdit->EnableZoomIn(true);
    m_pEdit->SetReadOnly(false);
    m_pEdit->SetRightInvalid(10);
    //m_pEdit->EnableGridlines(true);
    //m_pEdit->EnableInsideScroll(true);
    
    m_pEdit->SetLineSpace(10);
    m_pEdit->SetFontColor(RGB(155,155,2));
    m_pEdit->SetEditBgType(UI_EDIT_BGTYPE_FILL_WHITE);
    m_pEdit->EnableUndo(true);
    m_pEdit->SetMaxChar(140);
    AddUiWin(m_pEdit);

    m_Toolbar.SetID(MZ_IDC_TOOLBAR3);
    m_Toolbar.SetPos(0,GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR,GetWidth(),MZM_HEIGHT_TEXT_TOOLBAR);
    m_Toolbar.SetButton(0,true,true,L"Exit");
    m_Toolbar.SetButton(2,true,true,L"Send");
    AddUiWin(&m_Toolbar);
    
    return TRUE;

}

void SayWnd::OnMzCommand(WPARAM wParam,LPARAM lParam)
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
			    wsprintf(str.C_Str(),L"you twitter :\n%s",m_pEdit->GetText().C_Str());
				char buf[512];
				sprintf(buf,"%s",str.C_Str());
			    //GMitter m_itter;
			//	m_itter.SetStatus(buf);
			//MzMessageBoxEx(m_hWnd, str.C_Str(), L"", MB_OK, false);
			m_pwnd.AddMsg(L"lerosua",str.C_Str());
			this->EndModal(ID_OK);

		    }
	    }
	    break;

	}
}


