#pragma once
#include "BottomPane.h"

// CMainView view
#include "StockCountDlg.h"

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
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnTabSelectChange(LPNMHDR lpNMHDR, LRESULT* pResult);
};


