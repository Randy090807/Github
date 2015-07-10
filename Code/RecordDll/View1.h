#pragma once



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


