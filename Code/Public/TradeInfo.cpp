#include "stdafx.h"
#include "TradeInfo.h"
#include "MsgBuilder.h"
#include "MsgDefine.h"

CTradeInfoItem::CTradeInfoItem()
	: refrence(0)
	, Space(0)
	, BP(0)
{

}


//////////////////////////////////////////////////////////////////////////
CTradeInfo::CTradeInfo()
	:OrderRef(0)
	, BP(0)
	, InitBP(0)
	, Amount(0)
	, Volume(0)
	, m_pMsgRevicer(NULL)
{
}


CTradeInfo::~CTradeInfo()
{
	for (auto iter = mapValues.begin(); iter != mapValues.end(); ++iter)
	{
		delete iter->second;
	}
}

int CTradeInfo::NextOrderInfo()
{
	return ++OrderRef;
}

CTradeInfo* CTradeInfo::Inst()
{
	static CTradeInfo _inst;
	static bool bInit = false;
	if ( !bInit)
	{
		_inst.Init();
		bInit = true;
	}
	return &_inst;
}

void CTradeInfo::Init()
{

}


void CTradeInfo::AddStock(LPCTSTR Stock)
{
	auto iter = mapValues.find(Stock);
	if (iter == mapValues.end())
	{
		CTradeInfoItem* pTII = new CTradeInfoItem();
		pTII->refrence++;
		mapValues.insert(make_pair(Stock, pTII));
	}
	else
	{
		iter->second->refrence++;
	}

	char* msgbuf = 0;
	int msglen = 0;
	CMsgBuilder::BuildNewOrder(Stock, msgbuf, msglen);
	::PostMessage(m_pMsgRevicer->GetSafeHwnd(), UM_SRV_DATA_REPORT2, (WPARAM)msgbuf, (LPARAM)msglen);
}

void CTradeInfo::DeleteStock(LPCTSTR Stock)
{
	auto iter = mapValues.find(Stock);
	if (iter != mapValues.end())
	{
		iter->second->refrence--;
		if ( iter->second->refrence == 0)
		{
			char* msgbuf = 0;
			int msglen = 0;
			CMsgBuilder::BuildCancelOrder(Stock, msgbuf, msglen);
			::PostMessage(m_pMsgRevicer->GetSafeHwnd(), UM_SRV_DATA_REPORT2, (WPARAM)msgbuf, (LPARAM)msglen);

			delete iter->second;
			mapValues.erase(iter);
		}
	}
}


void CTradeInfo::SetMsgReciver(CWnd* pWnd)
{
	m_pMsgRevicer = pWnd;
}

CTradeInfoItem* CTradeInfo::GetStock(LPCTSTR Stock)
{
	auto iter = mapValues.find(Stock);
	return iter != mapValues.end() ? iter->second : NULL;
}
