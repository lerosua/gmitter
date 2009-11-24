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
#include "confini.h"
#include "gmutils.h"
#include <CallNotifyApi.h>

#include <sstream>
#include <string>
#include <fstream>
#include <stdio.h>

MainWnd::MainWnd():_status_id("")
		   ,_message_id("")
		   ,_mentions_id("")
		   ,_favorites_id("")
		   ,_friends_id("")
		   ,_public_id("")
		   ,_locked(false)
		   ,_current_page(1)
		   ,_current_page_type(STATUS_PAGE)
		   ,_path("\\Disk\\Program Files\\gmitter")
{

}
MainWnd::~MainWnd()
{
	CloseDialNet();

}
void MainWnd::StartTimer(int min_)
{
	SetTimer(m_hWnd,MZ_IDC_TIMER,min_*60*1000,NULL);
}
BOOL MainWnd::OnInitDialog()
{
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }

    m_Top.SetPos(0,0,GetWidth(),MZM_HEIGHT_ICON_TOOLBAR-10);
    m_Top.SetID(MZ_IDC_MAINWND_TOP);
    m_Top.SetButton(0,true,true,L"刷新");
    m_Top.SetButton(1,true,true,L"推倒");
    m_Top.SetButton(2,true,true,L"发推");
    //m_Top.SetText(L"推倒世界");
    AddUiWin(&m_Top);

    //m_imgUpdate_normal.LoadImage(L"\\Disk\\Program Files\\gmitter\\res\\update.png");
//    m_imgUpdate_normal.LoadImageFromRes(MzGetInstanceHandle(),RT_RCDATA,MAKEINTRESOURCE(IDR_PNG_UPDATE),TRUE,TRUE);
//    m_imgUpdate_press.LoadImageFromRes(MzGetInstanceHandle(),RT_RCDATA,MAKEINTRESOURCE(IDR_PNG_UPDATE_PRESS),TRUE,TRUE);
//    m_imgWrite_normal.LoadImageFromRes( MzGetInstanceHandle(),RT_RCDATA,MAKEINTRESOURCE(IDR_PNG_WRITE) ,TRUE,TRUE);
//    m_imgWrite_press.LoadImageFromRes(  MzGetInstanceHandle(),RT_RCDATA,MAKEINTRESOURCE(IDR_PNG_WRITE_PRESS),TRUE,TRUE);
//
//    m_btn_update.SetID(MZ_IDC_UPDATE);
//    m_btn_update.SetPos(2,2,50,50);
//    m_btn_update.SetImage_Normal(&m_imgUpdate_normal);
//    m_btn_update.SetImage_Pressed(&m_imgUpdate_press);
//    m_btn_update.SetMode(UI_BUTTON_IMAGE_MODE_ALWAYS_SHOW_NORMAL);
//    m_btn_update.SetTextColor(RGB(255,255,255));
//    AddUiWin(&m_btn_update);
//
//    m_btn_write.SetID(MZ_IDC_WRITE);
//    m_btn_write.SetPos(GetWidth()-52,2,50,50);
//    m_btn_write.SetImage_Normal(&m_imgWrite_normal);
//    m_btn_write.SetImage_Pressed(&m_imgWrite_press);
//    m_btn_write.SetMode(UI_BUTTON_IMAGE_MODE_ALWAYS_SHOW_NORMAL);
//    m_btn_write.SetTextColor(RGB(255,255,255));
//	AddUiWin(&m_btn_write);

    //m_ScrollWin.SetPos(0,0,GetWidth(),GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR);
    m_ScrollWin.SetPos(0,MZM_HEIGHT_ICON_TOOLBAR-10,GetWidth(),GetHeight()-2*MZM_HEIGHT_TEXT_TOOLBAR);
    m_ScrollWin.SetID(MZ_IDC_SCROLLWIN2);
    m_ScrollWin.EnableScrollBarV(true);
    AddUiWin(&m_ScrollWin);

    m_List.SetPos(0,MZM_HEIGHT_ICON_TOOLBAR-15,GetWidth(),GetHeight()-2*MZM_HEIGHT_TEXT_TOOLBAR-5);
    //m_List.SetPos(0,5,GetWidth(),GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR-5);
    m_List.SetID(MZ_IDC_STATUS_LIST);
    m_List.EnableScrollBarV(true);
    m_List.EnableNotifyMessage(true);
    m_List.SetItemHeight(90);
    m_List.SetTextColor(RGB(255,0,0));
    m_List.EnableVaryItemHeight(true);
    m_List.EnableDragModeH(true);
    AddUiWin(&m_List);
    

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

void MainWnd::AddPostMsg(wchar_t* msg_)
{

	if(STATUS_PAGE == _current_page)
		AddMsg(m_account.C_Str(),msg_,L"刚刚");
}

void MainWnd::AddMsg(wchar_t* author,wchar_t* msg,wchar_t* time_,int num)
{
	ListItem li;
	CMzString strAuthor(256);
	CMzString strMsg(256);
	CMzString strTime(256);
	wsprintf(strAuthor.C_Str(),author);
	wsprintf(strMsg.C_Str(), msg);
	wsprintf(strTime.C_Str(),time_);

	MsgListItemData* pmlid=new MsgListItemData;
	pmlid->StringAuthor = strAuthor;
	pmlid->StringText = strMsg;
	pmlid->StringTime = strTime;

	li.Data = pmlid;
	m_List.InsertItem(li,-1);
}

void MainWnd::DrawNextItem()
{
	ListItem li;
	MsgListItemData* pmlid=new MsgListItemData;
	pmlid->StringAuthor = L"Next";
	pmlid->StringText = L"Next";
	pmlid->StringTime = L"Next";

	li.Data = pmlid;
	//li.Text = MORE.c_str();
	m_List.AddItem(li);
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

			if(nID== MZ_IDC_STATUS_LIST && nNotify == MZ_MN_LBUTTONDOWN){
				if(!m_List.IsMouseDownAtScrolling()& !m_List.IsMouseMoved()){
					int nIndex=m_List.CalcIndexOfPos(x,y);
					if(nIndex<0)
						break;
					m_List.SetSelectedIndex(nIndex);
					m_List.Invalidate();
					m_List.Update();
					if(nIndex+1 > ConfIni::getPageCount()){
						_current_page++;
						MzBeginWaitDlg(m_hWnd);
						LoadCache(_current_page_type,_current_page);
						MzEndWaitDlg();
					}
				}
				return 0;
			}

			//double click
			if(nID== MZ_IDC_STATUS_LIST && nNotify == MZ_MN_LBUTTONDBLCLK){

				
				int nIndex=m_List.CalcIndexOfPos(x,y);
				if(nIndex<0|| (nIndex+1 > ConfIni::getPageCount()))
					break;
				int id_ = GMUtils::popup_menu_status(m_hWnd,L"lerosua");
				switch(id_){
					case MZ_IDC_POPMENU_RETURN:
						break;
					case MZ_IDC_POPMENU_REPLY:
						{
						ListItem* pItem_ = m_List.GetItem(nIndex);
						if(pItem_){
							MsgListItemData* mlid_ = (MsgListItemData*)pItem_->Data;
							CMzString reply_ = CMzString(L"@")+mlid_->StringAuthor+CMzString(L" ") ;

							// try put follow code to GMUtils
						SayWnd *m_Saywnd=new SayWnd(*this);
						RECT rcWork = MzGetWorkArea();
						m_Saywnd->Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd,0,WS_POPUP);
						m_Saywnd->SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_TOP_TO_BOTTOM_2);
						m_Saywnd->SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2);
						m_Saywnd->SetText(reply_.C_Str());
						m_Saywnd->DoModal();
						}
							

						}
						break;
					case MZ_IDC_POPMENU_RT:
						{
						ListItem* pItem_ = m_List.GetItem(nIndex);
						if(pItem_){
							MsgListItemData* mlid_ = (MsgListItemData*)pItem_->Data;
							CMzString reply_ = CMzString(L"RT:@")+mlid_->StringAuthor+CMzString(L":")+mlid_->StringText ;

							// try put follow code to GMUtils
						SayWnd *m_Saywnd=new SayWnd(*this);
						RECT rcWork = MzGetWorkArea();
						m_Saywnd->Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd,0,WS_POPUP);
						m_Saywnd->SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_TOP_TO_BOTTOM_2);
						m_Saywnd->SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2);
						m_Saywnd->SetText(reply_.C_Str());
						m_Saywnd->DoModal();
						}
							

						}

						break;
					case MZ_IDC_POPMENU_DM:
						{
						ListItem* pItem_ = m_List.GetItem(nIndex);
						if(pItem_){
							MsgListItemData* mlid_ = (MsgListItemData*)pItem_->Data;
							CMzString reply_ = CMzString(L"d ")+mlid_->StringAuthor+CMzString(L" ") ;

							// try put follow code to GMUtils
						SayWnd *m_Saywnd=new SayWnd(*this);
						RECT rcWork = MzGetWorkArea();
						m_Saywnd->Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd,0,WS_POPUP);
						m_Saywnd->SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_TOP_TO_BOTTOM_2);
						m_Saywnd->SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2);
						m_Saywnd->SetText(reply_.C_Str());
						m_Saywnd->DoModal();
						}
							

						}

						break;
					default:
						break;
				}

				return 0;
			}
			//处理列表控件的鼠标移动通知 
			if(nID== MZ_IDC_STATUS_LIST && nNotify == MZ_MN_MOUSEMOVE){
				if(m_List.GetSelectedIndex()!=-1){
					m_List.SetSelectedIndex(-1);
					m_List.Invalidate();
					m_List.Update();
				}
				return 0;
			}
			if(nID == MZ_IDC_STATUS_LIST && nNotify == MZ_WM_LIST_ITEM_DRAG_H){

				MzMessageBoxEx(m_hWnd, L"Just test dragH", L"", MB_OK, SHK_RET_APPNOEXIT_SHELLTOP);
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
	    case MZ_IDC_MAINWND_TOP:
			    {
				    int nIndex=lParam;
				    if(0==nIndex){

			MzBeginWaitDlg(m_hWnd);
			if(getLocked()){
			   UpdateList();
			    if(GetNetStatus()){
				    SaveCache(_current_page_type);
				    LoadCache(_current_page_type,_current_page);
			    }
			    freeLocked();
			}
			MzEndWaitDlg();
			    return;
				    }
				    if(1==nIndex){
				    }
				    if(2==nIndex){

			SayWnd *m_Saywnd=new SayWnd(*this);
			RECT rcWork = MzGetWorkArea();
			m_Saywnd->Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd,0,WS_POPUP);
			m_Saywnd->SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_TOP_TO_BOTTOM_2);
			m_Saywnd->SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2);
			m_Saywnd->DoModal();
				    }
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
		    if(0==nIndex){
			    /** freiends_timeline stauts page*/
			    if(_current_page>1 || STATUS_PAGE != _current_page_type){
				    _current_page=1;
				    _current_page_type= STATUS_PAGE;
				    MzBeginWaitDlg(m_hWnd);
				    LoadCache(_statusFile,_current_page);
				    MzEndWaitDlg();
			    }
		    }
		    if(1== nIndex){
			    /** mentions page*/
			    if(_current_page>1 || MENTIONS_PAGE != _current_page_type){
				    _current_page =1;
				    _current_page_type = MENTIONS_PAGE;
				    MzBeginWaitDlg(m_hWnd);
				    LoadCache(_mentionsFile,_current_page);
				    MzEndWaitDlg();
			    }

			return;
		

		    }
		    if(2 == nIndex){
			    /** message page*/
			    if(_current_page>1 || MESSAGE_PAGE != _current_page_type){
				    _current_page =1;
				    _current_page_type = MESSAGE_PAGE;
				    MzBeginWaitDlg(m_hWnd);
				    LoadCache(_messageFile,_current_page);
				    MzEndWaitDlg();
			    }

			
			    return;
		    }
		    if(3 == nIndex){
			    /** favorites page*/
			    if(_current_page > 1 || PUBLIC_PAGE!= _current_page_type ){
				    _current_page = 1;
				    _current_page_type = PUBLIC_PAGE;
				    MzBeginWaitDlg(m_hWnd);
				    LoadCache(_publicFile,_current_page);
				    MzEndWaitDlg();
			    }


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
		//if(mlid)
			//;//do something
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

	// 背景色
	RECT bgRect = *prcItem;
	bgRect.top = bgRect.top + 1;
	bgRect.bottom = bgRect.bottom - 1;

	if(0 == nIndex % 2) {  
	HBRUSH bgBrush = CreateSolidBrush(RGB(230, 230, 250));
	::FillRect(hdcDst, &bgRect, bgBrush);
	}



	if(GetSelectedIndex() == nIndex )
		MzDrawSelectedBg(hdcDst,prcItem);

	//if(pItem->Text == L"Next"){
	if(pmlid->StringAuthor == L"Next" && pmlid->StringText == L"Next"){

		HBRUSH bgBrush = CreateSolidBrush(RGB(220, 220, 220));
		::FillRect(hdcDst, &bgRect, bgBrush);
		MzDrawText(hdcDst,L"下一页", prcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
		return;
	}
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
	rcText.right=rcText.right - 200;
	rcText.bottom=rcText.top+RECT_HEIGHT(rcText)/3;
	::SetTextColor(hdcDst,RGB(0,200,0));
	MzDrawText(hdcDst,pmlid->StringAuthor.C_Str(), &rcText,DT_LEFT|DT_BOTTOM|DT_SINGLELINE|DT_END_ELLIPSIS);

	//for timetrim
	rcText.left = rcText.right;
	rcText.right = rcText.left+200;
	::SetTextColor(hdcDst,RGB(200,200,200));
	HFONT hf_=FontHelper::GetFont(16);
	SelectObject(hdcDst,hf_);
	MzDrawText(hdcDst,pmlid->StringTime.C_Str(), &rcText,DT_RIGHT|DT_TOP  |DT_SINGLELINE|DT_END_ELLIPSIS);

	// for message
	rcText.top=rcText.bottom;
	rcText.bottom=prcItem->bottom;
	rcText.left=MZM_MARGIN_MAX*2;
	rcText.right=rcText.right-MZM_MARGIN_MAX;
	::SetTextColor(hdcDst,RGB(0,100,0));
	//::SetTextColor(hdcDst,RGB(200,200,200));
	HFONT hf=FontHelper::GetFont(24);
	SelectObject(hdcDst,hf);
	MzDrawText(hdcDst,pmlid->StringText.C_Str(), &rcText,   DT_LEFT | DT_WORDBREAK | DT_EDITCONTROL | DT_END_ELLIPSIS | DT_NOPREFIX);

}
int GMList::CalcItemHeight(int index)
{

//	if(GetSelectedIndex() == nIndex )
	int height=0;
	int lines=0;
        ListItem* pItem = GetItem(index);
	MsgListItemData* pmlid = (MsgListItemData*)pItem->Data;

	lines = pmlid->StringText.Length()/16+1;
	height = 40+lines*24;
	height = height<100?100:height;
	return height;

}

void MainWnd::SetUserDir(const std::string& user_)
{
	wstring wdir_ = s2ws(_path+user_);
	Mkdirs(wdir_.c_str());

	_statusFile=_path+user_+"\\cache.json";
	_messageFile=_path+user_+"\\message.json";
	_favoritsFile=_path+user_+"\\favorites.json";
	_mentionsFile=_path+user_+"\\mentions.json";
	_publicFile=_path+user_+"\\public.json";
	_friendsFile=_path+user_+"\\friends.json";
	_updateFile=_path+user_+"\\update.json";

}
bool MainWnd::Login(const CMzString& account,const CMzString& password)
{
	std::string s_account=ws2s(account.C_Str());
	std::string s_pass=ws2s(password.C_Str());

	ConfIni::setAccount(account.C_Str());

	m_twitter.SetApi(ws2s(ConfIni::getTwitterApi()));

	AutoDialNet();
	if(m_twitter.Login(s_account,s_pass))
		SetUserDir(s_account);
	else{
		return false;
	}

	if(ConfIni::isRememberPassword()){
		ConfIni::setPassword(password.C_Str());
	}

	ConfIni::save();

	m_account = account;
	LoadCache(_statusFile,_current_page);
	StartTimer(ConfIni::getUpdateInterval());
	
	m_Top.SetButton(1,true,true,m_account.C_Str());
	return true;
}
	
void MainWnd::SendStatus(const wchar_t* msg)
{
	AutoDialNet();
	std::string status_ = ws2s_utf8(wstring(msg));
	m_twitter.SetStatus(status_);
	//CloseDialNet();

}
void MainWnd::UpdateList()
{
	AutoDialNet();
	std::string id_ ;
	switch(_current_page_type){
		case STATUS_PAGE:
			id_ = _status_id;
			m_twitter.UpdateStatus(id_);
			break;
		case MENTIONS_PAGE:
			id_ = _mentions_id;
			m_twitter.UpdateMentions(id_);
			break;
		case MESSAGE_PAGE:
			id_ = _message_id;
			m_twitter.UpdateDM(_message_id);
			break;
		case FAVORITES_PAGE:
			id_ = _favorites_id;
			break;
		case FRIEDNS_PAGE:
			id_ = _friends_id;
			break;
		case PUBLIC_PAGE:
			id_ = _public_id;
			m_twitter.UpdatePublic();
			break;
		default:
			//CloseDialNet();
			return;
	}

	//CloseDialNet();

}
void MainWnd::UpdateStatus()
{
	AutoDialNet();
        m_twitter.UpdateStatus(_status_id);
	//CloseDialNet();

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
	if(0==big){
		if( STATUS_PAGE == _current_page_type )
			_status_id=getStatusId(input);
		else if( FAVORITES_PAGE == _current_page_type)
			_favorites_id = getStatusId(input);
		else if( MENTIONS_PAGE == _current_page_type)
			_mentions_id = getStatusId(input);
		else if( MESSAGE_PAGE == _current_page_type)
			_message_id = getStatusId(input);
		
	}

if(big>= (_current_page-1)*ConfIni::getPageCount()){
	std::string str_msg;
	std::string str_name;
	std::string str_time;
	std::string str_source;
	str_name=getScreenName(input);
	if(str_name.empty())
		return;
	str_msg=getStatusText(input);
	str_time = getCreateTime(input);
	str_source = getSource(input);
	if(!str_source.empty());
		str_time= str_time +" "+str_source;
	std::wstring wstr_msg;
	std::wstring wstr_name;
	std::wstring wstr_time;
	wstr_msg=s2ws_unicode(str_msg.c_str());
	wstr_name=s2ws_unicode(str_name.c_str());
	wstr_time=s2ws_unicode(str_time.c_str());

	AddMsg((wchar_t*)wstr_name.c_str(),(wchar_t*)wstr_msg.c_str(),(wchar_t*)wstr_time.c_str(),big);
	}
}

void MainWnd::LoadCache(page_type type_,int page_)
{
	switch(type_){
		case STATUS_PAGE:
			LoadCache(_statusFile,page_);
			break;
		case MESSAGE_PAGE:
			LoadCache(_messageFile,page_);
			break;
		case MENTIONS_PAGE:
			LoadCache(_mentionsFile,page_);
			break;
		case FRIEDNS_PAGE:
			LoadCache(_friendsFile,page_);
			break;
		case FAVORITES_PAGE:
			LoadCache(_favoritsFile,page_);
			break;
		case PUBLIC_PAGE:
			LoadCache(_publicFile,page_);
			break;
		default:
			break;
	}

}
void MainWnd::LoadCache(const std::string& filename,int page_)
{
	using namespace std;

	ifstream infile;
	string str_content;
	infile.open(filename.c_str());
	if(!infile){
		return;
	}

	m_List.RemoveAll();

	int end_=page_*ConfIni::getPageCount();
	int global_count_=0;

	while(getline(infile,str_content)){
		if(str_content.empty())
			continue;

	if(global_count_>end_){
		//DrawNextItem();
		break;
	}
		
	string strp;
	string tmp;
	size_t begin_pos=0;
	size_t pos;
	int count=0;
do{
	pos= str_content.find(",{");
	if(pos==std::string::npos){
		Parser(str_content,1);	
		break;
	}

	if(0==count)
		strp=str_content.substr(1,pos-1);
	else
		strp=str_content.substr(begin_pos,pos);
	tmp=str_content.substr(pos+1,std::string::npos);

	if(global_count_<end_){
		Parser(strp,count);
		global_count_++;
	
		count++;

		str_content=tmp;
	}else{
		DrawNextItem();
		break;
	}
	

}while(true);
	  if(global_count_<end_)
		   Parser(tmp,count);
	   str_content.clear();
   }
   infile.close();

   m_List.ScrollTo(UI_SCROLLTO_TOP,0,false);
   m_List.Invalidate();
   m_List.Update();
}

void MainWnd::SaveCache(page_type type_)
{
	switch(type_){
		case STATUS_PAGE:
			SaveCache(_statusFile);
			break;
		case MESSAGE_PAGE:
			SaveCache(_messageFile);
			break;
		case MENTIONS_PAGE:
			SaveCache(_mentionsFile);
			break;
		case FRIEDNS_PAGE:
			SaveCache(_friendsFile);
			break;
		case FAVORITES_PAGE:
			SaveCache(_favoritsFile);
			break;
		case PUBLIC_PAGE:
			SaveCache(_publicFile);
			break;
		default:
			break;
	}

}
void MainWnd::SaveCache(const std::string& filename)
{
	    fstream infile;
	    infile.open(filename.c_str(),ios::in);
	    //infile.open(_updateFile,ios::in);
	if(!infile){
		//infile不存在，要新建
		fstream pfile_;
		pfile_.open(filename.c_str(),ios::out);
		pfile_.close();
	    infile.open(filename.c_str(),ios::in);
	}

	    fstream outfile;
	    outfile.open(_updateFile.c_str(),ios::out|ios::app);
	    //outfile.open(filename.c_str(),ios::out|ios::app);
	    outfile<<endl;
		string strline;
	    while(getline(infile,strline)){
		    outfile<<strline<<endl;
	    }
	    outfile.close();
	    infile.close();
	//rename(_updateFile,_statusFile);

	    //rename _updateFile to cacheFile
	    string strline_;
	    fstream outfile2;
	    fstream infile2;
	    outfile2.open(filename.c_str(),ios::out);
	    infile2.open(_updateFile.c_str(),ios::in);
	    int count_ =0;
	    while(getline(infile2,strline_)){
		    outfile2<<strline_<<endl;
		    count_++;
		    if(count_>100)
			    break;
	    }
	    outfile2.close();
	    infile2.close();
}


 void MainWnd::OnTimer(UINT_PTR nIDEvent)
{

	if(MZ_IDC_TIMER == nIDEvent){
		if(getLocked()){
	   UpdateStatus();
    if(GetNetStatus()){
	    //SaveCache(_updateFile);
	    SaveCache(_current_page_type);
	    if(1 == _current_page)
		    //LoadCache(_statusFile,_current_page);
	    	    LoadCache(_current_page_type,_current_page);
    }
		freeLocked();
		}
	}

}
bool MainWnd::getLocked()
{
	if(_locked)
		return false;
	_locked = true;
	return _locked;
}

void MainWnd::freeLocked()
{
	_locked = false;
}
const wstring MainWnd::MORE=L"Next";
