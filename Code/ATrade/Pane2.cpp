// Pane2.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "Pane2.h"
#include "afxdialogex.h"


// CPane2 dialog

IMPLEMENT_DYNAMIC(CPane2, CDialogEx)

CPane2::CPane2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPane2::IDD, pParent)
	, m_szUpDown(_T("0.01"))
	, m_szLeftRight(_T("0.05"))
{

}

CPane2::~CPane2()
{
}

void CPane2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDOWN, m_szUpDown);
	DDX_Text(pDX, IDC_EDIT_LEFTRIGHT, m_szLeftRight);
	DDX_Control(pDX, IDC_CLRBTN_16, m_ColorPicker16);
	DDX_Control(pDX, IDC_CLRBTN_27, m_ColorPicker27);
	DDX_Control(pDX, IDC_CLRBTN_38, m_ColorPicker38);
	DDX_Control(pDX, IDC_CLRBTN_49, m_ColorPicker49);
	DDX_Control(pDX, IDC_CLRBTN_510, m_ColorPicker510);
	DDX_Control(pDX, IDC_CLRBTN_UP, m_ColorPickerUp);
	DDX_Control(pDX, IDC_CLRBTN_DOWN, m_ColorPickerDown);
}


BEGIN_MESSAGE_MAP(CPane2, CDialogEx)
END_MESSAGE_MAP()


// CPane2 message handlers


BOOL CPane2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ColorPicker16.SetColor(RGB(255, 0, 0));
	m_ColorPicker16.SetColumnsNumber(10);

	m_ColorPicker27.SetColor(RGB(128, 192, 203));
	m_ColorPicker27.SetColumnsNumber(10);

	m_ColorPicker38.SetColor(RGB(255, 218, 185));
	m_ColorPicker38.SetColumnsNumber(10);

	m_ColorPicker49.SetColor(RGB(218, 165, 32));
	m_ColorPicker49.SetColumnsNumber(10);

	m_ColorPicker510.SetColor(RGB(255, 255, 0));
	m_ColorPicker510.SetColumnsNumber(10);

	m_ColorPickerUp.SetColor(RGB(255, 0, 0));
	m_ColorPickerUp.SetColumnsNumber(10);

	m_ColorPickerDown.SetColor(RGB(0, 170, 0));
	m_ColorPickerDown.SetColumnsNumber(10);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
