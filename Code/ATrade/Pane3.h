#pragma once
#include "afxcolorbutton.h"
#include "afxcmn.h"


// CPane3 dialog

class CPane3 : public CDialogEx
{
	DECLARE_DYNAMIC(CPane3)

public:
	CPane3(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPane3();

// Dialog Data
	enum { IDD = IDD_PANE3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CMFCColorButton m_ColorPicker;
	CListCtrl m_wndList;
	CString m_szCode;
	UINT	m_nCount;
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
