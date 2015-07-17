#pragma once
#include "afxwin.h"


// CNetConfigDlg dialog

class CNetConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNetConfigDlg)

public:
	CNetConfigDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNetConfigDlg();

// Dialog Data
	enum { IDD = IDD_NET_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_cbSvrIP;
	CComboBox m_cbSvrPort;
	CComboBox m_cbPriceIP;
	CComboBox m_cbPricePort;
	afx_msg void OnBnClickedOk();
};
