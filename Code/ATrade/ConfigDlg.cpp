// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"


// CConfigDlg dialog

IMPLEMENT_DYNAMIC(CConfigDlg, CDialogEx)

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigDlg::IDD, pParent)
{

}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_wndTab);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CConfigDlg::OnTcnSelchangeTab)
END_MESSAGE_MAP()


// CConfigDlg message handlers


BOOL CConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_wndTab.InsertItem(0L, _T("Level2交易面板"));
	m_wndTab.InsertItem(1L, _T("Level2方向键及颜色设置"));
	m_wndTab.InsertItem(2L, _T("大单设置"));
	m_wndTab.InsertItem(3L, _T("交易记录快捷键设置"));
	m_wndTab.InsertItem(4L, _T("密码"));

	CRect rc;
	m_wndTab.GetClientRect(rc);
	rc.top += 22;

// 	rc.bottom -= 1;
// 	rc.left += 1;
// 	rc.right -= 1;

	m_Pane1.Create(CPane1::IDD, &m_wndTab);
	m_Pane1.MoveWindow(rc);
	m_Pane1.ShowWindow(SW_SHOW);

	m_Pane2.Create(CPane2::IDD, &m_wndTab);
	m_Pane2.MoveWindow(rc);
	m_Pane2.ShowWindow(SW_HIDE);

	m_Pane3.Create(CPane3::IDD, &m_wndTab);
	m_Pane3.MoveWindow(rc);
	m_Pane3.ShowWindow(SW_HIDE);
	
	m_Pane4.Create(CPane4::IDD, &m_wndTab);
	m_Pane4.MoveWindow(rc);
	m_Pane4.ShowWindow(SW_HIDE);

	m_Pane5.Create(CPane5::IDD, &m_wndTab);
	m_Pane5.MoveWindow(rc);
	m_Pane5.ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


int CConfigDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	return 0;
}


void CConfigDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CConfigDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}


void CConfigDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int iTab = m_wndTab.GetCurSel();
	m_Pane1.ShowWindow(iTab == 0 ? SW_SHOW : SW_HIDE);
	m_Pane2.ShowWindow(iTab == 1 ? SW_SHOW : SW_HIDE);
	m_Pane3.ShowWindow(iTab == 2 ? SW_SHOW : SW_HIDE);
	m_Pane4.ShowWindow(iTab == 3 ? SW_SHOW : SW_HIDE);
	m_Pane5.ShowWindow(iTab == 4 ? SW_SHOW : SW_HIDE);
	*pResult = 0;
}
