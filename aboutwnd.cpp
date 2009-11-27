/*
 * =====================================================================================
 *
 *       Filename:  aboutwnd.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月20日 16时41分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#include "aboutwnd.h"
#include "resource.h"


AboutWnd::AboutWnd()
{

}

AboutWnd::~AboutWnd()
{

}

BOOL AboutWnd::OnInitDialog()
{

    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }

    int y=40;
    
    m_Logo.SetID(MZ_IDC_ABOUTWND_LOGO);
    m_Logo.SetPos(GetWidth()/2-100,y,48,48);
    m_Logo.SetPaintMode(MZ_PAINTMODE_NORMAL);
    m_Logo.LoadImage(MzGetInstanceHandle(),RT_RCDATA,MAKEINTRESOURCE(IDR_PNG_LOGO));
    AddUiWin(&m_Logo);

    y+=150;
    for(int i=0;i<ABOUT_NUM-1;i++){
    m_Text[i].SetID(MZ_IDC_ABOUTWND_TEXT+i);
    m_Text[i].SetPos(0, y,GetWidth(),50);
    m_Text[i].SetDrawTextFormat(DT_CENTER|DT_VCENTER| DT_WORDBREAK);
    //m_Text[i].SetText(MZ_ABOUT_TEXT);
    AddUiWin(&m_Text[i]);
    y+=50;
    }
    m_Text[0].SetText(L"GMitter copyright @lerosua");
    m_Text[1].SetText(L"您的捐助将帮助软件发展得更好");
    m_Text[2].SetText(L"支付宝:lerosua@gmail.com");
    m_Text[3].SetText(L"非常感谢！");
    m_Text[4].SetText(L"推倒");
	m_Text[4].SetID(MZ_IDC_ABOUTWND_TEXT+4);
	m_Text[4].SetPos(GetWidth()/2-50,40,100,50);
	m_Text[4].SetDrawTextFormat(DT_CENTER|DT_VCENTER| DT_WORDBREAK);
	AddUiWin(&m_Text[4]);
    
    m_Toolbar.SetID(MZ_IDC_ABOUTWND_TOOLBAR);
    m_Toolbar.SetPos(0,GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR,GetWidth(),MZM_HEIGHT_TEXT_TOOLBAR);
    m_Toolbar.SetButton(0,true,true,L"返回");
    AddUiWin(&m_Toolbar);

    return TRUE;
}

void AboutWnd::OnMzCommand(WPARAM wParam,LPARAM lParam)
{

    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
	    case MZ_IDC_ABOUTWND_TOOLBAR:
		    {
		    int nIndex=lParam;
		    if(nIndex==0){
			    EndModal(ID_CANCEL);
			    return;
		    }
		    }
		    break;
	    default:
		    break;
    }

}
