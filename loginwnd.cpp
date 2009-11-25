/************************************************************************/
/*
 * Copyright (C) Meizu Technology Corporation Zhuhai China
 * All rights reserved.
 * 中国珠海, 魅族科技有限公司, 版权所有.
 *
 * This file is a part of the Meizu Foundation Classes library.
 * Author:    Michael
 * Create on: 2008-12-8
 */
/************************************************************************/

//请按照以步骤运行此实例代码：
//首先, 打开VS2005/2008创建一个Win 32智能设备项目
//在项目向导中选择M8SDK, 并勾选空项目
//然后,在项目中新建一个cpp文件,将此处代码拷贝到cpp文件中
//最后,按照M8SDK的帮助文档,配置项目属性
//现在,可以运行此程序了

#include "loginwnd.h"
#include "mainwnd.h"
#include "settingwnd.h"
#include "resource.h"
#include "confini.h"
#include "aboutwnd.h"


BOOL LoginWnd::OnInitDialog()
{
    // 必须先调用基类的初始化
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }

    m_count = MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2;

    m_ScrollWin.SetPos(0,0,GetWidth(),GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR);
    m_ScrollWin.SetID(MZ_IDC_LOGINWND_SCROLLWIN);
    m_ScrollWin.EnableScrollBarV(true);
    AddUiWin(&m_ScrollWin);

    m_Title.SetPos(0,0,GetWidth(),100);
    m_Title.SetID(MZ_IDC_CAPTION1);
    m_Title.SetText(L"推倒世界");
    m_ScrollWin.AddChild(&m_Title);

    m_Logo.SetID(MZ_IDC_PIC);
    m_Logo.SetPos(GetWidth()/2-100,20,48,48);
    m_Logo.SetPaintMode(MZ_PAINTMODE_NORMAL);
    m_Logo.LoadImage(MzGetInstanceHandle(),RT_RCDATA,MAKEINTRESOURCE(IDR_PNG_LOGO));
    m_ScrollWin.AddChild(&m_Logo);
 	/* 初始化单行编辑控件，并添加到窗口中*/
    //m_Account.SetPos(MZM_MARGIN_MAX,MZM_MARGIN_MAX,GetWidth()-MZM_MARGIN_MAX*2,70);
    m_Account.SetPos(MZM_MARGIN_MAX,120,     GetWidth()-MZM_MARGIN_MAX*2,60);
    m_Account.SetID(MZ_IDC_TESTBTN1); //you must set an unique ID for a edit control
    m_Account.SetLeftInvalid(80);
    m_Account.SetTip2(L"账户:");	// set the tips text
    m_Account.SetTextColor(RGB(0,200,0)); // you could also set the color of text
    m_Account.SetSipMode(IM_SIP_MODE_GEL_LETTER);
    m_ScrollWin.AddChild(&m_Account);
    //m_Pass.SetPos(MZM_MARGIN_MAX,MZM_MARGIN_MAX-280,GetWidth()-MZM_MARGIN_MAX*2,140);
    m_Pass.SetPos(MZM_MARGIN_MAX,190,GetWidth()-MZM_MARGIN_MAX*2,60);
    m_Pass.SetID(MZ_IDC_TESTBTN2);
    m_Pass.SetLeftInvalid(80);
    m_Pass.SetTip2(L"密码:");
    m_Pass.SetTextColor(RGB(0,200,0));
    m_Pass.SetSipMode(IM_SIP_MODE_GEL_LETTER);
    //m_Pass.SetEditStyle(SINGLELINE_EDIT_STYLE_PASSWORD);
    m_Pass.EnablePassWord();
    //m_Pass.SetText(SINGLELINE_EDIT_STYLE_PASSWORD);
    m_ScrollWin.AddChild(&m_Pass);

    int y = MZM_HEIGHT_BUTTON*3;
    m_BtnArrow.SetID(MZ_IDC_BTNARROW);
    m_BtnArrow.SetPos(GetWidth()-70,y,70,MZM_HEIGHT_BUTTON);
    m_BtnArrow.SetButtonType(MZC_BUTTON_ARROW_RIGHT);
    m_ScrollWin.AddChild(&m_BtnArrow);

    
    m_Setingtext.SetText(L"配置");
    m_Setingtext.SetID(MZ_IDC_LOGINWND_SETTING_TEXT);
	m_Setingtext.SetTextColor(RGB(200,200,200));
    //m_Setingtext.SetPos(MZM_MARGIN_MAX-300,420,70,MZM_HEIGHT_BUTTON);
    m_Setingtext.SetPos(GetWidth()-180,y,100,MZM_HEIGHT_BUTTON);
    m_Setingtext.SetDrawTextFormat(DT_RIGHT|DT_VCENTER);
    m_ScrollWin.AddChild(&m_Setingtext);

    y+=MZM_HEIGHT_BUTTON;

    m_BtnAbout.SetID(MZ_IDC_LOGINWND_ABOUTBTN);
    m_BtnAbout.SetPos(GetWidth()-70,y,70,MZM_HEIGHT_BUTTON);
    m_BtnAbout.SetButtonType(MZC_BUTTON_ARROW_RIGHT);
    //m_BtnAbout.SetText(L"About");
    m_ScrollWin.AddChild(&m_BtnAbout);

    m_AboutText.SetText(L"关于");
    m_AboutText.SetID(MZ_IDC_LOGINWND_ABOUT_TEXT);
    m_AboutText.SetTextColor(RGB(200,200,200));
    m_AboutText.SetPos(GetWidth()-180,y,100,MZM_HEIGHT_BUTTON);
    m_AboutText.SetDrawTextFormat(DT_RIGHT | DT_VCENTER);
    m_ScrollWin.AddChild(&m_AboutText);

    m_copywrite.SetID(MZ_IDC_LOGINWND_COPYWRITE);
    m_copywrite.SetPos(100,560,370,40);
    m_copywrite.SetText(COPYWRITE);
    m_copywrite.SetDrawTextFormat(DT_RIGHT|DT_VCENTER);
    m_ScrollWin.AddChild(&m_copywrite);

	// 初始化文字工具条，并添加到窗口中
    m_Toolbar.SetPos(0,GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR,GetWidth(),MZM_HEIGHT_TEXT_TOOLBAR);
    m_Toolbar.SetButton(0, true, true, L"退出");
    m_Toolbar.SetButton(1, true, true, L"快推");
    m_Toolbar.SetButton(2, true, true, L"登录");
    m_Toolbar.SetID(MZ_IDC_TOOLBAR1);
    AddUiWin(&m_Toolbar);
    
	 SetShellHomekeyReturnValue(SHK_RET_APPNOEXIT_SHELLTOP);
	 ConfIni::init();
	 m_Account.SetText(ConfIni::getAccount().c_str());
	 m_Pass.SetText(ConfIni::getPassword().c_str());
    return TRUE;
  }

  // 重载命令消息的处理函数
   void LoginWnd::OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
    case MZ_IDC_TESTBTN1:
      {
        CMzString str(64+m_Account.GetTextLen());
        // 格式化字符串
        wsprintf(str.C_Str(), L"You'd input:\n%s", m_Account.GetText().C_Str());
        // 弹出消息框
        //MzMessageBoxEx(m_hWnd, str.C_Str(), L"", MB_OK, false);
	MzMessageBoxEx(m_hWnd, str.C_Str(), L"", MB_OK, SHK_RET_APPNOEXIT_SHELLTOP);
      }
      break;
    case MZ_IDC_TESTBTN2:
      {
        CMzString str(64+m_Pass.GetTextLen());
        wsprintf(str.C_Str(), L"You'd input:\n%s", m_Pass.GetText().C_Str());
        // 弹出消息框
        //MzMessageBoxEx(m_hWnd, str.C_Str(), L"", MB_OK, false);
	MzMessageBoxEx(m_hWnd, str.C_Str(), L"", MB_OK, SHK_RET_APPNOEXIT_SHELLTOP);

      }
      break;
    case MZ_IDC_BTNARROW:
      {
	      //配置界面
	        SettingWnd m_settingwnd;
		RECT rcWork = MzGetWorkArea();
		m_settingwnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd,0,WS_POPUP);
		m_settingwnd.SetAnimateType_Show(m_count);
		m_settingwnd.SetAnimateType_Hide(m_count+1);
		m_settingwnd.DoModal();

      }
      break;
    case MZ_IDC_LOGINWND_ABOUTBTN:
      {
	      AboutWnd m_aboutwnd;
		RECT rcWork = MzGetWorkArea();
		m_aboutwnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd,0,WS_POPUP);
		m_aboutwnd.SetAnimateType_Show(m_count);
		m_aboutwnd.SetAnimateType_Hide(m_count+1);
		m_aboutwnd.DoModal();

      }
      break;
    case MZ_IDC_TOOLBAR1:
      {
        int nIndex = lParam;
        if (nIndex==0)
        {
          PostQuitMessage(0);
          return;
        }
        if (nIndex==1)
        {

	MainWnd m_wnd;
	m_wnd.fakeLogin(m_Account.GetText(),m_Pass.GetText());
	SayWnd *m_Saywnd=new SayWnd(m_wnd);
	RECT rcWork = MzGetWorkArea();
	m_Saywnd->Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd,0,WS_POPUP);
	m_Saywnd->SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_TOP_TO_BOTTOM_2);
	m_Saywnd->SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2);
	m_Saywnd->DoModal();


          return;
        }
        if (nIndex==2)
        {
		    /** 关闭键盘*/
		    if(MzIsSipOpen())
			    MzCloseSip();

		this->Invalidate();
		this->UpdateWindow();

		if(m_Account.GetText().IsEmpty()||m_Pass.GetText().IsEmpty()){
			MzMessageBoxEx(m_hWnd, L"                警告\n用户名或密码不能为空", L"", MB_OK, SHK_RET_APPNOEXIT_SHELLTOP);
			return;
		}


		MainWnd m_wnd;
		RECT rcWork = MzGetWorkArea();
		m_wnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd,0,WS_POPUP);
		m_wnd.SetAnimateType_Show(m_count);
		m_wnd.SetAnimateType_Hide(m_count+1);

		
		MzBeginWaitDlg(m_hWnd);
		bool success = m_wnd.Login(m_Account.GetText(),m_Pass.GetText());
		MzEndWaitDlg();
		//delete me
		//m_wnd.AddMsg(L"lerosua",L"initial twitter",L"time Nov 2009 19:90");
		//m_wnd.AddMsg(L"lerosua",L"1234567890qwertyuioplkjahdgfgzvxbbcvmfjeuyw",L"1分钟之前");
		if(success)
			m_wnd.DoModal();
		else{

			MzMessageBoxEx(m_hWnd, L"               警告\n用户名或密码错误", L"", MB_OK, SHK_RET_APPNOEXIT_SHELLTOP);
		}
		
		  return;
        }
      }
      break;
    }
  }



