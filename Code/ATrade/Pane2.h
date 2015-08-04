#pragma once
#include "afxcolorbutton.h"


// CPane2 dialog

class CPane2 : public CDialogEx
{
	DECLARE_DYNAMIC(CPane2)

public:
	CPane2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPane2();

// Dialog Data
	enum { IDD = IDD_PANE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double		m_dbUpDown;
	double		m_dbLeftRight;
	
	virtual BOOL OnInitDialog();
	CMFCColorButton m_ColorPicker16;
	CMFCColorButton m_ColorPicker27;
	CMFCColorButton m_ColorPicker38;
	CMFCColorButton m_ColorPicker49;
	CMFCColorButton m_ColorPicker510;
	CMFCColorButton m_ColorPickerUp;
	CMFCColorButton m_ColorPickerDown;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnModify();
	BOOL PreTranslateMessage(MSG* pMsg);
};
