#pragma once
#include <map>
using namespace std;

class AFX_EXT_CLASS CTradeInfoItem
{
public:
	CTradeInfoItem();
	
	int		refrence;

	unsigned int nPreClose;               //ǰ���̼�
	unsigned int nOpen;                   //���̼�
	unsigned int nHigh;                   //��߼�
	unsigned int nLow;                    //��ͼ�
	unsigned int nMatch;              //���¼�
	unsigned int nAskPrice;           //������
	unsigned int nBidPrice;           //�����
	int	nYieldToMaturity;      //����������
	unsigned int nHighLimited;            //��ͣ��
	unsigned int nLowLimited;         //��ͣ��

	unsigned int BP;	// ����ԤԼȯ����
	unsigned int Space;	// �ֲ�����
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
	double		Amount;	// �ܳɽ�����
	UINT		Volume;	// �ܳɽ����

	CWnd*		m_pMsgRevicer;
protected:
	map<CString, CTradeInfoItem*>	mapValues;//��ֵ
};

