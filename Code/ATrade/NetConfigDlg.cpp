// NetConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "NetConfigDlg.h"
#include "afxdialogex.h"
#include "../Public/Config.h"

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
	DDX_Control(pDX, IDC_COMBO1, m_cbSvrIP);
	DDX_Control(pDX, IDC_COMBO2, m_cbSvrPort);
	DDX_Control(pDX, IDC_COMBO3, m_cbPriceIP);
	DDX_Control(pDX, IDC_COMBO4, m_cbPricePort);
}


BEGIN_MESSAGE_MAP(CNetConfigDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNetConfigDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNetConfigDlg message handlers


BOOL CNetConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	for (int i = 0; i < CConfig::Inst()->LogInfo()->GetSrvIPSize(); i++)
	{
		m_cbSvrIP.AddString(CConfig::Inst()->LogInfo()->GetSrvIPItem(i));
	}
	m_cbSvrIP.SetWindowText(CConfig::Inst()->LogInfo()->GetSrvIP());

	for (int i = 0; i < CConfig::Inst()->LogInfo()->GetSrvPortSize(); i++)
	{
		m_cbSvrPort.AddString(CConfig::Inst()->LogInfo()->GetSrvPortItem(i));
	}
	m_cbSvrPort.SetWindowText(CConfig::Inst()->LogInfo()->GetSrvPort());

	for (int i = 0; i < CConfig::Inst()->LogInfo()->GetPriceIPSize(); i++)
	{
		m_cbPriceIP.AddString(CConfig::Inst()->LogInfo()->GetPriceIPItem(i));
	}
	m_cbPriceIP.SetWindowText(CConfig::Inst()->LogInfo()->GetPriceIP());

	for (int i = 0; i < CConfig::Inst()->LogInfo()->GetPricePortSize(); i++)
	{
		m_cbPricePort.AddString(CConfig::Inst()->LogInfo()->GetPricePortItem(i));
	}
	m_cbPricePort.SetWindowText(CConfig::Inst()->LogInfo()->GetPricePort());


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CNetConfigDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString szText;
	
	m_cbSvrIP.GetWindowText(szText);
	szText.Trim();
	CConfig::Inst()->LogInfo()->AddSrvIP(szText);

	m_cbSvrPort.GetWindowText(szText);
	szText.Trim();
	CConfig::Inst()->LogInfo()->AddSrvPort(szText);

	m_cbPriceIP.GetWindowText(szText);
	szText.Trim();
	CConfig::Inst()->LogInfo()->AddPriceIP(szText);

	m_cbPricePort.GetWindowText(szText);
	szText.Trim();
	CConfig::Inst()->LogInfo()->AddPricePort(szText);

	CDialogEx::OnOK();
}
