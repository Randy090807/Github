#pragma once

#include "../Public/CDStatusBar.h"

// CSpaceDlg dialog
class CMainView;
class AFX_EXT_CLASS CSpaceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSpaceDlg)

public:
	CSpaceDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSpaceDlg();

// Dialog Data
	/*enum { IDD = IDD_SPACE };*/
	BOOL Create(CWnd* pParentWnd);
	
	
	CCDStatusBar	m_StatusBar;
protected:
	void QueryRequest();
	CMainView*	m_pView;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg LRESULT OnMsgSrvDataNofity(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgSrvDataReport(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgSrvDataNofity2(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgSrvDataReport2(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgInitComplete(WPARAM wparam, LPARAM lparam);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
