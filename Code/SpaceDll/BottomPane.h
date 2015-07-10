#pragma once



// CBottomPane form view

class CBottomPane : public CDialogEx
{
	friend class CMainView;
	DECLARE_DYNCREATE(CBottomPane)

public:
	CBottomPane();           // protected constructor used by dynamic creation
	virtual ~CBottomPane();

public:
//	enum { IDD = IDD_BOTTOMPANE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};


