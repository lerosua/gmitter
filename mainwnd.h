/*
 * =====================================================================================
 * 
 *       Filename:  mainwnd.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  2009年11月01日 17时22分33秒 CST
 *       Revision:  none
 *       Compiler:  vc
 * 
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  Cyclone
 * 
 * =====================================================================================
 */

#ifndef  MAINWND_FILE_HEADER_INC
#define  MAINWND_FILE_HEADER_INC

#include <mzfc_inc.h>
#include "gmitter.h"

#define MZ_IDC_TOOLBAR2 102
#define MZ_IDC_SCROLLWIN 105
#define MZ_IDC_LIST      120
//class GMitter;
class MsgListItemData
{
public:
	CMzString StringAuthor;
	CMzString StringText;
};

class GMList: public UiList
{
	public:
		virtual void OnRemoveItem(int nIndex);
		void MultiSelectItem(int nIndex,bool bSelect);
		virtual void DrawItem(HDC hdcDst,int nIndex,RECT* prcItem,RECT* prcWin,RECT* prcUpdate);
};

//main window , it is list
class MainWnd:public CMzWndEx
{
	MZ_DECLARE_DYNAMIC(MainWnd);
	public:
	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
	LRESULT MzDefWndProc(UINT message,WPARAM wParam,LPARAM lParam);
	void AddMsg(wchar_t* author,wchar_t* msg);
	void Login(const wchar_t*  account,const wchar_t* password);
	void SendStatus(const wchar_t* msg);
	protected:
	UiScrollWin m_ScrollWin;
	UiToolbar_Text m_Toolbar;
	GMList		m_List;
	GMitter		m_twitter;

private:
	//wstring m_account;
	//wstring m_pass;



};
#endif   /* ----- #ifndef MAINWND_FILE_HEADER_INC  ----- */

