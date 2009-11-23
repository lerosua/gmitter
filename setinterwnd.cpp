/*
 * =====================================================================================
 *
 *       Filename:  setinterwnd.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月23日 13时11分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#include "setinterwnd.h"


BOOL SetInterWnd::OnInitDialog()
{
	if (!CMzWndEx::OnInitDialog())
	{
		return FALSE;
	}

	m_ScrollWin.SetID(MZ_IDC_SCROLLWIN);
	m_ScrollWin.SetPos(0, 0, GetWidth(), GetHeight() - MZM_HEIGHT_TEXT_TOOLBAR);
	    m_ScrollWin.EnableScrollBarV(true);
	    AddUiWin(&m_ScrollWin);

	    m_btnCount[0].SetID(MZ_IDC_SETINTERWND_BTN_10);
	    m_btnCount[1].SetID(MZ_IDC_SETINTERWND_BTN_15);
	    m_btnCount[2].SetID(MZ_IDC_SETINTERWND_BTN_20);
	    m_btnCount[3].SetID(MZ_IDC_SETINTERWND_BTN_25);
	    m_btnCount[4].SetID(MZ_IDC_SETINTERWND_BTN_30);

	ImagingHelper *imgSelected = ImagingHelper::GetImageObject(GetMzResModuleHandle(), MZRES_IDR_PNG_SELECTED, true);
	    for(int i=0;i < _MAX; i++){
		    m_btnCount[i].SetPos(0,MZM_HEIGHT_BUTTONEX*i,GetWidth(),MZM_HEIGHT_BUTTONEX);
		temp << i * 5 + 10 << L"tiao";
		m_btnCount[i].SetText(temp.str().c_str());
		m_btnCount[i].SetButtonType(MZC_BUTTON_LINE_BOTTOM);
		m_btnCount[i].EnableNotifyMessage(true);
		m_ScrollWin.AddChild(&m_btnCount[i]);

		m_btnCount[i].SetImage2(imgSelected);
		m_btnCount[i].SetImageWidth2(imgSelected->GetImageWidth());
		m_btnCount[i].SetShowImage2(false);
	    }

	m_toolbar.SetID(MZ_IDC_SETINTERWND_TOOLBAR);
	m_toolbar.SetPos(0, GetHeight() - MZM_HEIGHT_TEXT_TOOLBAR, GetWidth(), MZM_HEIGHT_TEXT_TOOLBAR);
	m_toolbar.SetButton(0, true, true, L"Back");
	m_toolbar.EnableLeftArrow(true);
	m_toolbar.EnableNotifyMessage(true);
	AddUiWin(&m_toolbar);

	return TRUE;
}
void SetInterWnd::OnMzCommand(WPARAM wParam, LPARAM lParam)
{
	UINT_PTR id = LOWORD(wParam);
	int index = lParam;

	switch (id)
	{
	case MZ_IDC_SETINTERWND_BTN_10:
		_count = 10;
		select();
		break;

	case MZ_IDC_SETINTERWND_BTN_15:
		_count = 15;
		select();
		break;

	case MZ_IDC_SETINTERWND_BTN_20:
		_count = 20;
		select();
		break;

	case MZ_IDC_SETINTERWND_BTN_25:
		_count = 25;
		select();
		break;

	case MZ_IDC_SETINTERWND_BTN_30:
		_count = 30;
		select();
		break;

	case MZ_IDC_SETINTERWND_TOOLBAR:
		if (0 == index)			// 保存设置并返回
		{
			EndModal(_count);
		}
		break;
	}
}


void SetInterWnd::select(void)
{
	for (int i = 0; i < _MAX; i++)
	{
		if ((_count - 10) / 5 == i)
		{
			m_btnCount[i].SetShowImage2(true);
		}
		else
		{
			m_btnCount[i].SetShowImage2(false);
		}
	}

	Invalidate();
	UpdateWindow();
}

MZ_IMPLEMENT_DYNAMIC(SetInterWnd)
