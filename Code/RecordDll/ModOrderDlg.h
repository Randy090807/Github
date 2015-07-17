#pragma once

#include "Resource.h"
// CModOrderDlg dialog

class CModOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModOrderDlg)

public:
	CModOrderDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModOrderDlg();

// Dialog Data
	enum { IDD = IDD_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_dbPrice;
	UINT m_nCount;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
};
