/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009��11��01�� 17ʱ19��54�� CST
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
#include "settings.h"

MZ_IMPLEMENT_DYNAMIC(LoginWnd)
MZ_IMPLEMENT_DYNAMIC(MainWnd)
MZ_IMPLEMENT_DYNAMIC(SayWnd)
MZ_IMPLEMENT_DYNAMIC(SettingWnd)


/* �� CMzApp ������Ӧ�ó�����*/
class GMitterApp: public CMzApp
{
public:
  /* Ӧ�ó����������*/
  LoginWnd m_LoginWnd;

  /* Ӧ�ó���ĳ�ʼ��*/
  virtual BOOL Init()
  {
	/* ��ʼ�� COM ���*/
    CoInitializeEx(0, COINIT_MULTITHREADED);

	/* ����������*/
    RECT rcWork = MzGetWorkArea();
    m_LoginWnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork), 0, 0, 0);
    if(MzGetParam(MZGP_APP_START_ANIMATION)==TRUE){
	    m_LoginWnd.AnimateWindow(MZ_ANIMTYPE_ZOOM_IN,true);
	    Setting conf;
	    conf.loadSettings();
		const std::string& name=conf.GetAccount();
		const std::string& pass=conf.GetPass();
		if(!name.empty()&&!pass.empty()){

				m_LoginWnd.SetDefault(s2ws(name),s2ws(pass));
		}
	    //m_LoginWnd.SetBgColor(RGB(0,0,0));
	    m_LoginWnd.Show();
    }

	/* �ɹ��򷵻�TRUE*/
    return TRUE;
  }
};

/* ȫ�ֵ�Ӧ�ó������*/
GMitterApp gmApp;

