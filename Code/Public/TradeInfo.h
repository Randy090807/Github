#pragma once
#include <map>
using namespace std;

class AFX_EXT_CLASS CTradeInfoItem
{
public:
	CTradeInfoItem();
	
	int		refrence;

	unsigned int nPreClose;               //前收盘价
	unsigned int nOpen;                   //开盘价
	unsigned int nHigh;                   //最高价
	unsigned int nLow;                    //最低价
	unsigned int nMatch;              //最新价
	unsigned int nAskPrice;           //申卖价
	unsigned int nBidPrice;           //申买价
	int	nYieldToMaturity;      //到期收益率
	unsigned int nHighLimited;            //涨停价
	unsigned int nLowLimited;         //跌停价

	unsigned int BP;	// 可用预约券数量
	unsigned int Space;	// 持仓数量
};

class AFX_EXT_CLASS CTradeInfo
{
protected:
	CTradeInfo();
	~CTradeInfo();

	void Init();
public:
	static CTradeInfo* Inst();
	int NextOrderInfo();

	void AddStock(LPCTSTR Stock);
	void DeleteStock(LPCTSTR Stock);

	CTradeInfoItem* GetStock(LPCTSTR Stock);

	void SetMsgReciver(CWnd* pWnd);
public:
	double		InitBP;
	double		BP;
	int			OrderRef;
	double		Amount;	// 总成交股数
	UINT		Volume;	// 总成交金额

	CWnd*		m_pMsgRevicer;
protected:
	map<CString, CTradeInfoItem*>	mapValues;//市值
};

