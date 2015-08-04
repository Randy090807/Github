#include "stdafx.h"
#include "OrderReportCtrl.h"
#include "../Public/Config.h"
#include "../Public/EnumDefine.h"
#include "../Public/Utility.h"
//

COrderRecord::COrderRecord()
{

}

int COrderRecord::GetOrderRef()
{
	return _ttoi(GetItem(0)->GetCaption());
}

void COrderRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	UINT count = _ttoi(pDrawArgs->pRow->GetRecord()->GetItem(8)->GetCaption());
	CString code = pDrawArgs->pRow->GetRecord()->GetItem(2)->GetCaption();

	for (int i = 0; i < CConfig::Inst()->RecordInfo()->BOSize(); i++)
	{
		CRecordInfo::CBigOrderInfo* pBOI = CConfig::Inst()->RecordInfo()->Item(i);
		if (pBOI->code.CompareNoCase(code) == 0
			&& pBOI->count <= count)
		{
			pItemMetrics->clrBackground = CConfig::Inst()->RecordInfo()->clrBOColor;
		}
	}
}

int COrderRecord::GetVolume()
{
	return _ttoi(GetItem(7)->GetCaption());
}

double COrderRecord::GetPrice()
{
	return _ttof(GetItem(5)->GetCaption());
}

CString COrderRecord::GetStock()
{
	return	GetItem(2)->GetCaption();
}

CString COrderRecord::GetOrderType()
{
	return OrderType;
}

CString COrderRecord::StatusName(int iStatus)
{
	return g_StatusName[iStatus];
}

CString COrderRecord::OrderTypeName(LPCTSTR orderType)
{
	for (int i = 0; i < sizeof(g_OrderTypeVal)/sizeof(LPCTSTR); i++)
	{
		if ( StrCmp( g_OrderTypeVal[i] ,orderType) == 0)
		{
			return g_OrderTypeName[i];
		}
	}
	return _T("");
}

//////////////////////////////////////////////////////////////////////////
static LPCTSTR g_columns[] =
{
	_T("客户端订单ID"),
	_T("时间"),
	_T("代码"),
	_T("名称"),
	_T("券商订单ID"),
	_T("送单价格"),
	_T("成交价格"),
	_T("送单股数"),
	_T("成交股数"),
	_T("方式"),
	_T("成交与否"),
	_T("信息"),
};

COrderReportCtrl::COrderReportCtrl()
{
}


COrderReportCtrl::~COrderReportCtrl()
{
}

BOOL COrderReportCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext /*= NULL*/)
{
	return CXTPReportControl::Create(dwStyle, rect, pParentWnd, nID, pContext);
}

void COrderReportCtrl::AddRecord(COrderInquiryResultMsg::COrders* pOrder)
{
	CXTPReportRecord* pRecord = FindRecord(pOrder->OrderRef);
	if (pRecord == NULL)	// 视图中不存在
	{
		if (!pOrder->IsDone())	// 订单未成交，在视图中添加
		{
			AddItemToReport(pOrder);
		}
	}
	else
	{
		if (pOrder->IsDone())	// 订单已成交，从视图中移除
		{
			RemoveRecordEx(pRecord, FALSE);
		}
		else // 订单未成交，在视图中添加
		{
			ModifyItemToReport(pOrder, pRecord);
		}
	}
}


void COrderReportCtrl::AddRecord2(COrderInquiryResultMsg::COrders* pOrder)
{
	CXTPReportRecord* pRecord = FindRecord(pOrder->OrderRef);
	if (pRecord == NULL)	// 视图中不存在
	{
		if (pOrder->IsDone())	// 订单未成交，在视图中添加
		{
			AddItemToReport(pOrder);
		}
	}
	else
	{
		if ( pOrder->IsDone())	// 订单已成交，从视图中移除
		{
			ModifyItemToReport(pOrder, pRecord);
		}
	}
}

void COrderReportCtrl::CreateColumns()
{
	GetReportHeader()->AllowColumnRemove(FALSE);
	SetGridStyle(TRUE, xtpReportLineStyleSolid);
	SetGridStyle(FALSE, xtpReportLineStyleSolid);
	GetReportHeader()->AllowColumnResize(TRUE);

	for (int i = 0; i < sizeof(g_columns) / sizeof(LPCTSTR); i++)
	{
		CXTPReportColumn* pColumn = new CXTPReportColumn(i, g_columns[i], 70, FALSE, XTP_REPORT_NOICON, TRUE);
		pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
		pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
		pColumn->EnableResize(TRUE);
		AddColumn(pColumn);
	}
}

CXTPReportRecord* COrderReportCtrl::FindRecord(int OrderRef)
{
	for (int i = 0; i < GetRecords()->GetCount(); i++)
	{
		COrderRecord* pRecord = (COrderRecord*)(GetRecords()->GetAt(i));
		if ( pRecord->GetOrderRef()== OrderRef)
		{
			return GetRecords()->GetAt(i);
		}
	}
	return NULL;
}

void COrderReportCtrl::AddItemToReport(COrderInquiryResultMsg::COrders* iter)
{
	COrderRecord* pRecord = new COrderRecord();
	CXTPReportControl::AddRecord(pRecord);

	pRecord->AddItem(new CXTPReportRecordItemNumber(iter->OrderRef));
	pRecord->AddItem(new CXTPReportRecordItemText( FormatTime(iter->ReportTime)));
	pRecord->AddItem(new CXTPReportRecordItemText(iter->StockID));
	pRecord->AddItem(new CXTPReportRecordItemText(CConfig::Inst()->StockInfo()->CodeToName(iter->StockID)));
	pRecord->AddItem(new CXTPReportRecordItemText(iter->OrderID));
	pRecord->AddItem(new CXTPReportRecordItemNumber(iter->Price, _T("%.2f")));
	pRecord->AddItem(new CXTPReportRecordItemNumber(iter->ExeAmount, _T("%.2f")));
	pRecord->AddItem(new CXTPReportRecordItemNumber(iter->Volume));
	pRecord->AddItem(new CXTPReportRecordItemNumber(iter->ExeVol));
	pRecord->AddItem(new CXTPReportRecordItemText(pRecord->OrderTypeName(iter->OrderType)));
	pRecord->AddItem(new CXTPReportRecordItemText(pRecord->StatusName(iter->Status)));
	pRecord->AddItem(new CXTPReportRecordItemText(iter->ErrMsg));

	pRecord->OrderType = iter->OrderType;

}

void COrderReportCtrl::ModifyItemToReport(COrderInquiryResultMsg::COrders* iter, CXTPReportRecord* pRecord)
{
	COrderRecord* pRecord2 = (COrderRecord*)pRecord;
	((CXTPReportRecordItemNumber*)pRecord->GetItem(0))->SetValue(iter->OrderRef);
	((CXTPReportRecordItemText*)pRecord->GetItem(1))->SetValue(FormatTime(iter->ReportTime));
	((CXTPReportRecordItemText*)pRecord->GetItem(2))->SetValue(iter->StockID);
	((CXTPReportRecordItemText*)pRecord->GetItem(3))->SetValue(CConfig::Inst()->StockInfo()->CodeToName(iter->StockID));
	((CXTPReportRecordItemText*)pRecord->GetItem(4))->SetValue(iter->OrderID);
	((CXTPReportRecordItemNumber*)pRecord->GetItem(5))->SetValue(iter->Price);
	((CXTPReportRecordItemNumber*)pRecord->GetItem(6))->SetValue(iter->ExeAmount);
	((CXTPReportRecordItemNumber*)pRecord->GetItem(7))->SetValue(iter->Volume);
	((CXTPReportRecordItemNumber*)pRecord->GetItem(8))->SetValue(iter->ExeVol);
	((CXTPReportRecordItemText*)pRecord->GetItem(9))->SetValue(pRecord2->OrderTypeName(iter->OrderType));
	((CXTPReportRecordItemText*)pRecord->GetItem(10))->SetValue(pRecord2->StatusName(iter->Status));
	((CXTPReportRecordItemText*)pRecord->GetItem(11))->SetValue(iter->ErrMsg);

}

