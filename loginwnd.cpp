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


BOOL LoginWnd::OnInitDialog()
{
    // 必须先调用基类的初始化
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }

    m_count = MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2;

    m_ScrollWin.SetPos(0,0,GetWidth(),GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR);
    m_ScrollWin.SetID(MZ_IDC_SCROLLWIN);
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
    m_Account.SetPos(MZM_MARGIN_MAX*2,120,     GetWidth()-MZM_MARGIN_MAX*4,60);
    m_Account.SetID(MZ_IDC_TESTBTN1); //you must set an unique ID for a edit control
    m_Account.SetTip(L"Account:");	// set the tips text
    m_Account.SetTextColor(RGB(0,200,0)); // you could also set the color of text
    m_ScrollWin.AddChild(&m_Account);
    //m_Pass.SetPos(MZM_MARGIN_MAX,MZM_MARGIN_MAX-280,GetWidth()-MZM_MARGIN_MAX*2,140);
    m_Pass.SetPos(MZM_MARGIN_MAX*2,190,GetWidth()-MZM_MARGIN_MAX*4,60);
    m_Pass.SetID(MZ_IDC_TESTBTN2);
    m_Pass.SetTip(L"Password:");
    m_Pass.SetTextColor(RGB(0,200,0));
    m_Pass.SetEditStyle(SINGLELINE_EDIT_STYLE_PASSWORD);
    m_Pass.EnablePassWord();
    //m_Pass.SetText(SINGLELINE_EDIT_STYLE_PASSWORD);
    m_ScrollWin.AddChild(&m_Pass);

    m_BtnArrow.SetID(MZ_IDC_BTNARROW);
    m_BtnArrow.SetPos(GetWidth()-70,MZM_HEIGHT_BUTTON*3,70,MZM_HEIGHT_BUTTON);
    m_BtnArrow.SetButtonType(MZC_BUTTON_ARROW_RIGHT);
    m_ScrollWin.AddChild(&m_BtnArrow);
    
    //m_text.SetText(L"Configure");
    m_text.SetText(L"配置");
    m_text.SetID(MZ_IDC_STATIC_START1);
	m_text.SetTextColor(RGB(200,200,200));
    //m_text.SetPos(MZM_MARGIN_MAX-300,420,70,MZM_HEIGHT_BUTTON);
    m_text.SetPos(GetWidth()-180,MZM_HEIGHT_BUTTON*3,100,MZM_HEIGHT_BUTTON);
    m_text.SetDrawTextFormat(DT_RIGHT|DT_VCENTER);
    m_ScrollWin.AddChild(&m_text);

	// 初始化文字工具条，并添加到窗口中
    m_Toolbar.SetPos(0,GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR,GetWidth(),MZM_HEIGHT_TEXT_TOOLBAR);
    m_Toolbar.SetButton(0, true, true, L"Exit");
    //m_Toolbar.SetButton(1, true, true, L"Menu");
    m_Toolbar.SetButton(2, true, true, L"Login");
    m_Toolbar.SetID(MZ_IDC_TOOLBAR1);
    AddUiWin(&m_Toolbar);
    
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
        MzMessageBoxEx(m_hWnd, str.C_Str(), L"", MB_OK, false);
      }
      break;
    case MZ_IDC_TESTBTN2:
      {
        CMzString str(64+m_Pass.GetTextLen());
        wsprintf(str.C_Str(), L"You'd input:\n%s", m_Pass.GetText().C_Str());
        // 弹出消息框
        MzMessageBoxEx(m_hWnd, str.C_Str(), L"", MB_OK, false);

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
        CMzString str(128);
        wsprintf(str.C_Str(), L"twitter loging test");
        MzMessageBoxEx(m_hWnd, str.C_Str(), L"", MB_OK, false);

          return;
        }
        if (nIndex==2)
        {
		if(m_Account.GetText().IsEmpty()||m_Pass.GetText().IsEmpty()){
			MzMessageBoxEx(m_hWnd, L"警告\n用户名或密码不能为空", L"", MB_OK, false);
			return;
		}

		wchar_t str_name[128];
		wchar_t str_pass[128];
		wsprintf(str_name,m_Account.GetText().C_Str());
		wsprintf(str_pass,m_Pass.GetText().C_Str());

		MainWnd m_wnd;
		RECT rcWork = MzGetWorkArea();
		m_wnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd,0,WS_POPUP);
		m_wnd.SetAnimateType_Show(m_count);
		m_wnd.SetAnimateType_Hide(m_count+1);

		
		m_wnd.Login(str_name,str_pass);
		//delete me
		m_wnd.AddMsg(L"lerosua",L"initial twitter");
		m_wnd.DoModal();
		/*
		m_count++;
		if (m_count>15)
		{
		  m_count = 0;
		}
		*/
		          return;
        }
      }
      break;
    }
  }


void LoginWnd::SetDefault(const std::wstring& name,const std::wstring& pass)
{
	m_Account.SetText(name.c_str());
   m_Pass.SetText(pass.c_str());

}
