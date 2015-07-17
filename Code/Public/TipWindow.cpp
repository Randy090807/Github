#include "stdafx.h"
#include "TipWindow.h"


CTipWindow::CTipWindow()
	:CXTPTipWindow()
{
}


CTipWindow::~CTipWindow()
{
}

BOOL CTipWindow::Create(CWnd* pParentWnd)
{
	ASSERT(pParentWnd);
	return CXTPTipWindow::Create(pParentWnd);
}

void CTipWindow::Show(LPCTSTR lpText, int nID)
{
	SetTipText(_T("ÌבÊ¾"), lpText);

	CRect rect;
	GetParent()->GetDlgItem(nID)->GetWindowRect(&rect);
	SetMargins(CSize(1, 1));
	SetLineSpace(1);
	ShowTipWindow(CPoint(rect.left - 5, rect.bottom - 5));
}
