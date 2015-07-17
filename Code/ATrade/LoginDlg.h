#pragma once

#include "../Public/TipWindow.h"
// CLoginDlg dialog

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoginDlg();

// Dialog Data
	enum { IDD = IDD_LOGIN };

protected:
	CString m_szAdmin;
	CString m_szOperator;
	CString m_szAssetsUnit;
	CString m_szTradeUnit;
	CString m_szPassword;
	BOOL m_bSavePwd;
	CString m_szStatus;

	CTipWindow	m_wndTip;

	BOOL Verify();
	void UpdateStatus(LPCTSTR szText);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnNetconfig();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedOk();
};
