#pragma once


// CRTButton

class CRTButton : public CButton
{
	DECLARE_DYNAMIC(CRTButton)

public:
	CRTButton();
	virtual ~CRTButton();

	Image*		m_pImage;
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


