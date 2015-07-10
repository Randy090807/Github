#pragma once
#include "afxcmn.h"


#include "Pane1.h"
#include "Pane2.h"
#include "Pane3.h"
#include "Pane4.h"
#include "Pane5.h"

// CConfigDlg dialog

class CConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigDlg();

// Dialog Data
	enum { IDD = IDD_CONFIG };

protected:

	CPane1	m_Pane1;
	CPane2	m_Pane2;
	CPane3	m_Pane3;
	CPane4	m_Pane4;
	CPane5	m_Pane5;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_wndTab;
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
};
