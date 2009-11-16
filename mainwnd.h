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

#define MZ_IDC_CAPTION_TOP 130
#define MZ_IDC_TOOLBAR2 131
#define MZ_IDC_SCROLLWIN2 132
#define MZ_IDC_LIST      133
#define MZ_IDC_TIMER     134
#define MZ_IDC_UPDATE    135
#define MZ_IDC_WRITE     136
//class GMitter;
class MsgListItemData
{
public:
	CMzString StringAuthor;
	CMzString StringText;
	CMzString StringTime;
};

class GMList: public UiList
{
	public:
		virtual void OnRemoveItem(int nIndex);
		void MultiSelectItem(int nIndex,bool bSelect);
		virtual void DrawItem(HDC hdcDst,int nIndex,RECT* prcItem,RECT* prcWin,RECT* prcUpdate);
		//virtual int CalcItemHeight(int index);
};

//main window , it is list
class MainWnd:public CMzWndEx
{
	MZ_DECLARE_DYNAMIC(MainWnd);
	public:
	MainWnd();
	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
	LRESULT MzDefWndProc(UINT message,WPARAM wParam,LPARAM lParam);
	//void AddMsg(wchar_t* author,wchar_t* msg,int num=0);
	void AddMsg(wchar_t* author,wchar_t* msg,wchar_t* time_,int num=0);
	void Login(const CMzString& account,const CMzString& password);
	void SendStatus(const wchar_t* msg);
	BOOL AutoDialNet();
	void CloseDialNet();
	bool GetNetStatus();
	//void LoadCache();
	//void LoadCache(const std::string& filename="\\Disk\\Program Files\\gmitter\\test.json");
	void LoadCache(const std::string& filename);
	void SaveCache(const std::string& filename);
	void Parser(const std::string& input,int big);
	void UpdateStatus();
	void StartTimer();
	virtual void OnTimer(UINT_PTR nIDEvent);
	protected:
	UiScrollWin m_ScrollWin;
	//UiToolbar_Text m_Toolbar;
	UiToolbar_Icon m_Toolbar;
	UiCaption      m_Top;
	GMList		m_List;
	GMitter		m_twitter;
	BOOL		m_isDialConnect;

	UiButton_Image m_btn_update;
	UiButton_Image m_btn_write;
	ImagingHelper  m_imgUpdate;
	ImagingHelper  m_imgWrite;

private:
	std::string m_id;
	//wstring m_account;
	//wstring m_pass;



};
#endif   /* ----- #ifndef MAINWND_FILE_HEADER_INC  ----- */

