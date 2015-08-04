// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "NetConfigDlg.h"
#include "../Public/Config.h"
#include "SvrSocket.h"
#include "PriceSocket.h"
#include "../Public/MsgDefine.h"
#include "../Public/TradeInfo.h"
#include "../Public/MsgBuilder.h"

extern CSvrSocket	g_SockSvr;
extern CPriceSocket	g_SockPrice;

extern BOOL g_StatusSrv;
extern BOOL g_StatusPrice;
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
	, m_szStatus(_T("���½"))
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
	ON_MESSAGE(UM_SRV_DATA_NOTIFY, &CLoginDlg::OnMsgSrvDataNofity)
	ON_MESSAGE(UM_SRV_DATA_NOTIFY2, &CLoginDlg::OnMsgSrvDataNofity2)
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

//	g_SockSvr.Create();
	g_SockSvr.SetMsgReciver(this);
	g_SockPrice.SetMsgReciver(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CLoginDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if (!Verify())
		return;

	UpdateStatus(_T("��¼��......"));
	
	CConfig::Inst()->LogInfo()->Admin = m_szAdmin;
	CConfig::Inst()->LogInfo()->Operator = m_szOperator;
	CConfig::Inst()->LogInfo()->AssetsUnit = m_szAssetsUnit;
	CConfig::Inst()->LogInfo()->TradeUnit = m_szTradeUnit;
	CConfig::Inst()->LogInfo()->IsSavePwd = m_bSavePwd;
	CConfig::Inst()->LogInfo()->Password = m_szPassword;	

	//��������֤��Ϣ
	g_SockSvr.Create();
	g_SockSvr.Connect(CConfig::Inst()->LogInfo()->GetSrvIP(), _ttoi(CConfig::Inst()->LogInfo()->GetSrvPort()));
	UpdateStatus(_T("�������ӷ�����......"));
	
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_NETCONFIG)->EnableWindow(FALSE);

//	CDialogEx::OnOK();
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
		m_wndTip.Show(_T("����Ա�˺Ų���Ϊ��"), IDC_EDIT1);
		return FALSE;
	}

	m_szOperator.Trim();
	if (m_szOperator.IsEmpty())
	{
		m_wndTip.Show(_T("����Ա�˺Ų���Ϊ��"), IDC_EDIT3);
		return FALSE;
	}

	m_szAssetsUnit.Trim();
	if (m_szAssetsUnit.IsEmpty())
	{
		m_wndTip.Show(_T("�ʲ���Ԫ��Ϣ����Ϊ��"), IDC_EDIT2);
		return FALSE;
	}

	m_szTradeUnit.Trim();
	if (m_szTradeUnit.IsEmpty())
	{
		m_wndTip.Show(_T("���׵�Ԫ��Ϣ����Ϊ��"), IDC_EDIT4);
		return FALSE;
	}

	m_szPassword.Trim();
	if (m_szPassword.IsEmpty())
	{
		m_wndTip.Show(_T("���벻��Ϊ��"), IDC_EDIT5);
		return FALSE;
	}

	if ( CConfig::Inst()->LogInfo()->GetSrvIP().IsEmpty()
		|| CConfig::Inst()->LogInfo()->GetSrvPort().IsEmpty()
		|| CConfig::Inst()->LogInfo()->GetPriceIP().IsEmpty()
		|| CConfig::Inst()->LogInfo()->GetPricePort().IsEmpty())
	{
		m_wndTip.Show(_T("����������Ϣ������"), IDC_BTN_NETCONFIG);
		return FALSE;
	}

	return TRUE;
}


LRESULT CLoginDlg::OnMsgSrvDataNofity(WPARAM wparam, LPARAM lparam)
{
	CBaseMsg* pBaseMsg = (CBaseMsg*)wparam;
	if (pBaseMsg->Header.type == ID_CUSTOM_SOCK_CONN_RESULT)
	{
		CLoginResultMsg* pMsg = (CLoginResultMsg*)pBaseMsg;
		if ( pMsg->Error == 0)
		{
			UpdateStatus(_T("�������ӳɹ�����¼��......"));
			CLoginMsg Msg;
			Msg.UserID = m_szAdmin;
			Msg.Password = m_szPassword;
			g_SockSvr.Send( &Msg);
		}
		else
		{
			g_SockSvr.Close();// ShutDown(CAsyncSocket::both);
			UpdateStatus(_T("�������Ӵ���������������......"));

			GetDlgItem(IDOK)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_NETCONFIG)->EnableWindow(TRUE);
		}
	}
	else if (pBaseMsg->Header.type == ID_LOGIN_RESULT)
	{
		CLoginResultMsg* pMsg = (CLoginResultMsg*)pBaseMsg;
		if (pMsg->Error == 0)
		{
			UpdateStatus(_T("�û���������֤�ɹ������ڵ�¼���������......"));

			g_SockPrice.Create();
			g_SockPrice.Connect(CConfig::Inst()->LogInfo()->GetPriceIP(), _ttoi(CConfig::Inst()->LogInfo()->GetPricePort()));
		}
		else
		{
			g_SockSvr.Close();// ShutDown(CAsyncSocket::both);
			UpdateStatus(pMsg->ErrMsg);

			GetDlgItem(IDOK)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_NETCONFIG)->EnableWindow(TRUE);
		}		
	}
	else if (pBaseMsg->Header.type == ID_CUSTOM_PRICE_SOCK_CONN_RESULT)
	{
		CLoginResultMsg* pMsg = (CLoginResultMsg*)pBaseMsg;
		if (pMsg->Error == 0)
		{
			UpdateStatus(_T("�����������¼�ɹ������ڸ��·��������......"));

			char* msg = 0;
			int len = 0;
			CMsgBuilder::BuildStockCode(msg, len);
			g_SockPrice.Send( msg, len);
			delete msg;
		}
		else
		{
			g_SockPrice.Close();// ShutDown(CAsyncSocket::both);
			g_SockSvr.Close();
			UpdateStatus(_T("����������������Ӵ���������������......"));

			GetDlgItem(IDOK)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_NETCONFIG)->EnableWindow(TRUE);

		}
	}
	

	delete pBaseMsg;
	return 0;
}

LRESULT CLoginDlg::OnMsgSrvDataNofity2(WPARAM wparam, LPARAM lparam)
{
	MsgHeader* Header = (MsgHeader*)wparam;
	if (Header->type == ID_GET_STOCK_CODE_TABLE_RESULT)
	{
		UpdateStatus(_T("��¼�ɹ������ڽ���ϵͳ......"));
		CConfig::Inst()->StockInfo()->Load((char*)wparam, (int)lparam);
		delete (char*)wparam;

		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_NETCONFIG)->EnableWindow(TRUE);

		g_StatusSrv = TRUE;
		g_StatusPrice = TRUE;

		CDialogEx::OnOK();
	}
	return 0;
}
