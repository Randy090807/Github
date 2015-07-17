// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "NetConfigDlg.h"
#include "../Public/Config.h"

// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_szAdmin(CConfig::Inst()->LogInfo()->Admin)
	, m_szOperator(CConfig::Inst()->LogInfo()->Operator)
	, m_szAssetsUnit(CConfig::Inst()->LogInfo()->AssetsUnit)
	, m_szTradeUnit(CConfig::Inst()->LogInfo()->TradeUnit)
	, m_szPassword(CConfig::Inst()->LogInfo()->IsSavePwd ? CConfig::Inst()->LogInfo()->Password:_T(""))
	, m_bSavePwd(CConfig::Inst()->LogInfo()->IsSavePwd)
	, m_szStatus(_T("请登陆"))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szAdmin);
	DDX_Text(pDX, IDC_EDIT3, m_szOperator);
	DDX_Text(pDX, IDC_EDIT2, m_szAssetsUnit);
	DDX_Text(pDX, IDC_EDIT4, m_szTradeUnit);
	DDX_Text(pDX, IDC_EDIT5, m_szPassword);
	DDX_Check(pDX, IDC_CHK_MEMERY, m_bSavePwd);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_szStatus);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_NETCONFIG, &CLoginDlg::OnBnClickedBtnNetconfig)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
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
	m_wndTip.Create(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CLoginDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if (!Verify())
		return;

	UpdateStatus(_T("登录中......"));
	
	CConfig::Inst()->LogInfo()->Admin = m_szAdmin;
	CConfig::Inst()->LogInfo()->Operator = m_szOperator;
	CConfig::Inst()->LogInfo()->AssetsUnit = m_szAssetsUnit;
	CConfig::Inst()->LogInfo()->TradeUnit = m_szTradeUnit;
	CConfig::Inst()->LogInfo()->IsSavePwd = m_bSavePwd;
	CConfig::Inst()->LogInfo()->Password = m_szPassword;	

	//服务器验证信息

	CDialogEx::OnOK();
}

void CLoginDlg::UpdateStatus(LPCTSTR szText)
{
	m_szStatus = szText;
	UpdateData(FALSE);
}

BOOL CLoginDlg::Verify()
{
	m_szAdmin.Trim();
	if ( m_szAdmin.IsEmpty())
	{
		m_wndTip.Show(_T("管理员账号不能为空"), IDC_EDIT1);
		return FALSE;
	}

	m_szOperator.Trim();
	if (m_szOperator.IsEmpty())
	{
		m_wndTip.Show(_T("操作员账号不能为空"), IDC_EDIT3);
		return FALSE;
	}

	m_szAssetsUnit.Trim();
	if (m_szAssetsUnit.IsEmpty())
	{
		m_wndTip.Show(_T("资产单元信息不能为空"), IDC_EDIT2);
		return FALSE;
	}

	m_szTradeUnit.Trim();
	if (m_szTradeUnit.IsEmpty())
	{
		m_wndTip.Show(_T("交易单元信息不能为空"), IDC_EDIT4);
		return FALSE;
	}

	m_szPassword.Trim();
	if (m_szPassword.IsEmpty())
	{
		m_wndTip.Show(_T("密码不能为空"), IDC_EDIT5);
		return FALSE;
	}

	if ( CConfig::Inst()->LogInfo()->GetSrvIP().IsEmpty()
		|| CConfig::Inst()->LogInfo()->GetSrvPort().IsEmpty()
		|| CConfig::Inst()->LogInfo()->GetPriceIP().IsEmpty()
		|| CConfig::Inst()->LogInfo()->GetPricePort().IsEmpty())
	{
		m_wndTip.Show(_T("网络配置信息不完整"), IDC_BTN_NETCONFIG);
		return FALSE;
	}

	return TRUE;
}
