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
#define MZ_IDC_SETINTERWND_BTN_5    924
#define MZ_IDC_SETINTERWND_BTN_3    925
#define MZ_IDC_SETINTERWND_TOOLBAR   926
#define _MAXT  4

class SetInterWnd:public CMzWndEx
{
	MZ_DECLARE_DYNAMIC(SetInterWnd);
	public:
	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
	void set_select(const int count_);
	void select();
	protected:
	UiScrollWin m_ScrollWin;
	UiToolbar_Text m_toolbar;
	
	UiButtonEx m_btnCount[_MAXT];
	int	_count;



};

#endif
