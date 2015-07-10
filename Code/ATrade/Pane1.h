#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CPane1 dialog

class CPane1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPane1)

public:
	CPane1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPane1();

// Dialog Data
	enum { IDD = IDD_PANE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_wndList;
	virtual BOOL OnInitDialog();
	CComboBox m_cbDirect;
	CComboBox m_cbReSend;
	CComboBox m_cbPrice;
	CComboBox m_cbCount;
	CString m_szOffset;
	CString m_szShotcut;
};
