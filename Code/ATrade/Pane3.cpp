// Pane3.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "Pane3.h"
#include "afxdialogex.h"
#include "../Public/Config.h"

// CPane3 dialog

IMPLEMENT_DYNAMIC(CPane3, CDialogEx)

CPane3::CPane3(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPane3::IDD, pParent)
	, m_szCode(_T(""))
	, m_nCount(1000)
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
	DDX_Text(pDX, IDC_EDIT_COUNT, m_nCount);
}


BEGIN_MESSAGE_MAP(CPane3, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &CPane3::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CPane3::OnBnClickedBtnDelete)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPane3 message handlers


BOOL CPane3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ColorPicker.SetColor(CConfig::Inst()->RecordInfo()->clrBOColor);
	m_ColorPicker.SetColumnsNumber(10);

	m_wndList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_wndList.InsertColumn(0L, _T("股票代码"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(1L, _T("股票名称"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(2L, _T("大单数量"), LVCFMT_CENTER, 400);
	

	for (int i = 0; i < CConfig::Inst()->RecordInfo()->BOSize(); i++)
	{
		CRecordInfo::CBigOrderInfo* pBOI = CConfig::Inst()->RecordInfo()->Item(i);
		CString szText;
		m_wndList.InsertItem(i, pBOI->code);
		m_wndList.SetItemText(i, 1L, CConfig::Inst()->StockInfo()->CodeToName( pBOI->code));
		szText.Format(_T("%d"), pBOI->count);
		m_wndList.SetItemText(i, 2L, szText);
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPane3::OnBnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_szCode.IsEmpty())
	{
		return;
	}

	CRecordInfo::CBigOrderInfo* pBOI = new CRecordInfo::CBigOrderInfo();
	pBOI->code = m_szCode;
	pBOI->count = m_nCount;
	CConfig::Inst()->RecordInfo()->Add(pBOI);

	CString szText;
	int idx = m_wndList.InsertItem(m_wndList.GetItemCount(), pBOI->code);
	m_wndList.SetItemText(idx, 1L, CConfig::Inst()->StockInfo()->CodeToName(pBOI->code));
	szText.Format(_T("%d"), pBOI->count);
	m_wndList.SetItemText(idx, 2L, szText);

}


void CPane3::OnBnClickedBtnDelete()
{
	// TODO: Add your control notification handler code here
	int idx = m_wndList.GetNextItem(-1, LVIS_SELECTED);
	if ( idx >= 0)
	{
		CConfig::Inst()->RecordInfo()->Delete(idx);
		m_wndList.DeleteItem(idx);
	}
}


void CPane3::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	UpdateData();

	CConfig::Inst()->RecordInfo()->clrBOColor = m_ColorPicker.GetColor();
	
}


BOOL CPane3::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
