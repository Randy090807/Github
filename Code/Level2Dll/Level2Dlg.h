#pragma once

// CLevel2Dlg dialog
class CMainView;
class AFX_EXT_CLASS CLevel2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLevel2Dlg)

public:
	CLevel2Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLevel2Dlg();

	BOOL Create(CWnd* pParentWnd = NULL);
// Dialog Data
//	enum { IDD = IDD_LEVEL2 };
	
protected:
	CMainView*	m_pView;
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnClose();
	afx_msg LRESULT OnConfigRefreshNotify(WPARAM wparam, LPARAM lparam);
};
