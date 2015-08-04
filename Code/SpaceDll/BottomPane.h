#pragma once

#define UM_SPCAE_DEAL_ALL		WM_USER+0x701
#define UM_SPCAE_DEAL_EMPTY		WM_USER+0x702
#define UM_SPCAE_DEAL_MORE		WM_USER+0x703

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

	CString m_szNetPL;
	CString m_szFloatPL;
	CString m_szAmont;
	CString m_szColsePL;
	CString m_szVolume;
	CString m_szFee;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnAll();
	afx_msg void OnBnClickedBtnMore();
	afx_msg void OnBnClickedBtnEmpty();
	BOOL PreTranslateMessage(MSG* pMsg);

	int m_nPrice;
};


