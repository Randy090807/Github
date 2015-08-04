#pragma once

#define CDCSTAUTSBAR_HEIGHT	20

class AFX_EXT_CLASS CCDStatusBar
{
public:
	
	enum enStatus{ STATUS_NORMAL = 0, STATUS_SUCCESS = 1, STATUS_ERROR = 2 };
	CCDStatusBar(CWnd* pParent);
	~CCDStatusBar();

	void UpdateStatus(LPCTSTR lpText, CCDStatusBar::enStatus eStatus = CCDStatusBar::STATUS_NORMAL);
	void DrawItem(CDC* pDC);

private:
	CString			m_szText;
	enStatus		m_enStatus;
	CWnd*			m_pParentWnd;
	
};

