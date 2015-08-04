#pragma once

#include "../Public/CDStatusBar.h"
// CRecordDlg dialog

class AFX_EXT_CLASS CRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRecordDlg)

public:
	CRecordDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRecordDlg();

// Dialog Data
//	enum { IDD = IDD_RECORD };

	BOOL Create(CWnd* pParentWnd = NULL);

protected:
	CSplitterWnd	m_wndSplitter;
	CFrameWnd*		m_pMyFrame;
	CCDStatusBar	m_StatusBar;

	void QueryRequest();
	void QueryResponse();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg LRESULT OnConfigRefreshNotify(WPARAM wparam, LPARAM lparam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnMsgSrvDataNofity(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgInitComplete(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgUpdateData(WPARAM wparam, LPARAM lparam);
	afx_msg void OnPaint();
	afx_msg LRESULT OnMsgSrvDataReport(WPARAM wparam, LPARAM lparam);
};
