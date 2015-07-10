#pragma once


// CStockCountDlg dialog

class CStockCountDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStockCountDlg)

public:
	CStockCountDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStockCountDlg();

// Dialog Data
//	enum { IDD = IDD_STOCKCOUNTDLG };

protected:

	CXTPReportControl	m_wndReport;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
