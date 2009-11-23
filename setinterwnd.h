/*
 * =====================================================================================
 *
 *       Filename:  setinterwnd.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月23日 12时52分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#ifndef SET_INTER_WND_H_
#define SET_INTER_WND_H_
#include <mzfc_inc.h>

#define MZ_IDC_SETINTERWND_SCROLLWIN 920
#define MZ_IDC_SETINTERWND_BTN_10    921
#define MZ_IDC_SETINTERWND_BTN_15    922
#define MZ_IDC_SETINTERWND_BTN_20    923
#define MZ_IDC_SETINTERWND_BTN_30    924
#define MZ_IDC_SETINTERWND_TOOLBAR   925


class SetInterWnd:public CMzWndEx
{
	MZ_DECLARE_DYNAMIC(SetInterWnd);
	public:
	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);

	protected:
	UiScrollWin m_ScrollWin;
	UiToolbar_Text m_Toolbar;
	static int _MAX=5;
	UiButtonEx m_btnCount[_MAX];
	int	_count;



};

#endif
