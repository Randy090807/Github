// Pane4.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "Pane4.h"
#include "afxdialogex.h"
#include "../Public/Config.h"

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
	DDX_Control(pDX, IDC_HOTKEY3, m_hotkeyGaiDan);
	DDX_Control(pDX, IDC_HOTKEY2, m_hotkeyPiLiangCeDan);
	DDX_Control(pDX, IDC_HOTKEY1, m_hotkeyCeDan);
}


BEGIN_MESSAGE_MAP(CPane4, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_MODIFY1, &CPane4::OnBnClickedBtnModify1)
	ON_BN_CLICKED(IDC_BTN_MODIFY2, &CPane4::OnBnClickedBtnModify2)
	ON_BN_CLICKED(IDC_BTN_MODIFY3, &CPane4::OnBnClickedBtnModify3)
END_MESSAGE_MAP()


// CPane4 message handlers


BOOL CPane4::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_DELETE)
	{
		if (&m_hotkeyCeDan == GetFocus())
		{
			m_hotkeyCeDan.SetHotKey(pMsg->wParam, 0);
		}
		else if (&m_hotkeyPiLiangCeDan == GetFocus())
		{
			m_hotkeyPiLiangCeDan.SetHotKey(pMsg->wParam, 0);
		}
		if (&m_hotkeyGaiDan == GetFocus())
		{
			m_hotkeyGaiDan.SetHotKey(pMsg->wParam, 0);
		}
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CPane4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	DWORD hotkey = CConfig::Inst()->RecordInfo()->HKCancelSingle;
	m_hotkeyCeDan.SetHotKey(LOBYTE(hotkey), HIBYTE(hotkey));

	hotkey = CConfig::Inst()->RecordInfo()->HKCancelBat;
	m_hotkeyPiLiangCeDan.SetHotKey(LOBYTE(hotkey), HIBYTE(hotkey));

	hotkey = CConfig::Inst()->RecordInfo()->HKModify;
	m_hotkeyGaiDan.SetHotKey(LOBYTE(hotkey), HIBYTE(hotkey));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPane4::OnBnClickedBtnModify1()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if (m_hotkeyCeDan.GetHotKey() == m_hotkeyPiLiangCeDan.GetHotKey()
		|| m_hotkeyCeDan.GetHotKey() == m_hotkeyGaiDan.GetHotKey())
	{
		MessageBox(_T("ÈÈ¼üÉèÖÃ³åÍ»"), _T("´íÎó"), MB_OK | MB_ICONERROR);
		return;
	}

	CConfig::Inst()->RecordInfo()->HKCancelSingle = m_hotkeyCeDan.GetHotKey();
}


void CPane4::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

//	CDialogEx::OnOK();
}


void CPane4::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	
//	CDialogEx::OnCancel();
}


void CPane4::OnBnClickedBtnModify2()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_hotkeyPiLiangCeDan.GetHotKey() == m_hotkeyCeDan.GetHotKey()
		|| m_hotkeyPiLiangCeDan.GetHotKey() == m_hotkeyGaiDan.GetHotKey())
	{
		MessageBox(_T("ÈÈ¼üÉèÖÃ³åÍ»"), _T("´íÎó"), MB_OK | MB_ICONERROR);
		return;
	}

	CConfig::Inst()->RecordInfo()->HKCancelBat = m_hotkeyPiLiangCeDan.GetHotKey();
}


void CPane4::OnBnClickedBtnModify3()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if (m_hotkeyGaiDan.GetHotKey() == m_hotkeyCeDan.GetHotKey()
		|| m_hotkeyGaiDan.GetHotKey() == m_hotkeyPiLiangCeDan.GetHotKey())
	{
		MessageBox(_T("ÈÈ¼üÉèÖÃ³åÍ»"), _T("´íÎó"), MB_OK | MB_ICONERROR);
		return;
	}

	CConfig::Inst()->RecordInfo()->HKModify = m_hotkeyGaiDan.GetHotKey();
}
