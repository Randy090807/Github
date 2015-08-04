// Pane5.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "Pane5.h"
#include "afxdialogex.h"
#include "../Public/MsgDefine.h"
#include "../Public/Config.h"

// CPane5 dialog

IMPLEMENT_DYNAMIC(CPane5, CDialogEx)

CPane5::CPane5(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPane5::IDD, pParent)
	, m_szOld(_T(""))
	, m_szNew(_T(""))
	, m_szNew2(_T(""))
{

}

CPane5::~CPane5()
{
}

void CPane5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PWD1, m_szOld);
	DDX_Text(pDX, IDC_EDIT_PWD2, m_szNew);
	DDX_Text(pDX, IDC_EDIT_PWD3, m_szNew2);
}


BEGIN_MESSAGE_MAP(CPane5, CDialogEx)
	ON_MESSAGE(UM_SRV_DATA_NOTIFY, &CPane5::OnMsgSrvDataNofity)
	ON_MESSAGE(UM_SRV_DATA_REPORT, &CPane5::OnMsgSrvDataReport)
	ON_BN_CLICKED(IDC_BTN_COMFIRM, &CPane5::OnBnClickedBtnComfirm)
END_MESSAGE_MAP()


// CPane5 message handlers

LRESULT CPane5::OnMsgSrvDataReport(WPARAM wparam, LPARAM lparam)
{
	return 0;
}

LRESULT CPane5::OnMsgSrvDataNofity(WPARAM wparam, LPARAM lparam)
{
	CChangePasswordResultMsg* pMsg = (CChangePasswordResultMsg*)wparam;
	if ( pMsg->Error == 0)
	{
		MessageBox(_T("ÃÜÂëÐÞ¸Ä³É¹¦"), _T("ÌáÊ¾"), MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		MessageBox( pMsg->ErrMsg, _T("´íÎó"), MB_OK | MB_ICONINFORMATION);
	}
	delete  pMsg;
	return 0;
}

void CPane5::OnBnClickedBtnComfirm()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	if ( m_szOld.IsEmpty() || m_szNew.IsEmpty() || m_szNew2.IsEmpty())
	{
		MessageBox(_T("ÃÜÂë²»ÄÜÎª¿Õ£¬ÇëÌîÐ´ÐÅÏ¢ÍêÕû."), _T("´íÎó"), MB_OK|MB_ICONERROR);
		return;
	}

	if ( m_szNew2 != m_szNew)
	{
		MessageBox(_T("Á½´ÎÃÜÂëÊäÈë²»Ò»ÖÂ."), _T("´íÎó"), MB_OK | MB_ICONERROR);
		return;
	}

// 	if ( m_szOld != CConfig::Inst()->LogInfo()->Password)
// 	{
// 		MessageBox(_T("¾ÉÃÜÂë´íÎó."), _T("´íÎó"), MB_OK | MB_ICONERROR);
// 		return;
// 	}

	CChangePasswordMsg* pMsg = new CChangePasswordMsg();
	pMsg->Password == m_szOld;
	pMsg->NewPassword == m_szNew;

	::PostMessage(GetParent()->GetParent()->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);
}

BOOL CPane5::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}