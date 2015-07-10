// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "NetConfigDlg.h"

// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_NETCONFIG, &CLoginDlg::OnBnClickedBtnNetconfig)
END_MESSAGE_MAP()


// CLoginDlg message handlers


void CLoginDlg::OnBnClickedBtnNetconfig()
{
	// TODO: Add your control notification handler code here
	CNetConfigDlg dlg;
	dlg.DoModal();
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
