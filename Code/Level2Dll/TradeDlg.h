#pragma once


// CTradeDlg dialog
#include "../Public/OperEdit.h"

class CQTTradeInfo
{
public:
	CQTTradeInfo(){}
	int			OrderType;
	double		BidPrice;
	double		AskPrice;
	double		TopLimitPrice;
	double		DownLimitPrice;
	double		OpenPrice;
	int			PriceType;
	int			Volume;
	int			DefaultVolume;
	double		PriceOffset;
	BOOL		bMaxSell;
	CString		StockID;
};

class CTradeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTradeDlg)
public:
	CTradeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTradeDlg();

// Dialog Data
//	enum { IDD = IDD_TRADE };
	
	BOOL Create(CWnd* pParentWnd  = NULL );
	void SetInfo(CQTTradeInfo* pTradeInfo);
	double m_dbPrice;
	UINT m_nCount;
	CString m_szTip;

	COperEdit m_editPrice;
	CEdit m_editCount;

protected:
	void RegisterHotKey();
	void UnRegisterHotKey();
	void FillData();
	CQTTradeInfo*	m_pTradeInfo;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnPaint();
	
	virtual void OnCancel();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnDestroy();
};
