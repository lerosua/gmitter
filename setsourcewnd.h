/*
 * =====================================================================================
 *
 *       Filename:  sourcewnd.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月24日 16时51分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#ifndef SET_SOURCE_WND_H_
#define SET_SOURCE_WND_H_

#include <mzfc_inc.h>

#define MZ_IDC_SOURCEWND_SCROLLWIN 940
#define MZ_IDC_SOURCEWND_TOOLBAR   941
#define MZ_IDC_SOURCEWND_CLINET0   942
#define MZ_IDC_SOURCEWND_CLINET1   943
#define MZ_IDC_SOURCEWND_CLINET2   944
#define MZ_IDC_SOURCEWND_CLINET3   945
#define MZ_IDC_SOURCEWND_CLINET4   946
#define MZ_IDC_SOURCEWND_CLINET5   947
#define MZ_IDC_SOURCEWND_CLINET6   948
#define MZ_IDC_SOURCEWND_CLINET7   949
#define MZ_IDC_SOURCEWND_CLINET8   950
#define MZ_IDC_SOURCEWND_CLINET9   951

#define SOURCE_MAX 10

wchar* client[SOURCE_MAX]={"iTweet","EchoFon","Gravity","twidroid","twhirl","dabr","twittai","Seesmic","Brizzly","Tweetie"};

class SetSourceWnd:public CMzWndEx
{
	MZ_DECLARE_DYNAMIC(SetSourceWnd);
	public:

	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
	void set_select(const int select_){_select = select_;}
	void select();
	protected:
	UiScrollWin m_ScrollWin;
	UiToolbar_Text m_toolbar;

	UiButtonEx m_btnCount[SOURCE_MAX];
	int _select;
	
};

#endif
