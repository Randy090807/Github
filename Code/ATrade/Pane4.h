#pragma once
#include "afxwin.h"
#include "afxcmn.h"
// CPane4 dialog

class CPane4 : public CDialogEx
{
	DECLARE_DYNAMIC(CPane4)

public:
	CPane4(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPane4();

// Dialog Data
	enum { IDD = IDD_PANE4 };

	CHotKeyCtrl m_hotkeyCeDan;
	CHotKeyCtrl m_hotkeyGaiDan;
	CHotKeyCtrl m_hotkeyPiLiangCeDan;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();	
	afx_msg void OnBnClickedBtnModify1();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBnClickedBtnModify2();
	afx_msg void OnBnClickedBtnModify3();
};
