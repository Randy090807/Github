#pragma once


// CSpaceDlg dialog
class CMainView;
class AFX_EXT_CLASS CSpaceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSpaceDlg)

public:
	CSpaceDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSpaceDlg();

// Dialog Data
	/*enum { IDD = IDD_SPACE };*/
	BOOL Create(CWnd* pParentWnd);
protected:
	CMainView*	m_pView;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();

};
