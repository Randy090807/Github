#include "stdafx.h"
#include "MsgBuilder.h"



char* CMsgBuilder::BuildNewOrder(vector<CString>& stockidlst, char* &outbuf, int& outbuflen)
{
	USES_CONVERSION;

	string stockids;
	for (unsigned int i = 0; i < stockidlst.size(); i++)
	{
		if (!stockids.empty())
		{
			stockids.append(",");
		}
		stockids.append(T2A(stockidlst[i]));
	}

	outbuflen = sizeof(MsgHeader) + stockids.length();
	outbuf = new char[outbuflen];
	memcpy(outbuf + sizeof(MsgHeader), stockids.c_str(), stockids.length());
	MsgHeader* msgHeader = (MsgHeader*)(outbuf);
	msgHeader->flag = MSG_HEADER_TAG;
	msgHeader->len = stockids.length();
	msgHeader->type = ID_SUBSCRIBE_ADD;
	return outbuf;
}

char* CMsgBuilder::BuildNewOrder(LPCTSTR stockid, char* &outbuf, int& outbuflen)
{
	USES_CONVERSION;

	string stockids = T2A(stockid);
	
	outbuflen = sizeof(MsgHeader) + stockids.length();
	outbuf = new char[outbuflen];
	memcpy(outbuf + sizeof(MsgHeader), stockids.c_str(), stockids.length());
	MsgHeader* msgHeader = (MsgHeader*)(outbuf);
	msgHeader->flag = MSG_HEADER_TAG;
	msgHeader->len = stockids.length();
	msgHeader->type = ID_SUBSCRIBE_ADD;

	return outbuf;
}

char* CMsgBuilder::BuildCancelOrder(LPCTSTR stockid, char* &outbuf, int& outbuflen)
{
	USES_CONVERSION;

	string stockids = T2A(stockid);

	outbuflen = sizeof(MsgHeader) + stockids.length();
	outbuf = new char[outbuflen];
	memcpy(outbuf + sizeof(MsgHeader), stockids.c_str(), stockids.length());
	MsgHeader* msgHeader = (MsgHeader*)(outbuf);
	msgHeader->flag = MSG_HEADER_TAG;
	msgHeader->len = stockids.length();
	msgHeader->type = ID_SUBSCRIBE_CANCEL;

	return outbuf;
}

char* CMsgBuilder::BuildStockCode( char* &outbuf, int& outbuflen)
{
	outbuflen = sizeof(MsgHeader);
	outbuf = new char[outbuflen];
	MsgHeader* msgHeader = (MsgHeader*)(outbuf);
	msgHeader->flag = MSG_HEADER_TAG;
	msgHeader->len = 0;
	msgHeader->type = ID_GET_STOCK_CODE_TABLE;

	return outbuf;
}
