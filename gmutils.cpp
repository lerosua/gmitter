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
