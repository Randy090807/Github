#pragma once

class AFX_EXT_CLASS CTipWindow : public CXTPTipWindow
{
public:
	CTipWindow();
	~CTipWindow();
public:
	BOOL Create(CWnd* pParentWnd);
	void Show(LPCTSTR lpText, int nID);
};

