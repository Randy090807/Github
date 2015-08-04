#pragma once
#include "BottomPane.h"

// CMainView view
#include "StockCountDlg.h"
class CPositionInquryResultMsg;
class CTransactionRecordsResultMsg;
class CMainView : public CView
{
	DECLARE_DYNCREATE(CMainView)

protected:
	CMainView();           // protected constructor used by dynamic creation
	virtual ~CMainView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	CMFCTabCtrl	m_wndTab;
	CBottomPane	m_PaneBottom;

	CXTPReportControl	m_wndReportCur;
	CXTPReportControl	m_wndReportInfo;
	CXTPReportControl	m_wndReportKuiYing;

	CStockCountDlg		m_PaneReserve;
	CStockCountDlg		m_PaneLeft;

protected:
	// 更新股票交易信息
	void UpdataTraceInfo(CPositionInquryResultMsg* pMsg);

	// 处理当前仓位信息
	void DealCurSpace(CPositionInquryResultMsg* pMsg);
	
	// 处理个人信息
	void DealInfoSpace(CPositionInquryResultMsg* pMsg);

	// 处理各股票亏盈信息
	void DealStockSpace(CTransactionRecordsResultMsg* pMsg);

	double GetStockPrice(LPCTSTR Stock);

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnMsgSrvDataNofity(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgSrvDataReport(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgInitComplete(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgTabSelectChanged(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgSpaceDealEmpty(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgSpaceDealAll(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgSpaceDealMore(WPARAM wparam, LPARAM lparam);
};


