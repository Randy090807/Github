#pragma once
#include "afxwin.h"
#include "RTButton.h"
#include <vector>
using namespace std;

// CMainDlg dialog

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMainDlg();

// Dialog Data
	enum { IDD = IDD_MAINDLG };

	vector<CWnd*>	m_Lev2Wnds;
	int				m_nLev2Idx;
protected:
	CRTButton m_btnLevel2;
	CRTButton m_btnConfig;
	CRTButton m_btnRecord;
	CRTButton m_btnSpace;
	CRTButton m_btnExit;
	Gdiplus::Image*	m_pImage;
	Gdiplus::Image	m_pImageLogo;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnLevel2();
	afx_msg void OnBnClickedBtnRecord();
	afx_msg void OnBnClickedBtnSpace();
	afx_msg void OnBnClickedBtnConfig();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMsgLevel2WndClose(WPARAM wparam, LPARAM lparam);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
};
