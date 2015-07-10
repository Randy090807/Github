// Pane4.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "Pane4.h"
#include "afxdialogex.h"


// CPane4 dialog

IMPLEMENT_DYNAMIC(CPane4, CDialogEx)

CPane4::CPane4(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPane4::IDD, pParent)
{

}

CPane4::~CPane4()
{
}

void CPane4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditCeDan);
	DDX_Control(pDX, IDC_EDIT3, m_EditPiLiangCeDan);
	DDX_Control(pDX, IDC_EDIT2, m_EditGaiDan);
}


BEGIN_MESSAGE_MAP(CPane4, CDialogEx)
END_MESSAGE_MAP()


// CPane4 message handlers


BOOL CPane4::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CPane4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_EditCeDan.SetWindowText(_T("ESC"));
	m_EditPiLiangCeDan.SetWindowText(_T("DEL"));
	m_EditGaiDan.SetWindowText(_T("F10"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
