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

    y+=50;
    m_Text.SetID(MZ_IDC_ABOUTWND_TEXT);
    m_Text.SetPos(GetWidth()/8, y,GetWidth()*7/8,400);
    m_Text.SetDrawTextFormat(DT_CENTER|DT_VCENTER| DT_WORDBREAK);
    m_Text.SetText(MZ_ABOUT_TEXT);
    AddUiWin(&m_Text);
    
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
