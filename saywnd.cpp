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
#include <iostream>
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

    int y=0;
    m_CaptionTop.SetID(MZ_IDC_CAPTION_TOP);
    m_CaptionTop.SetPos(0,0,GetWidth(),100);
    m_CaptionTop.SetText(L"GMitter");
    AddUiWin(&m_CaptionTop);

    y+=100;
    m_ScrollWin.SetID(MZ_IDC_POST_SCROLLWIN);
    m_ScrollWin.SetPos(0,y,GetWidth(),GetHeight()-y-MZM_HEIGHT_TEXT_TOOLBAR);
    AddUiWin(&m_ScrollWin);

    y=0;
    //m_pEdit = new UiEdit;
    m_pEdit.SetPos(0,y,470,170);
    m_pEdit.SetID(MZ_IDC_EDIT4);
    m_pEdit.EnableZoomIn(true);
    m_pEdit.SetReadOnly(false);
    m_pEdit.SetRightInvalid(20);
    m_pEdit.EnableGridlines(true);
    m_pEdit.EnableInsideScroll(true);
    
    m_pEdit.SetLineSpace(4);
    m_pEdit.SetFontColor(RGB(155,155,2));
    m_pEdit.SetEditBgType(UI_EDIT_BGTYPE_FILL_WHITE);
    m_pEdit.EnableUndo(true);
    m_pEdit.SetMaxChar(140);
    //AddUiWin(&m_pEdit);
    m_ScrollWin.AddChild(&m_pEdit);

    y+=170;

    m_CaptionBottom.SetID(MZ_IDC_CAPTION_BOTTOM);
    m_CaptionBottom.SetPos(0,y,GetWidth(),100);
    m_CaptionBottom.SetText(L"140");
    m_ScrollWin.AddChild(&m_CaptionBottom);



    m_Toolbar.SetID(MZ_IDC_STATUS_TOOLBAR);
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
	    case MZ_IDC_STATUS_TOOLBAR:
	    {
		    int nIndex=lParam;
		    if(nIndex==0){
			    /*退出发送窗口*/
			    EndModal(ID_CANCEL);
			    return;
		    }
		    if(2==nIndex){
			    /*发送处理*/

			    /** 关闭键盘*/
			    if(MzIsSipOpen()){
				    MzCloseSip();
			    }

			    CMzString str(256);
			    wsprintf(str.C_Str(),L"%s",m_pEdit.GetText().C_Str());

				this->Invalidate();
				this->UpdateWindow();

				MzBeginWaitDlg(m_hWnd);
				
				m_pwnd.SendStatus(str.C_Str());

				MzEndWaitDlg();
				if(m_pwnd.GetNetStatus()){

					MzMessageBoxEx(m_hWnd, str.C_Str(), L"", MB_OK, SHK_RET_APPNOEXIT_SHELLTOP);
					//m_pwnd.AddMsg(L"lerosua",str.C_Str());
					this->EndModal(ID_OK);
				}
				else
					MzMessageBoxEx(m_hWnd, L"发送失败", L"", MB_OK, SHK_RET_APPNOEXIT_SHELLTOP);

		    }
	    }
	    break;

	}
}


void SayWnd::OnChar(TCHAR chCharCOde, LPARM lKeyData)
{
	size_t num=140-m_pEdit.GetText().Length();

	CMxString count_(num);
	m_CaptionBottom.SetText(count_.C_Str());
	m_CaptionBottom.UpdateWindow();

}
