/*
 * =====================================================================================
 *
 *       Filename:  mainwnd.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月01日 17时28分17秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  Cyclone
 *
 * =====================================================================================
 */


#include "mainwnd.h"
#include "saywnd.h"
#include "Resource.h"
#include "base64.h"
#include <CallNotifyApi.h>
#include <ReadWriteIni.h>
#include <sstream>
#include <string>
#include <fstream>

MainWnd::MainWnd():m_id("")
{

}
void MainWnd::StartTimer()
{
	SetTimer(m_hWnd,MZ_IDC_TIMER,180*1000,NULL);

}
BOOL MainWnd::OnInitDialog()
{
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }

    m_Top.SetPos(0,0,GetWidth(),MZM_HEIGHT_ICON_TOOLBAR-10);
    m_Top.SetID(MZ_IDC_CAPTION_TOP);
    m_Top.SetText(L"推倒世界");
    AddUiWin(&m_Top);

    //m_imgUpdate.LoadImage(L"\\Disk\\Program Files\\gmitter\\res\\update.png");
    m_imgUpdate.LoadImageFromRes(MzGetInstanceHandle(),RT_RCDATA,MAKEINTRESOURCE(IDR_PNG_UPDATE),TRUE,TRUE);
    m_imgWrite.LoadImageFromRes( MzGetInstanceHandle(),RT_RCDATA,MAKEINTRESOURCE(IDR_PNG_WRITE) ,TRUE,TRUE);

    m_btn_update.SetID(MZ_IDC_UPDATE);
    m_btn_update.SetPos(2,2,50,50);
    m_btn_update.SetImage_Normal(&m_imgUpdate);
    m_btn_update.SetMode(UI_BUTTON_IMAGE_MODE_ALWAYS_SHOW_NORMAL);
    m_btn_update.SetTextColor(RGB(255,255,255));
	AddUiWin(&m_btn_update);

    m_btn_write.SetID(MZ_IDC_WRITE);
    m_btn_write.SetPos(GetWidth()-52,2,50,50);
    m_btn_write.SetImage_Normal(&m_imgWrite);
    m_btn_write.SetMode(UI_BUTTON_IMAGE_MODE_ALWAYS_SHOW_NORMAL);
    m_btn_write.SetTextColor(RGB(255,255,255));
	AddUiWin(&m_btn_write);

    //m_ScrollWin.SetPos(0,0,GetWidth(),GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR);
    m_ScrollWin.SetPos(0,MZM_HEIGHT_ICON_TOOLBAR-10,GetWidth(),GetHeight()-2*MZM_HEIGHT_TEXT_TOOLBAR);
    m_ScrollWin.SetID(MZ_IDC_SCROLLWIN2);
    m_ScrollWin.EnableScrollBarV(true);
    AddUiWin(&m_ScrollWin);

    m_List.SetPos(0,MZM_HEIGHT_ICON_TOOLBAR-15,GetWidth(),GetHeight()-2*MZM_HEIGHT_TEXT_TOOLBAR-5);
    //m_List.SetPos(0,5,GetWidth(),GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR-5);
    m_List.SetID(MZ_IDC_LIST);
    m_List.EnableScrollBarV(true);
    m_List.EnableNotifyMessage(true);
    m_List.SetItemHeight(90);
    m_List.SetTextColor(RGB(255,0,0));
    m_List.EnableVaryItemHeight(true);
    AddUiWin(&m_List);
    
    /*
    m_Toolbar.SetPos(0,GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR,GetWidth(),MZM_HEIGHT_TEXT_TOOLBAR);
    m_Toolbar.SetButton(0,true,true,L"Exit");
    m_Toolbar.EnableLeftArrow(true);
    m_Toolbar.SetButton(1,true,true,L"I Say");
    m_Toolbar.SetButton(2,true,true,L"Update");
    m_Toolbar.SetID(MZ_IDC_TOOLBAR2);
    AddUiWin(&m_Toolbar);
    */

    m_Toolbar.SetPos(0,GetHeight()-MZM_HEIGHT_ICON_TOOLBAR,GetWidth(),MZM_HEIGHT_ICON_TOOLBAR);
    m_Toolbar.SetID(MZ_IDC_TOOLBAR2);
    m_Toolbar.SetButtonCount(5);
    m_Toolbar.LoadButtonIcon(0, MzGetInstanceHandle(),RT_RCDATA, MAKEINTRESOURCE(IDR_PNG_FRI));
    m_Toolbar.LoadButtonIcon(1, MzGetInstanceHandle(),RT_RCDATA, MAKEINTRESOURCE(IDR_PNG_METION));
    m_Toolbar.LoadButtonIcon(2, MzGetInstanceHandle(),RT_RCDATA, MAKEINTRESOURCE(IDR_PNG_SEARCH));
    m_Toolbar.LoadButtonIcon(3, MzGetInstanceHandle(),RT_RCDATA, MAKEINTRESOURCE(IDR_PNG_FAV));
    m_Toolbar.LoadButtonIcon(4, MzGetInstanceHandle(),RT_RCDATA, MAKEINTRESOURCE(IDR_PNG_EXIT));
    AddUiWin(&m_Toolbar);
    return TRUE;
}

void MainWnd::AddMsg(wchar_t* author,wchar_t* msg,int num)
{
	ListItem li;
	CMzString strAuthor(256);
	CMzString strMsg(256);
	wsprintf(strAuthor.C_Str(),author);
	wsprintf(strMsg.C_Str(), msg);
	MsgListItemData* pmlid=new MsgListItemData;
	pmlid->StringAuthor = strAuthor;
	pmlid->StringText = strMsg;

	li.Data = pmlid;
	//m_List.AddItem(li);
	m_List.InsertItem(li,num);
}


LRESULT MainWnd::MzDefWndProc(UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message){
		case MZ_WM_MOUSE_NOTIFY:
		{
			int nID=LOWORD(wParam);
			int nNotify=HIWORD(wParam);
			int x=LOWORD(lParam);
			int y=HIWORD(lParam);

			if(nID== MZ_IDC_LIST && nNotify == MZ_MN_LBUTTONDOWN){
				if(!m_List.IsMouseDownAtScrolling()& !m_List.IsMouseMoved()){
					int nIndex=m_List.CalcIndexOfPos(x,y);
					m_List.SetSelectedIndex(nIndex);
					m_List.Invalidate();
					m_List.Update();
				}
				return 0;
			}

			//处理列表控件的鼠标移动通知 
			if(nID== MZ_IDC_LIST && nNotify == MZ_MN_MOUSEMOVE){
				if(m_List.GetSelectedIndex()!=-1){
					m_List.SetSelectedIndex(-1);
					m_List.Invalidate();
					m_List.Update();
				}
				return 0;
			}
		}
		return 0;
	}
	return CMzWndEx::MzDefWndProc(message,wParam,lParam);
}



void MainWnd::OnMzCommand(WPARAM wParam,LPARAM lParam)
{
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
	    case MZ_IDC_UPDATE:
		    {
			    /* 更新*/
			MzBeginWaitDlg(m_hWnd);
			   UpdateStatus();
			    if(GetNetStatus()){
				    LoadCache(updateFile);
				    SaveCache(updateFile);
			    }
			MzEndWaitDlg();

			    return;
		    }
			    break;
	    case MZ_IDC_WRITE:
			    {
			SayWnd *m_Saywnd=new SayWnd(*this);
			RECT rcWork = MzGetWorkArea();
			m_Saywnd->Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd,0,WS_POPUP);
			m_Saywnd->SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_TOP_TO_BOTTOM_2);
			m_Saywnd->SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2);
			m_Saywnd->DoModal();

			    }
			    break;
	    case MZ_IDC_TOOLBAR2:
	    {
		    int nIndex=lParam;
		    if(nIndex==4){
			    /* 退出程序*/
			   PostQuitMessage(0);
        
			    return;
		    }
		    if(1== nIndex){
			    /* 发推*/

		return;
		

		    }
		    if(2 == nIndex){

			
			    //EndModal(ID_OK);
			    return;
		    }

	    }
      break;
    }


}

void GMList::OnRemoveItem(int nIndex)
{
	ListItem* pItem = GetItem(nIndex);
	if(pItem){
		MsgListItemData* mlid= (MsgListItemData*)pItem->Data;
		if(mlid)
			delete mlid;
	}
}

void GMList::MultiSelectItem(int nIndex,bool bSelect)
{
	ListItem* pItem = GetItem(nIndex);
	if(pItem){
		MsgListItemData* mlid= (MsgListItemData*)pItem->Data;
		if(mlid)
			;//do something
	}
}

void GMList::DrawItem(HDC hdcDst,int nIndex,RECT* prcItem,RECT* prcWin,RECT* prcUpdate)
{
	ListItem* pItem = GetItem(nIndex);
	if(0==pItem)
		return;
	if(0== pItem->Data )
		return;
	MsgListItemData* pmlid = (MsgListItemData*)pItem->Data;


    // 绘制左边的小图像
    //ImagingHelper *pimg = ImagingHelper::GetImageObject(MzGetInstanceHandle(), IDR_PNG_LOGO, true);
    ImagingHelper *pimg = ImagingHelper::GetImageObject(MzGetInstanceHandle(), IDR_PNG_SMS, true);
    RECT rcImg = *prcItem;
    rcImg.right = rcImg.left + MZM_MARGIN_MAX*2;
    if (pimg)
    {
      pimg->Draw(hdcDst, &rcImg, false, false);
    }

	// for author
	RECT rcText=*prcItem;
	rcText.left=MZM_MARGIN_MAX*2;
	rcText.bottom=rcText.top+RECT_HEIGHT(rcText)/3;
	::SetTextColor(hdcDst,RGB(0,200,0));
	MzDrawText(hdcDst,pmlid->StringAuthor.C_Str(), &rcText,DT_LEFT|DT_BOTTOM|DT_SINGLELINE|DT_END_ELLIPSIS);

	// for message
	rcText.top=rcText.bottom;
	rcText.bottom=prcItem->bottom;
	::SetTextColor(hdcDst,RGB(200,200,200));
	HFONT hf=FontHelper::GetFont(24);
	SelectObject(hdcDst,hf);
	//MzDrawText(hdcDst,pmlid->StringText.C_Str(), &rcText,DT_LEFT|DT_TOP|DT_SINGLELINE|DT_END_ELLIPSIS);
	MzDrawText(hdcDst,pmlid->StringText.C_Str(), &rcText,DT_LEFT|DT_WORDBREAK);

}
#if 0
int GMList::CalcItemHeight(int index)
{
        ListItem* pItem = GetItem(index);
        //SmsListItemData_Details *p = (SmsListItemData_Details *)pItem->Data;
MsgListItemData* p = (MsgListItemData*)pItem->Data;
        HDC hdc = GetDC(NULL);
        ::SetTextColor(hdc, RGB(0,255,255));
        SelectObject(hdc, FontHelper::GetFont(24));
        RECT rcContent={32,35,GetWidth()-50,480};
        DrawText(hdc,p->StringText,wcslen(p->StringText),&rcContent,DT_LEFT|DT_TOP);
	ReleaseDC(NULL, hdc);
	return rcContent.bottom-rcContent.top+10;

}
#endif

void MainWnd::Login(const CMzString& account,const CMzString& password)
{
	std::string s_account=ws2s(account.C_Str());
	std::string s_pass=ws2s(password.C_Str());

	m_twitter.Login(s_account,s_pass);


    if(!FileExists(rcFile)){
	    IniCreateFile(rcFile);
    }
	IniWriteString(L"config",L"account",account,rcFile);
	IniWriteString(L"config",L"password",password,rcFile);

	LoadCache(cacheFile);
}
	
void MainWnd::SendStatus(const wchar_t* msg)
{
	AutoDialNet();
	std::string status_ = ws2s_utf8(wstring(msg));
	m_twitter.SetStatus(status_);
	CloseDialNet();

}

void MainWnd::UpdateStatus()
{
	AutoDialNet();
    m_twitter.UpdateStatus(m_id);
	CloseDialNet();

}

BOOL MainWnd::AutoDialNet()
{
	DWORD dwSize, dwNetWorkStatus;
	
	m_isDialConnect=FALSE;
	dwNetWorkStatus = QueryNetWorkStatus();
	if(dwNetWorkStatus == NETWORK_NONE){
		if(RESULT_OK == Dial_StartGprsConnect2(m_hWnd,GPRS_FORCE_APP_TYPE)){ //connect to EDGE
			m_isDialConnect = TRUE;
			return TRUE;
		}else
			return FALSE;
	}
	else
		return TRUE; //maybe has wifi
}

void MainWnd::CloseDialNet()
{
	if(m_isDialConnect)
		Dial_StopGprsConnect2(m_hWnd);
	m_isDialConnect=FALSE;
}

bool MainWnd::GetNetStatus()
{
	return m_twitter.GetNetStatus();

}

void MainWnd::Parser(const std::string& input,int big)
{

	std::string str1;
	std::string str2;
	str1=getStatusText(input);
	str2=getScreenName(input);
	std::wstring wstr1;
	std::wstring wstr2;
	wstr1=s2ws_unicode(str1.c_str());
	wstr2=s2ws_unicode(str2.c_str());

	AddMsg((wchar_t*)wstr2.c_str(),(wchar_t*)wstr1.c_str(),big);
	//std::string sid=getStatusId();
	if(0==big)
		m_id=getStatusId(input);
}


void MainWnd::LoadCache(const std::string& filename)
{
	using namespace std;

	ifstream infile;
	string str_content;
	infile.open(filename.c_str());
	if(!infile){
		//MzMessageBoxEx(m_hWnd, L"Load Cache Error", L"", MB_OK, SHK_RET_APPNOEXIT_SHELLTOP);
		return;
	}

	//getline(infile,str_content);
	while(getline(infile,str_content)){

		
	string strp;
	string tmp;
	size_t begin_pos=0;
	size_t pos;
	int count=0;
do{
	pos= str_content.find(",{");
	if(pos==std::string::npos)
		break;

	if(0==count)
		strp=str_content.substr(1,pos-1);
	else
		strp=str_content.substr(begin_pos,pos);
	tmp=str_content.substr(pos+1,std::string::npos);

	Parser(strp,count);
	
	count++;

	str_content=tmp;
	

}while(true);
   Parser(tmp,count);
   }
   infile.close();

}

void MainWnd::SaveCache(const std::string& filename)
{
	    fstream infile;
	    infile.open(filename.c_str(),ios::in);
	if(!infile)
		return;

	    fstream outfile;
	    outfile.open(cacheFile,ios::out|ios::app);
	    outfile<<endl;
		string strline;
	    while(getline(infile,strline)){
		    outfile<<strline<<endl;
	    }
	    outfile.close();
	    infile.close();

}


 void MainWnd::OnTimer(UINT_PTR nIDEvent)
{

	if(MZ_IDC_TIMER == nIDEvent){
	   UpdateStatus();
    if(GetNetStatus()){
	    LoadCache(updateFile);
	    SaveCache(updateFile);
    }
	}

}
