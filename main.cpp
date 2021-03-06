/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月01日 17时19分54秒 CST
 *       Revision:  none
 *       Compiler:  vc2005
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  Cyclone
 *
 * =====================================================================================
 */

#include "loginwnd.h"
#include "mainwnd.h"
#include "saywnd.h"
#include "settingwnd.h"
#include "aboutwnd.h"
#include "base64.h"

MZ_IMPLEMENT_DYNAMIC(LoginWnd)
MZ_IMPLEMENT_DYNAMIC(MainWnd)
MZ_IMPLEMENT_DYNAMIC(SayWnd)
MZ_IMPLEMENT_DYNAMIC(SettingWnd)
MZ_IMPLEMENT_DYNAMIC(AboutWnd)



/* 从 CMzApp 派生的应用程序类*/
class GMitterApp: public CMzApp
{
public:
  /* 应用程序的主窗口*/
  LoginWnd m_LoginWnd;

  /* 应用程序的初始化*/
  virtual BOOL Init()
  {
	/* 初始化 COM 组件*/
    CoInitializeEx(0, COINIT_MULTITHREADED);

	/* 创建主窗口*/
    RECT rcWork = MzGetWorkArea();
    m_LoginWnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork), 0, 0, 0);
    if(MzGetParam(MZGP_APP_START_ANIMATION)==TRUE){
	    m_LoginWnd.AnimateWindow(MZ_ANIMTYPE_ZOOM_IN,true);

	// m_LoginWnd.SetShellHomekeyReturnValue(SHK_RET_APPNOEXIT_SHELLTOP);
	    m_LoginWnd.Show();

	    //m_LoginWnd.SetBgColor(RGB(0,0,0));

    }

	/* 成功则返回TRUE*/
    return TRUE;
  }
};

/* 全局的应用程序对象*/
GMitterApp gmApp;

