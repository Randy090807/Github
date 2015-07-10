#pragma once



// CView2 form view

class CView2 : public CFormView
{
	DECLARE_DYNCREATE(CView2)

protected:
	CView2();           // protected constructor used by dynamic creation
	virtual ~CView2();

public:
//	enum { IDD = IDD_VIEW2 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	CXTPReportControl	m_wndReport;
	void LoadData();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
};


