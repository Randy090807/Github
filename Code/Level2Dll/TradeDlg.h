#pragma once


// CTradeDlg dialog
#include "../Public/OperEdit.h"
class CTradeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTradeDlg)
public:
	CTradeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTradeDlg();

// Dialog Data
//	enum { IDD = IDD_TRADE };
	
	void SetMode(int i);
	BOOL Create(CWnd* pParentWnd  = NULL );
	void Show(BOOL bShow = TRUE);

	double m_dbPrice;
	UINT m_nCount;
	CString m_szTip;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	COperEdit m_editPrice;
	COperEdit m_editCount;
};
