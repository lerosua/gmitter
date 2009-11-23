/*
 * =====================================================================================
 *
 *       Filename:  pagecountwnd.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年11月23日 14时22分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lerosua (), lerosua@gmail.com
 *        Company:  cyclone
 *
 * =====================================================================================
 */

#ifndef PAGE_COUNT_WND_H_
#define PAGE_COUNT_WND_H_

#include <mzfc_inc.h>

#define MZ_IDC_PAGECOUNT_SCROLLWND  930
#define MZ_IDC_PAGECOUNT_TOOLBAR    931
#define MZ_IDC_PAGECOUNT_BTN_10      934
#define MZ_IDC_PAGECOUNT_BTN_15      935
#define MZ_IDC_PAGECOUNT_BTN_20      936
#define MZ_IDC_PAGECOUNT_BTN_25      937
#define MZ_IDC_PAGECOUNT_BTN_30      938
#define _MAXP  5
class PageCountWnd:public CMzWndEx
{

	MZ_DECLARE_DYNAMIC(PageCountWnd);
	public:
	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
	void set_select(const int count_){ _count = count_; };
	void select();

	protected:
	UiScrollWin m_ScrollWin;
	UiToolbar_Text m_toolbar;
	
	UiButtonEx m_btnCount[_MAXP];
	int	_count;









};


#endif
