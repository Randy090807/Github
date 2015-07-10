// Pane3.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "Pane3.h"
#include "afxdialogex.h"


// CPane3 dialog

IMPLEMENT_DYNAMIC(CPane3, CDialogEx)

CPane3::CPane3(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPane3::IDD, pParent)
	, m_szCode(_T("000001"))
	, m_szCount(_T("10000"))
{

}

CPane3::~CPane3()
{
}

void CPane3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLRBTN_COLOR, m_ColorPicker);
	DDX_Control(pDX, IDC_LIST, m_wndList);
	DDX_Text(pDX, IDC_EDIT_CODE, m_szCode);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_szCount);
}


BEGIN_MESSAGE_MAP(CPane3, CDialogEx)
END_MESSAGE_MAP()


// CPane3 message handlers


BOOL CPane3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ColorPicker.SetColor(RGB(0, 0, 255));
	m_ColorPicker.SetColumnsNumber(10);

	m_wndList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_wndList.InsertColumn(0L, _T("股票代码"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(1L, _T("股票名称"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(2L, _T("大单数量"), LVCFMT_CENTER, 400);
	
	m_wndList.InsertItem(0L, _T("000001"));
	m_wndList.SetItemText(0L, 1L, _T("上海机场"));
	m_wndList.SetItemText(0L, 2L, _T("10000"));

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
