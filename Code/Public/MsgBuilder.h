#pragma once
#include "MsgDefine.h"


class AFX_EXT_CLASS CMsgBuilder
{
public:
	static char* BuildNewOrder(vector<CString>& stockidlst, char* &outbuf, int& outbuflen);
	static char* BuildNewOrder(LPCTSTR stockid, char* &outbuf, int& outbuflen);

	static char* BuildCancelOrder(LPCTSTR stockid, char* &outbuf, int& outbuflen);

	static char* BuildStockCode(char* &outbuf, int& outbuflen);
};

