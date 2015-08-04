#pragma once


// CPane5 dialog

class CPane5 : public CDialogEx
{
	DECLARE_DYNAMIC(CPane5)

public:
	CPane5(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPane5();

// Dialog Data
	enum { IDD = IDD_PANE5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnMsgSrvDataNofity(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMsgSrvDataReport(WPARAM wparam, LPARAM lparam);
public:
	afx_msg void OnBnClickedBtnComfirm();
	BOOL PreTranslateMessage(MSG* pMsg);
	CString m_szOld;
	CString m_szNew;
	CString m_szNew2;
};
