/*
 * =====================================================================================
 *
 *       Filename:  GMUtils.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月17日 13时37分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#include "gmutils.h"

GMUtils::GMUtils()
{

}

GMUtils::~GMUtils()
{

}

int GMUtils::popup_menu_status(HWND hParentWnd,const wstring& user_id)
{
	CPopupMenu popup_menu;
	struct PopupMenuItemProp menu_item;

	menu_item.itemCr = MZC_BUTTON_PELLUCID;
	menu_item.itemRetID = MZ_IDC_POPMENU_RETURN;
	menu_item.str = L"返回";
	popup_menu.AddItem(menu_item);

	menu_item.itemCr = MZC_BUTTON_PELLUCID;
	menu_item.itemRetID = MZ_IDC_POPMENU_REPLY;
	menu_item.str = L"Reply";
	popup_menu.AddItem(menu_item);

	menu_item.itemCr = MZC_BUTTON_PELLUCID;
	menu_item.itemRetID = MZ_IDC_POPMENU_RT;
	menu_item.str = L"Retweet";
	popup_menu.AddItem(menu_item);

	menu_item.itemCr = MZC_BUTTON_PELLUCID;
	menu_item.itemRetID = MZ_IDC_POPMENU_DM;
	menu_item.str = L"Send a DM";
	popup_menu.AddItem(menu_item);

	RECT rc = MzGetWorkArea();
	rc.top = rc.bottom - popup_menu.GetHeight();
	popup_menu.Create(rc.left, rc.top, RECT_WIDTH(rc), RECT_HEIGHT(rc), hParentWnd, 0, WS_POPUP);

	return popup_menu.DoModal();
}
#if 0
void GMUtils::edit_post_status_wnd(HWND hparentwnd,MainWnd* mwnd,const wstring& str_)
{

			SayWnd *m_Saywnd=new SayWnd(*mwnd);
			RECT rcWork = MzGetWorkArea();
			m_Saywnd->Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),hparentwnd,0,WS_POPUP);
			m_Saywnd->SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_TOP_TO_BOTTOM_2);
			m_Saywnd->SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2);
			m_Saywnd->DoModal();

}
#endif 
