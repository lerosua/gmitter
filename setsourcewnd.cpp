/*
 * =====================================================================================
 *
 *       Filename:  sourcewnd.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月24日 17时07分48秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#include "setsourcewnd.h"
#include "base64.h"

const char* SetSourceWnd::client[SOURCE_MAX]={"iTweet","EchoFon","Gravity","twidroid","twhirl","dabr","twittai","Seesmic","Brizzly","Tweetie"};
BOOL SetSourceWnd::OnInitDialog()
{

	if (!CMzWndEx::OnInitDialog())
	{
		return FALSE;
	}


	m_ScrollWin.SetID(MZ_IDC_SOURCEWND_SCROLLWIN);
	m_ScrollWin.SetPos(0, 0, GetWidth(), GetHeight() - MZM_HEIGHT_TEXT_TOOLBAR);
	m_ScrollWin.EnableScrollBarV(true);
	AddUiWin(&m_ScrollWin);

	ImagingHelper *imgSelected = ImagingHelper::GetImageObject(GetMzResModuleHandle(), MZRES_IDR_PNG_SELECTED, true);

	for(int i=0;i<SOURCE_MAX;i++){
		m_btnCount[i].SetID(MZ_IDC_SOURCEWND_CLINET0+i);
		m_btnCount[i].SetPos(0,MZM_HEIGHT_BUTTONEX*i,GetWidth(),MZM_HEIGHT_BUTTONEX);
		m_btnCount[i].SetButtonType(MZC_BUTTON_LINE_BOTTOM);
		m_btnCount[i].EnableNotifyMessage(true);
		m_ScrollWin.AddChild(&m_btnCount[i]);
		m_btnCount[i].SetImage2(imgSelected);
		m_btnCount[i].SetImageWidth2(imgSelected->GetImageWidth());
		m_btnCount[i].SetShowImage2(false);
		wstring temp=s2ws(string(client[i]));
		m_btnCount[i].SetText(temp.c_str());
	}

	m_toolbar.SetID(MZ_IDC_SOURCEWND_TOOLBAR);
	m_toolbar.SetPos(0, GetHeight() - MZM_HEIGHT_TEXT_TOOLBAR, GetWidth(), MZM_HEIGHT_TEXT_TOOLBAR);
	m_toolbar.SetButton(0, true, true, L"返回");
	m_toolbar.EnableLeftArrow(true);
	m_toolbar.EnableNotifyMessage(true);
	AddUiWin(&m_toolbar);


	return TRUE;
}

void SetSourceWnd::OnMzCommand(WPARAM wParam,LPARAM lParam)
{

	UINT_PTR id = LOWORD(wParam);
	int index = lParam;

	if(id>=MZ_IDC_SOURCEWND_CLINET0 && id<=MZ_IDC_SOURCEWND_CLINET9){
		_select = id-MZ_IDC_SOURCEWND_CLINET0;
		select();
	}
	if( MZ_IDC_SOURCEWND_TOOLBAR == id){
		if (0 == index)
			EndModal(_select);
	}
}

void SetSourceWnd::select()
{
	for(int i=0; i< SOURCE_MAX; i++){
		if( _select == i)
			m_btnCount[i].SetShowImage2(true);
		else
			m_btnCount[i].SetShowImage2(false);
	}
	Invalidate();
	UpdateWindow();

}

MZ_IMPLEMENT_DYNAMIC(SetSourceWnd)


