/*
 * =====================================================================================
 *
 *       Filename:  saywnd.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009��11��01�� 21ʱ29��50�� CST
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
#include "Mzfc\ConvertHelper.h"
#include <acc_api.h>



SayWnd::SayWnd(MainWnd& wnd):m_pwnd(wnd)
			     ,m_max_char(140)
{
}

SayWnd::~SayWnd()
{

	MzAccClose();
}
BOOL SayWnd::OnInitDialog()
{
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }

    int y=0;
    m_Toolbar_Top.SetID(MZ_IDC_POST_TOOLBAR_TOP);
    m_Toolbar_Top.SetPos(0,y,GetWidth(),MZM_HEIGHT_TEXT_TOOLBAR);
    m_Toolbar_Top.SetButton(0,true,true,L"���");
    m_Toolbar_Top.SetButton(1,true,true,Int2String(m_max_char));
    m_Toolbar_Top.SetButton(2,true,true,L"����");
    AddUiWin(&m_Toolbar_Top);

    y+=MZM_HEIGHT_TEXT_TOOLBAR;
    m_ScrollWin.SetID(MZ_IDC_POST_SCROLLWIN);
    m_ScrollWin.SetPos(0,y,GetWidth(),GetHeight()-y-MZM_HEIGHT_TEXT_TOOLBAR);
    AddUiWin(&m_ScrollWin);
    

    y=0;

    m_pEdit.SetPos(0,y,470,MZ_IDC_EDIT_HEIGHT);
    m_pEdit.SetID(MZ_IDC_POST_EDIT);
    m_pEdit.EnableZoomIn(true);
    m_pEdit.SetReadOnly(false);
    m_pEdit.SetRightInvalid(20);
    m_pEdit.EnableInsideScroll(true);
    
    m_pEdit.SetLineSpace(4);
    m_pEdit.SetFontColor(RGB(155,155,2));
    m_pEdit.SetEditBgType(UI_EDIT_BGTYPE_FILL_WHITE);
    m_pEdit.EnableUndo(true);
    m_pEdit.SetMaxChar(140);
    m_pEdit.SetSipMode(IM_SIP_MODE_GEL_PY);
    m_pEdit.SetFocus(true);
    m_ScrollWin.AddChild(&m_pEdit);

    y+=MZ_IDC_EDIT_HEIGHT;


    m_Toolbar.SetID(MZ_IDC_POST_TOOLBAR);
    m_Toolbar.SetPos(0,GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR,GetWidth(),MZM_HEIGHT_TEXT_TOOLBAR);
    m_Toolbar.SetButton(0,true,true,L"�˳�");
    m_Toolbar.SetButton(2,true,true,L"����");
    AddUiWin(&m_Toolbar);

    MzAccOpen();
    //SetTimer(m_hWnd,1,50,NULL);

    m_accMsg = MzAccGetMessage();
    
    return TRUE;

}

void SayWnd::OnMzCommand(WPARAM wParam,LPARAM lParam)
{

    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
	    case MZ_IDC_POST_TOOLBAR:
	    {
		    int nIndex=lParam;
		    if(nIndex==0){
			    /*�˳����ʹ���*/
			    MzAccClose();
			//SetWindowPos(m_hWnd, 0, TASK_BAR_HEIGHT, 480, 720-TASK_BAR_HEIGHT);
			    EndModal(ID_CANCEL);
			    return;
		    }
		    if(2==nIndex){
			    /*���ʹ���*/

			    if(m_pEdit.GetText().IsEmpty())
				    return;
			int nOK = MzMessageBoxEx(m_hWnd, L"ȷ�Ϸ�����", L"", MB_YESNO, SHK_RET_APPNOEXIT_SHELLTOP);
			if(2==nOK)
				return;

			    /** �رռ���*/
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

					MzAutoMsgBoxEx(m_hWnd, L"���ͳɹ�");
					m_pwnd.AddPostMsg(str.C_Str());
					this->EndModal(ID_OK);
				}
				else
					MzAutoMsgBoxEx(m_hWnd, L"����ʧ��");
					

		    }
	    }
	    break;

	    case MZ_IDC_POST_TOOLBAR_TOP:
	    {
		    int nIndex=lParam;
		    if(0 ==nIndex){
			    m_pEdit.Clear();
			    m_pEdit.Invalidate();
			    m_pEdit.Update();
		    }
		    if(2==nIndex){
			MzAutoMsgBoxEx(m_hWnd, L"δʵ��");
		    }

	    }
	    
	    break;

	}
}


LRESULT SayWnd::MzDefWndProc(UINT  message,WPARAM wParam, LPARAM lParam)
{
	switch(message){
		case MZ_WM_UIMULTILINEEDIT_TEXT_CHANGE:
			m_Toolbar_Top.SetButton(1,true,true,Int2String(m_max_char - m_pEdit.GetCharCount()));
			m_Toolbar_Top.Invalidate();
			m_Toolbar_Top.Update();

			break;
		default:
		if(message == m_accMsg){
			switch(wParam){
				case SCREEN_PORTRAIT_P:
					ScreenRotate(SCREEN_PORTRAIT_P);
					break;
				case SCREEN_PORTRAIT_N:
					ScreenRotate(SCREEN_PORTRAIT_N);
					break;
				case SCREEN_LANDSCAPE_P:
					ScreenRotate(SCREEN_LANDSCAPE_N);
					break;
				case SCREEN_LANDSCAPE_N:
					ScreenRotate(SCREEN_LANDSCAPE_P);
					break;
			}
		}
	}

	return CMzWndEx::MzDefWndProc(message, wParam, lParam);

}

void SayWnd::SetText(const wstring& str_)
{
	m_pEdit.SetText(str_.c_str());

}
/*
void SayWnd::onTimer(UINT_PTR nIDEvent)
{
switch(nIDEvent){
	case 1:
	{
		signed char x;
		signed char y;
		signed char z;
		MzAccGetXYZ(&x,&y,&z);


	}

}
*/

void SayWnd::ScreenRotate(int RotateMode)
{
	//��ת��Ļ
    DEVMODE DevMode;

    memset(&DevMode, 0, sizeof(DEVMODE));

    DevMode.dmSize = sizeof(DEVMODE);

    DevMode.dmFields = DM_DISPLAYQUERYORIENTATION;

    if (DISP_CHANGE_SUCCESSFUL == ChangeDisplaySettingsEx(NULL, &DevMode, NULL, CDS_TEST, NULL)) 
    {
      DevMode.dmFields = DM_DISPLAYORIENTATION;
      DWORD dDegree = DMDO_90;
      switch(RotateMode)
      {
        case 0:
        dDegree = DMDO_90;
        break;
        case 1:  
        dDegree = DMDO_270;
        break;
        case 2:
        dDegree = DMDO_0;
        break;
        case 3:
        dDegree = DMDO_180;
        break;
      }
      int y=38;
	    if(MzIsSipOpen()){
		    MzCloseSip();
	    }

      //��תΪ����ʱ���Ĵ��ڡ����б༭����ToolbarText��λ�ô�С
      if (dDegree == DMDO_90 || dDegree == DMDO_270)
      {
        SetWindowPos(m_hWnd, 0, TASK_BAR_HEIGHT, 480, 720-TASK_BAR_HEIGHT);

        m_Toolbar.SetTextBarType(ICON_TOOLBAR_TYPE_480);
        m_Toolbar_Top.SetTextBarType(ICON_TOOLBAR_TYPE_480);

        m_Toolbar.SetPos(0, GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR, GetWidth(), MZM_HEIGHT_TEXT_TOOLBAR);  
        m_Toolbar_Top.SetPos(0, y, GetWidth(), MZM_HEIGHT_TEXT_TOOLBAR);  

	m_ScrollWin.SetPos(0,MZM_HEIGHT_TEXT_TOOLBAR+y,GetWidth(),GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR*2-y);
	m_pEdit.SetPos(0,0,470,MZ_IDC_EDIT_HEIGHT);
	this->UpdateWindow();
      }

      //��תΪ����ʱ���Ĵ��ڡ����б༭����ToolbarText��λ�ô�С
      if (dDegree == DMDO_180 || dDegree == DMDO_0)
      {
        SetWindowPos(m_hWnd, 0, TASK_BAR_HEIGHT, 720, 480-TASK_BAR_HEIGHT);

        m_Toolbar.SetTextBarType(TEXT_TOOLBAR_TYPE_720);
        m_Toolbar_Top.SetTextBarType(TEXT_TOOLBAR_TYPE_720);

        m_Toolbar.SetPos(0, GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR_w720, GetWidth(), MZM_HEIGHT_TEXT_TOOLBAR_w720);
        m_Toolbar_Top.SetPos(0, y, GetWidth(), MZM_HEIGHT_TEXT_TOOLBAR_w720);

	m_ScrollWin.SetPos(0,MZM_HEIGHT_TEXT_TOOLBAR+y,GetWidth(),GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR*2-y);
        //m_pEdit.SetPos(MZM_MARGIN_MAX,MZM_MARGIN_MAX*2,GetWidth()-MZM_MARGIN_MAX*2,70);
	m_pEdit.SetPos(0,0,700,MZ_IDC_EDIT_HEIGHT);
	this->UpdateWindow();
      }
      DevMode.dmDisplayOrientation = dDegree;

      if(DISP_CHANGE_SUCCESSFUL == ChangeDisplaySettingsEx(NULL, &DevMode, NULL, 0, NULL))
      {

      }
      else
      {

      }
    }

}
