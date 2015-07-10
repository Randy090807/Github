#pragma once


// CMainView view

class AFX_EXT_CLASS CMainView : public CView
{
	DECLARE_DYNCREATE(CMainView)

protected:
	CMainView();           // protected constructor used by dynamic creation
	virtual ~CMainView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	CSplitterWnd	m_wndSplitter;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
};


