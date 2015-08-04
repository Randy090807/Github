#pragma once


#include "OrderReportCtrl.h"
// CView1 form view

class CView1 : public CFormView
{
	DECLARE_DYNCREATE(CView1)

protected:
	CView1();           // protected constructor used by dynamic creation
	virtual ~CView1();

public:
//	enum { IDD = IDD_VIEW1 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	

	COrderReportCtrl	m_wndReport;
	BOOL m_bCancelTip;
	BOOL m_bWasteResend;
	BOOL m_bErrorResend;
	CWnd* m_pMsgReciver;

	void SetMsgReciver(CWnd* pWnd);
	void Update(COrderInquiryResultMsg* pMsg);

	void LoadData();
	void CancelOrder();
	void ClearOrder();
	void ModifyOrder();
	void SaveOrder();
	void NotifyUpdate();
protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnReportItemRClick(NMHDR* pNotifyStruct, LRESULT *);
	
	afx_msg void OnBnClickedChkCedantishi();
	afx_msg void OnBnClickedChkFeidanchongfa();
	afx_msg void OnBnClickedChkCuodanchongfa();

	afx_msg LRESULT OnConfigRefreshNotify(WPARAM wparam, LPARAM lparam);
	
};


