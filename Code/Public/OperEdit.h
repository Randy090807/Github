#pragma once


// COperEdit

class AFX_EXT_CLASS COperEdit : public CEdit
{
	DECLARE_DYNAMIC(COperEdit)

public:
	COperEdit();
	virtual ~COperEdit();

public:
	void SetUpDownScale(double v)
	{
		m_nUDScale = v;
	}
	void SetLeftRightScale(double v)
	{
		m_nLRScale = v;
	}
private:
	double	m_nUDScale;
	double	m_nLRScale;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


