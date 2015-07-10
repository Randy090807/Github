// Pane1.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "Pane1.h"
#include "afxdialogex.h"


// CPane1 dialog

IMPLEMENT_DYNAMIC(CPane1, CDialogEx)

CPane1::CPane1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPane1::IDD, pParent)
	, m_szOffset(_T("0.01"))
	, m_szShotcut(_T("F1"))
{

}

CPane1::~CPane1()
{
}

void CPane1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_wndList);
	DDX_Control(pDX, IDC_COMBO1, m_cbDirect);
	DDX_Control(pDX, IDC_COMBO4, m_cbReSend);
	DDX_Control(pDX, IDC_COMBO2, m_cbPrice);
	DDX_Control(pDX, IDC_COMBO3, m_cbCount);
	DDX_Text(pDX, IDC_EDIT1, m_szOffset);
	DDX_Text(pDX, IDC_EDIT2, m_szShotcut);
}


BEGIN_MESSAGE_MAP(CPane1, CDialogEx)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CPane1::OnLvnItemchangedList)
END_MESSAGE_MAP()


// CPane1 message handlers



void CPane1::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


BOOL CPane1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_wndList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_wndList.InsertColumn(0L, _T("快捷键"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(1L, _T("方向"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(2L, _T("价位"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(3L, _T("价格偏移值"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(0L, _T("默认股数"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(0L, _T("重发"), LVCFMT_CENTER, 100);

	m_wndList.InsertItem(0L, _T("F1"));
	m_wndList.SetItemText(0L, 1L, _T("担保品买入"));
	m_wndList.SetItemText(0L, 2L, _T("Bid"));
	m_wndList.SetItemText(0L, 3L, _T("0"));
	m_wndList.SetItemText(0L, 4L, _T("Default"));
	m_wndList.SetItemText(0L, 5L, _T("不改变"));
	
	m_wndList.InsertItem(1L, _T("F2"));
	m_wndList.SetItemText(1L, 1L, _T("融券卖出"));
	m_wndList.SetItemText(1L, 2L, _T("Ask"));
	m_wndList.SetItemText(1L, 3L, _T("0"));
	m_wndList.SetItemText(1L, 4L, _T("Default"));
	m_wndList.SetItemText(1L, 5L, _T("不改变"));

	m_wndList.InsertItem(2L, _T("F3"));
	m_wndList.SetItemText(2L, 1L, _T("预约券卖出"));
	m_wndList.SetItemText(2L, 2L, _T("Ask"));
	m_wndList.SetItemText(2L, 3L, _T("0"));
	m_wndList.SetItemText(2L, 4L, _T("Default"));
	m_wndList.SetItemText(2L, 5L, _T("不改变"));

	m_wndList.InsertItem(3L, _T("F4"));
	m_wndList.SetItemText(3L, 1L, _T("涨停券卖出"));
	m_wndList.SetItemText(3L, 2L, _T("涨停价"));
	m_wndList.SetItemText(3L, 3L, _T("0"));
	m_wndList.SetItemText(3L, 4L, _T("Default"));
	m_wndList.SetItemText(3L, 5L, _T("不改变"));

	m_cbDirect.SetCurSel(0);
	m_cbReSend.SetCurSel(0);
	m_cbPrice.SetCurSel(0);
	m_cbCount.SetCurSel(0);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
