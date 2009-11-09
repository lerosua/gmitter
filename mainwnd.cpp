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
#include "settings.h"

BOOL MainWnd::OnInitDialog()
{
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }

    m_ScrollWin.SetPos(0,0,GetWidth(),GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR);
    m_ScrollWin.SetID(MZ_IDC_SCROLLWIN2);
    m_ScrollWin.EnableScrollBarV(true);
    AddUiWin(&m_ScrollWin);

    m_List.SetPos(0,5,GetWidth(),GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR-5);
    m_List.SetID(MZ_IDC_LIST);
    m_List.EnableScrollBarV(true);
    m_List.EnableNotifyMessage(true);
    m_List.SetItemHeight(90);
    m_List.SetTextColor(RGB(255,0,0));
    AddUiWin(&m_List);
    
    m_Toolbar.SetPos(0,GetHeight()-MZM_HEIGHT_TEXT_TOOLBAR,GetWidth(),MZM_HEIGHT_TEXT_TOOLBAR);
    m_Toolbar.SetButton(0,true,true,L"Exit");
    m_Toolbar.EnableLeftArrow(true);
    m_Toolbar.SetButton(1,true,true,L"I Say");
    m_Toolbar.SetButton(2,true,true,L"Update");
    m_Toolbar.SetID(MZ_IDC_TOOLBAR2);
    AddUiWin(&m_Toolbar);

    return TRUE;
}

void MainWnd::AddMsg(wchar_t* author,wchar_t* msg)
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
	m_List.InsertItem(li,0);
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
	    case MZ_IDC_TOOLBAR2:
	    {
		    int nIndex=lParam;
		    if(nIndex==0){
			    /* 退出程序*/
			   PostQuitMessage(0);
        
			    return;
		    }
		    if(1== nIndex){
			    /* 发推*/
#if 1
			SayWnd m_Saywnd;
			RECT rcWork = MzGetWorkArea();
			m_Saywnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd,0,WS_POPUP);
			m_Saywnd.SetAnimateType_Show(5);
			m_Saywnd.SetAnimateType_Hide(6);
			m_Saywnd.DoModal();
#else
			SayWnd *m_Saywnd=new SayWnd(*this);
			RECT rcWork = MzGetWorkArea();
			m_Saywnd->Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd,0,WS_POPUP);
			m_Saywnd->SetAnimateType_Show(5);
			m_Saywnd->SetAnimateType_Hide(6);
			m_Saywnd->DoModal();
#endif
		return;
		

		    }
		    if(2 == nIndex){
			    /* 更新*/
			    EndModal(ID_OK);
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
	rcText.bottom=rcText.top+RECT_HEIGHT(rcText)/4;
	::SetTextColor(hdcDst,RGB(0,200,0));
	MzDrawText(hdcDst,pmlid->StringAuthor.C_Str(), &rcText,DT_LEFT|DT_BOTTOM|DT_SINGLELINE|DT_END_ELLIPSIS);

	// for message
	rcText.top=rcText.bottom;
	rcText.bottom=prcItem->bottom;
	::SetTextColor(hdcDst,RGB(200,200,200));
	HFONT hf=FontHelper::GetFont(16);
	SelectObject(hdcDst,hf);
	//MzDrawText(hdcDst,pmlid->StringText.C_Str(), &rcText,DT_LEFT|DT_TOP|DT_SINGLELINE|DT_END_ELLIPSIS);
	MzDrawText(hdcDst,pmlid->StringText.C_Str(), &rcText,DT_LEFT|DT_WORDBREAK|DT_END_ELLIPSIS);

}


void MainWnd::Login(const wchar_t*  account,const wchar_t* password)
{
	std::wstring p_account(account);
	std::wstring p_pass(password);
	std::string s_account=ws2s(p_account);
	std::string s_pass=ws2s(p_pass);
	Setting conf;
	conf.applySettings(s_account,s_pass);
	conf.saveSettings();
	m_twitter.Login(s_account,s_pass);
}
	
void MainWnd::SendStatus(const wchar_t* msg)
{
	std::string status_ = ws2s(wstring(msg));
	m_twitter.SetStatus(status_);

}
