// ShortcutEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ShortcutEdit.h"


// CShortcutEdit

IMPLEMENT_DYNAMIC(CShortcutEdit, CEdit)

CShortcutEdit::CShortcutEdit()
{

}

CShortcutEdit::~CShortcutEdit()
{
}


BEGIN_MESSAGE_MAP(CShortcutEdit, CEdit)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CShortcutEdit message handlers




void CShortcutEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

//	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	BOOL bShift = FALSE;
	BOOL bCtrl = FALSE;

	BYTE   KeyBuf[256] = { 0 };
	GetKeyboardState(KeyBuf);
	if (KeyBuf[VK_SHIFT] >> 7 == TRUE)
	{
		bShift = TRUE;
	}
	if (KeyBuf[VK_CONTROL] >> 7 == TRUE)
	{
		bCtrl = TRUE;
	}

	if ( bCtrl == FALSE && bShift == FALSE 
		&& !((nChar >= 'a' && nChar <= 'z') || (nChar >= 'A' && nChar <= 'Z') || nChar == VK_ESCAPE || (nChar >=VK_F1 && nChar <= VK_F12))
		  )
	{
		return;
	}
	switch (nChar)
	{
	case VK_ESCAPE:
		SetWindowText(_T("ESC"));
		break;
	case VK_F1:
		SetWindowText(_T("F1"));
		break;
	case VK_F2:
		SetWindowText(_T("F2"));
		break;
	case VK_F3:
		SetWindowText(_T("F3"));
		break;
	case VK_F4:
		SetWindowText(_T("F4"));
		break;
	case VK_F5:
		SetWindowText(_T("F5"));
		break;
	case VK_F6:
		SetWindowText(_T("F6"));
		break;
	case VK_F7:
		SetWindowText(_T("F7"));
		break;
	case VK_F8:
		SetWindowText(_T("F8"));
		break;
	case VK_F9:
		SetWindowText(_T("F9"));
		break;
	case VK_F10:
		SetWindowText(_T("F10"));
		break;
	case VK_F11:
		SetWindowText(_T("F11"));
		break;
	case VK_F12:
		SetWindowText(_T("F12"));
		break;
	case VK_CONTROL:
	{
		BYTE   KeyBuf[256] = { 0 };
		GetKeyboardState(KeyBuf);
		if (KeyBuf[VK_SHIFT] >> 7 == TRUE)
		{
			SetWindowText(_T("CTRL+SHIFT"));
		}
		else
		{
			SetWindowText(_T("CTRL+"));
		}
	}
		
		break;
	case VK_SHIFT:
	{
		BYTE   KeyBuf[256] = { 0 };
		GetKeyboardState(KeyBuf);
		if (KeyBuf[VK_CONTROL] >> 7 == TRUE)
		{
			SetWindowText(_T("CTRL+SHIFT"));
		}
		else
		{
			SetWindowText(_T("SHIFT+"));
		}
	}
		break;
	default:
	{
		BYTE   KeyBuf[256] = { 0 };
		GetKeyboardState(KeyBuf);
		if (KeyBuf[VK_SHIFT] >> 7 == TRUE || KeyBuf[VK_CONTROL] >> 7 == TRUE)
		{
			CString szText;
			if (KeyBuf[VK_SHIFT] >> 7 == TRUE && KeyBuf[VK_CONTROL] >> 7 == TRUE)
			{
				szText.Format(_T("CTRL+SHIFT+%C"), nChar);
			}
			else if (KeyBuf[VK_SHIFT] >> 7 == TRUE)
			{
				szText.Format(_T("SHIFT+%C"), nChar);
			}
			else
			{
				szText.Format(_T("CTRL+%C"), nChar);
			}
			SetWindowText(szText);
		}
		else
			SetWindowText(_T(""));
		
		break;
	}
		
		
		
	}
	
}
