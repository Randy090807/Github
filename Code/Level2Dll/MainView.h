#pragma once
#include "afxwin.h"

#include "TradeDlg.h"
#include "../Public/CDStatusBar.h"
// CMainView form view
struct MarketData;
struct Trasaction;
class AFX_EXT_CLASS CMainView : public CFormView
{
	friend class CLevel2Dlg;
	DECLARE_DYNCREATE(CMainView)

protected:
	CMainView();           // protected constructor used by dynamic creation
	virtual ~CMainView();

public:
//	enum { IDD = IDD_MAINVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	void ShowTrade(int iMode);
	void CancelOrder();
protected:
	void LoadStockData(LPCTSTR StockId);
//	CTradeDlg	m_dlgTrade;

	CCDStatusBar			m_StatusBar;


	UINT	m_nOrderRef;

	UINT	m_nDefault;
	CString m_szTopLImitPrice;
	CString m_szBottomLImitPrice;
	CString m_szOpenPrice;
	CString m_szIncrease;
	CString m_szMatch;
	CString m_szBP;
	UINT m_nAvailed;
	UINT m_nBooking;
	BOOL m_bMaxSell;
	
	CComboBox m_cbCode;
	CXTPReportControl	m_wndReport;
	CXTPReportControl	m_wndReport2;

	CString				m_szLastCtockID;

protected:
	void LoadData();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void ClearData();
	void UpdataPrice(MarketData* marketdata);
	void UpdataTrancation(Trasaction* trasaction);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnCbnSelchangeCbCode();
	afx_msg void OnComBoEditComplete();
	afx_msg LRESULT OnConfigRefreshNotify(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgSrvDataNofity(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgSrvDataReport(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgSrvDataNofity2(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgSrvDataReport2(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgInitComplete(WPARAM wparam, LPARAM lparam);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
};


