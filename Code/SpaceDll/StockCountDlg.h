#pragma once


// CStockCountDlg dialog
class CBookingInquiryResultMsg;
class CStockCountDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStockCountDlg)

public:
	CStockCountDlg(int mode,CWnd* pParent = NULL);   // standard constructor
	virtual ~CStockCountDlg();

// Dialog Data
//	enum { IDD = IDD_STOCKCOUNTDLG };
public:
	void Updata(CBookingInquiryResultMsg* pMsg);

protected:
	

	int			m_nMode;	// 0-预约券查询  1-可融券查询
	CXTPReportControl	m_wndReport;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnFreash();
};
