// NetConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "NetConfigDlg.h"
#include "afxdialogex.h"


// CNetConfigDlg dialog

IMPLEMENT_DYNAMIC(CNetConfigDlg, CDialogEx)

CNetConfigDlg::CNetConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNetConfigDlg::IDD, pParent)
{

}

CNetConfigDlg::~CNetConfigDlg()
{
}

void CNetConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNetConfigDlg, CDialogEx)
END_MESSAGE_MAP()


// CNetConfigDlg message handlers


BOOL CNetConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
