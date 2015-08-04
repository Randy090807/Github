#pragma once
#include "../Public/MsgDefine.h"


class COrderRecord : public CXTPReportRecord
{
public:
	COrderRecord();

	int GetOrderRef();
	int GetVolume();
	double GetPrice();
	CString GetStock();
	CString GetOrderType();

	void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics);

public:
	CString StatusName(int iStatus);
	CString OrderTypeName( LPCTSTR orderType);
	CString OrderType;
};

class COrderReportCtrl :public CXTPReportControl
{
public:
	COrderReportCtrl();
	~COrderReportCtrl();

	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	void CreateColumns();
	void AddRecord(COrderInquiryResultMsg::COrders* pOrder);
	void AddRecord2(COrderInquiryResultMsg::COrders* pOrder);
protected:
	CXTPReportRecord* FindRecord(int OrderRef);
	void AddItemToReport(COrderInquiryResultMsg::COrders* iter);
	void ModifyItemToReport(COrderInquiryResultMsg::COrders* iter, CXTPReportRecord* pRecord);
};

