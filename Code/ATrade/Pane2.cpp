// Pane2.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "Pane2.h"
#include "afxdialogex.h"
#include "../Public/Config.h"

// CPane2 dialog

IMPLEMENT_DYNAMIC(CPane2, CDialogEx)

CPane2::CPane2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPane2::IDD, pParent)
	, m_dbUpDown( CConfig::Inst()->Level2Info()->dbUDSacle)
	, m_dbLeftRight(CConfig::Inst()->Level2Info()->dbLRSacle)
{

}

CPane2::~CPane2()
{
}

void CPane2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDOWN, m_dbUpDown);
	DDX_Text(pDX, IDC_EDIT_LEFTRIGHT, m_dbLeftRight);
	DDX_Control(pDX, IDC_CLRBTN_16, m_ColorPicker16);
	DDX_Control(pDX, IDC_CLRBTN_27, m_ColorPicker27);
	DDX_Control(pDX, IDC_CLRBTN_38, m_ColorPicker38);
	DDX_Control(pDX, IDC_CLRBTN_49, m_ColorPicker49);
	DDX_Control(pDX, IDC_CLRBTN_510, m_ColorPicker510);
	DDX_Control(pDX, IDC_CLRBTN_UP, m_ColorPickerUp);
	DDX_Control(pDX, IDC_CLRBTN_DOWN, m_ColorPickerDown);
}


BEGIN_MESSAGE_MAP(CPane2, CDialogEx)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_MODIFY, &CPane2::OnBnClickedBtnModify)
END_MESSAGE_MAP()


// CPane2 message handlers


BOOL CPane2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ColorPicker16.SetColor(CConfig::Inst()->Level2Info()->clrBid16);
	m_ColorPicker16.SetColumnsNumber(10);

	m_ColorPicker27.SetColor(CConfig::Inst()->Level2Info()->clrBid27);
	m_ColorPicker27.SetColumnsNumber(10);

	m_ColorPicker38.SetColor(CConfig::Inst()->Level2Info()->clrBid38);
	m_ColorPicker38.SetColumnsNumber(10);

	m_ColorPicker49.SetColor(CConfig::Inst()->Level2Info()->clrBid49);
	m_ColorPicker49.SetColumnsNumber(10);

	m_ColorPicker510.SetColor(CConfig::Inst()->Level2Info()->clrBid510);
	m_ColorPicker510.SetColumnsNumber(10);

	m_ColorPickerUp.SetColor(CConfig::Inst()->Level2Info()->clrRise);
	m_ColorPickerUp.SetColumnsNumber(10);

	m_ColorPickerDown.SetColor(CConfig::Inst()->Level2Info()->clrFall);
	m_ColorPickerDown.SetColumnsNumber(10);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPane2::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	UpdateData();

	CConfig::Inst()->Level2Info()->clrBid16 = m_ColorPicker16.GetColor();
	CConfig::Inst()->Level2Info()->clrBid27 = m_ColorPicker27.GetColor();
	CConfig::Inst()->Level2Info()->clrBid38 = m_ColorPicker38.GetColor();
	CConfig::Inst()->Level2Info()->clrBid49 = m_ColorPicker49.GetColor();
	CConfig::Inst()->Level2Info()->clrBid510 = m_ColorPicker510.GetColor();

	CConfig::Inst()->Level2Info()->clrRise = m_ColorPickerUp.GetColor();
	CConfig::Inst()->Level2Info()->clrFall = m_ColorPickerDown.GetColor();

	
}


void CPane2::OnBnClickedBtnModify()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CConfig::Inst()->Level2Info()->dbLRSacle = m_dbLeftRight;
	CConfig::Inst()->Level2Info()->dbUDSacle = m_dbUpDown;
}
