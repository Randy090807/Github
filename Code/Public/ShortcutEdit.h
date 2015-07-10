#pragma once


// CShortcutEdit

class AFX_EXT_CLASS CShortcutEdit : public CEdit
{
	DECLARE_DYNAMIC(CShortcutEdit)

public:
	CShortcutEdit();
	virtual ~CShortcutEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


