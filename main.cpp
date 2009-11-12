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
#include "base64.h"
#include <ReadWriteIni.h>
//#include "settings.h"

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

		 m_LoginWnd.SetShellHomekeyReturnValue(SHK_RET_APPNOEXIT_SHELLTOP);
	    m_LoginWnd.Show();

    if(FileExists(rcFile)){
	    CMzString name;
	    CMzString pass;
	    TCHAR* s_name;
	    TCHAR* s_pass;
	    IniReadString(L"config",L"account",&s_name,rcFile);
	    //wprintf(name.C_Str(),L"%s",s_name);
	    name=s_name;
	    IniReadString(L"config",L"password",&s_pass,rcFile);
	    //wprintf(pass.C_Str(),L"%s",s_pass);
	    pass=s_pass;
		//free(s_name);
	    //free(s_pass);

		if(!name.IsEmpty()&&!pass.IsEmpty()){

				m_LoginWnd.SetDefault(name.C_Str(),pass.C_Str());
				
		}
;
	    }
	    //m_LoginWnd.SetBgColor(RGB(0,0,0));

		//m_LoginWnd.SetDefault(name.C_Str(),pass.C_Str());
    }

	/* �ɹ��򷵻�TRUE*/
    return TRUE;
  }
};

/* ȫ�ֵ�Ӧ�ó������*/
GMitterApp gmApp;

