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
#define MZ_IDC_PAGECOUNT_BTN_3      932
#define MZ_IDC_PAGECOUNT_BTN_5      933
#define MZ_IDC_PAGECOUNT_BTN_10      934
#define MZ_IDC_PAGECOUNT_BTN_15      935

class PageCountWnd:public CMzWndEx
{

	MZ_DECLARE_DYNAMIC(PageCountWnd);
	public:
	virtual BOOL OnInitDialog();
	virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
	void set_select(const int count_);


	protected:
	UiScrollWin m_ScrollWin;
	UiToolbar_Text m_Toolbar;
	static int _MAX=4;
	UiButtonEx m_btnCount[_MAX];
	int	_count;









};


#endif
