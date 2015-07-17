#pragma once


// CTradeDlg dialog
#include "../Public/OperEdit.h"

class CTradeInfo
{
public:
	CTradeInfo(){}
};

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
	void Show(BOOL bShow = TRUE, CTradeInfo* pTradeInfo=NULL);
	void SetInfo(CTradeInfo* pTradeInfo);
	double m_dbPrice;
	UINT m_nCount;
	CString m_szTip;

	COperEdit m_editPrice;
	CEdit m_editCount;

protected:
	CTradeInfo*	m_pTradeInfo;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	
	afx_msg void OnPaint();
};
