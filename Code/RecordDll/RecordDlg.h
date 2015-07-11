#pragma once


// CRecordDlg dialog

class AFX_EXT_CLASS CRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRecordDlg)

public:
	CRecordDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRecordDlg();

// Dialog Data
//	enum { IDD = IDD_RECORD };

	BOOL Create(CWnd* pParentWnd = NULL);

protected:
	CSplitterWnd	m_wndSplitter;
	CFrameWnd*		m_pMyFrame;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};
