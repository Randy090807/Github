#pragma once
class AFX_EXT_CLASS CReportCtrlLayout
{
public:
	CReportCtrlLayout();
	~CReportCtrlLayout();
public:
	static void Layout(LPCTSTR lpLayoutFile, CXTPReportControl* pControl);
	static void SaveLayout(LPCTSTR lpLayoutFile, CXTPReportControl* pControl);
};

