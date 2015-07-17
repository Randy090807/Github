// ModOrderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ModOrderDlg.h"
#include "afxdialogex.h"


// CModOrderDlg dialog

IMPLEMENT_DYNAMIC(CModOrderDlg, CDialogEx)

CModOrderDlg::CModOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModOrderDlg::IDD, pParent)
	, m_dbPrice(23.67)
	, m_nCount(100)
{

}

CModOrderDlg::~CModOrderDlg()
{
}

void CModOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_dbPrice);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_nCount);
}


BEGIN_MESSAGE_MAP(CModOrderDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CModOrderDlg message handlers


BOOL CModOrderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetWindowText(_T("600009 - ÆÖ·¢ÒøÐÐ"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


HBRUSH CModOrderDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if ( pWnd->GetDlgCtrlID() == IDC_STATIC_INFO)
	{
		pDC->SetBkColor(RGB(0, 255, 0));
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CModOrderDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}
