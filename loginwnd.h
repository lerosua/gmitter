/*
 * =====================================================================================
 * 
 *       Filename:  gmitter.h
 * 
 *    Description:  twitter for m8
 * 
 *        Version:  1.0
 *        Created:  2009年11月01日 17时14分14秒 CST
 *       Revision:  none
 *       Compiler:  vc2005
 * 
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  Cyclone
 * 
 * =====================================================================================
 */

#ifndef  GMITTER_FILE_HEADER_INC
#define  GMITTER_FILE_HEADER_INC

//包含MZFC库的头文件
#include <mzfc_inc.h>

#define MZ_IDC_TESTBTN1  101
#define MZ_IDC_TESTBTN2  106
#define MZ_IDC_TOOLBAR1  102

#define IDC_PPM_OK    103
#define IDC_PPM_CANCEL  104

#define MZ_IDC_EDIT  105
#define MZ_IDC_SCROLLWIN 107
#define MZ_IDC_BTNARROW 110
#define MZ_IDC_STATIC_START1 111
#define MZ_IDC_CAPTION1 112
#define MZ_IDC_PIC	113
#define MZM_HEIGHT_BUTTON 80

class LoginWnd: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(LoginWnd);
public:
  
  /* 文字按钮工具条*/
  UiToolbar_Text m_Toolbar;
  UiScrollWin m_ScrollWin;

  /* 单行编辑器*/
  UiSingleLineEdit m_Account;
  UiSingleLineEdit m_Pass;
  UiButton	   m_BtnArrow;
  UiStatic	   m_text;
  UiCaption	   m_Title;
  UiPicture	   m_Logo;
  int m_count;

protected:
  /* 窗口的初始化*/
  virtual BOOL OnInitDialog();

  /* 重载命令消息的处理函数*/
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
  
};




#endif   /* ----- #ifndef GMITTER_FILE_HEADER_INC  ----- */

