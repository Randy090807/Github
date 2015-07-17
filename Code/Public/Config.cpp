#include "stdafx.h"
#include "Config.h"
#include "sqlite3.h"
#include "Application.h"
#include "Utility.h"
#include <algorithm>
#include "../TinyXml/tinyxml.h"
#include "../Public/EnumDefine.h"

#pragma warning(disable:4018)

//////////////////////////////////////////////////////////////////////////
#define LOGIN_NETWORK_INFO_LIMIT 10

int _sql_callback_load_Logininfo(void * notused, int argc, char ** argv, char ** szColName)
{
	if (*argv == NULL)
		return 0;

	CLoginInfo* pQQSI = (CLoginInfo*)notused;
	ASSERT(pQQSI);

	switch (atoi(argv[0]))
	{
	case 0:
		pQQSI->Admin = UTF8ToUnicode(argv[1]);
		break;
	case 1:
		pQQSI->Operator = UTF8ToUnicode(argv[1]);
		break;
	case 2:
		pQQSI->AssetsUnit = UTF8ToUnicode(argv[1]);
		break;
	case 3:
		pQQSI->TradeUnit = UTF8ToUnicode(argv[1]);
		break;
	case 4:
		pQQSI->IsSavePwd = argv[1] == NULL ? FALSE : atoi(argv[1]);
		break;
	case 5:
		pQQSI->Password = UTF8ToUnicode(argv[1]);
		break;
		// 服务器IP
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		pQQSI->vSrvIPs.push_back(UTF8ToUnicode(argv[1]));
		break;
		// 服务器端口
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
		pQQSI->vSrvPorts.push_back(UTF8ToUnicode(argv[1]));
		break;
		// 行情源IP
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
		pQQSI->vPriceIPs.push_back(UTF8ToUnicode(argv[1]));
		break;
		// 行情源端口
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
	case 48:
	case 49:
		pQQSI->vPricePorts.push_back(UTF8ToUnicode(argv[1]));
		break;

	}

	return 0;
}

CLoginInfo::CLoginInfo()
{

}

CLoginInfo::~CLoginInfo()
{

}

void CLoginInfo::Load()
{
	CString szDBFile = CApplication::DataDir() + _T("\\conf.dat");
	string szFilePath = UnicodeToUTF8(szDBFile);

	sqlite3 * db = 0;
	char * pErrMsg = 0;
	int ret = 0;

	// 连接数据库
	ret = sqlite3_open(szFilePath.c_str(), &db);

	if (ret != SQLITE_OK)
	{
		sqlite3_close(db);
		ASSERT(0);
	}

	// 执行SQL
	ret = sqlite3_exec(db, "select key,value from login order by key asc", _sql_callback_load_Logininfo, this, &pErrMsg);
	if (ret != SQLITE_OK)
	{
		ASSERT(0);
		sqlite3_free(pErrMsg);
	}

	// 关闭数据库
	sqlite3_close(db);
}

CString CLoginInfo::GetSrvIP()
{
	return vSrvIPs.size() ? vSrvIPs[0] : _T("");
}

CString CLoginInfo::GetSrvPort()
{
	return vSrvPorts.size() ? vSrvPorts[0] : _T("");
}

CString CLoginInfo::GetPriceIP()
{
	return vPriceIPs.size() ? vPriceIPs[0] : _T("");
}

CString CLoginInfo::GetPricePort()
{
	return vPricePorts.size() ? vPricePorts[0] : _T("");
}

void CLoginInfo::AddSrvIP(LPCTSTR v)
{

	vector<CString>::iterator iter = std::find(vSrvIPs.begin(), vSrvIPs.end(), v);
	if (iter == vSrvIPs.end())
	{
		if (vSrvIPs.size() >= LOGIN_NETWORK_INFO_LIMIT)
		{
			vSrvIPs.erase(vSrvIPs.begin() + LOGIN_NETWORK_INFO_LIMIT);
		}
		vSrvIPs.insert(vSrvIPs.begin(), v);
	}
	else
	{
		vSrvIPs.erase(iter);
		vSrvIPs.insert(vSrvIPs.begin(), v);
	}

}

void CLoginInfo::AddSrvPort(LPCTSTR v)
{
	vector<CString>::iterator iter = std::find(vSrvPorts.begin(), vSrvPorts.end(), v);
	if (iter == vSrvPorts.end())
	{
		if (vSrvPorts.size() >= LOGIN_NETWORK_INFO_LIMIT)
		{
			vSrvPorts.erase(vSrvPorts.begin() + LOGIN_NETWORK_INFO_LIMIT);
		}
		vSrvPorts.insert(vSrvPorts.begin(), v);
	}
	else
	{
		vSrvPorts.erase(iter);
		vSrvPorts.insert(vSrvPorts.begin(), v);
	}
}

void CLoginInfo::AddPriceIP(LPCTSTR v)
{
	vector<CString>::iterator iter = std::find(vPriceIPs.begin(), vPriceIPs.end(), v);
	if (iter == vPriceIPs.end())
	{
		if (vPriceIPs.size() >= LOGIN_NETWORK_INFO_LIMIT)
		{
			vPriceIPs.erase(vPriceIPs.begin() + LOGIN_NETWORK_INFO_LIMIT);
		}
		vPriceIPs.insert(vPriceIPs.begin(), v);
	}
	else
	{	
		vPriceIPs.erase(iter);
		vPriceIPs.insert(vPriceIPs.begin(), v);
	}

}

void CLoginInfo::AddPricePort(LPCTSTR v)
{
	vector<CString>::iterator iter = std::find(vPricePorts.begin(), vPricePorts.end(), v);
	if (iter == vPricePorts.end())
	{
		if (vPricePorts.size() >= LOGIN_NETWORK_INFO_LIMIT)
		{
			vPricePorts.erase(vPricePorts.begin() + LOGIN_NETWORK_INFO_LIMIT);
		}
		vPricePorts.insert(vPricePorts.begin(), v);
	}
	else
	{
		
		vPricePorts.erase(iter);
		vPricePorts.insert(vPricePorts.begin(), v);
	}

}

int CLoginInfo::GetSrvIPSize()
{
	return vSrvIPs.size();
}

int CLoginInfo::GetSrvPortSize()
{
	return vSrvPorts.size();
}

int CLoginInfo::GetPriceIPSize()
{
	return vPriceIPs.size();
}

int CLoginInfo::GetPricePortSize()
{
	return vPricePorts.size();
}

CString CLoginInfo::GetSrvIPItem(int idx)
{
	return vSrvIPs[idx];
}

CString CLoginInfo::GetSrvPortItem(int idx)
{
	return vSrvPorts[idx];
}

CString CLoginInfo::GetPriceIPItem(int idx)
{
	return vPriceIPs[idx];
}

CString CLoginInfo::GetPricePortItem(int idx)
{
	return vPricePorts[idx];
}

void CLoginInfo::Save()
{
	CString szDBFile = CApplication::DataDir() + _T("\\conf.dat");
	string szFilePath = UnicodeToUTF8(szDBFile);

	sqlite3 * db = 0;
	char * pErrMsg = 0;
	int ret = 0;

	// 连接数据库
	ret = sqlite3_open(szFilePath.c_str(), &db);

	if (ret != SQLITE_OK)
	{
		sqlite3_close(db);
		ASSERT(0);
	}
	ret = sqlite3_exec(db, "BEGIN;", NULL, NULL, &pErrMsg);


	ret = sqlite3_exec(db, "delete from login where key >= 10", NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	char sql[256];
	sprintf_s(sql, "update login set value = '%s' where key = '0'", UnicodeToUTF8(Admin).c_str());
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update login set value = '%s' where key = '1'", UnicodeToUTF8(Operator).c_str());
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update login set value = '%s' where key = '2'", UnicodeToUTF8(AssetsUnit).c_str());
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update login set value = '%s' where key = '3'", UnicodeToUTF8(TradeUnit).c_str());
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update login set value = '%d' where key = '4'", IsSavePwd);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update login set value = '%s' where key = '5'", UnicodeToUTF8(Password).c_str());
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	for (int i = 0; i < vSrvIPs.size(); i++)
	{
		sprintf_s(sql, "insert into login(key,value) values('%d','%s')", 10 + i, UnicodeToUTF8(vSrvIPs[i]).c_str());
		ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
		ASSERT(ret == 0);
	}

	for (int i = 0; i < vSrvPorts.size(); i++)
	{
		sprintf_s(sql, "insert into login(key,value) values('%d','%s')", 20 + i, UnicodeToUTF8(vSrvPorts[i]).c_str());
		ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
		ASSERT(ret == 0);
	}

	for (int i = 0; i < vPriceIPs.size(); i++)
	{
		sprintf_s(sql, "insert into login(key,value) values('%d','%s')", 30 + i, UnicodeToUTF8(vPriceIPs[i]).c_str());
		ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
		ASSERT(ret == 0);
	}

	for (int i = 0; i < vPricePorts.size(); i++)
	{
		sprintf_s(sql, "insert into login(key,value) values('%d','%s')", 40 + i, UnicodeToUTF8(vPricePorts[i]).c_str());
		ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
		ASSERT(ret == 0);
	}

	ret = sqlite3_exec(db, "COMMIT;", NULL, NULL, &pErrMsg);
	// 关闭数据库
	sqlite3_close(db);
}
//////////////////////////////////////////////////////////////////////////
int _sql_callback_load_RecordInfo(void * notused, int argc, char ** argv, char ** szColName)
{
	if (*argv == NULL)
		return 0;

	CRecordInfo* pQQSI = (CRecordInfo*)notused;
	ASSERT(pQQSI);

	switch (atoi(argv[0]))
	{
	case 0:
		pQQSI->bCancelTip = atoi(argv[1]);
		break;
	case 1:
		pQQSI->bErrorReSend = atoi(argv[1]);
		break;
	case 2:
		pQQSI->bWasteReSend = atoi(argv[1]);
		break;
	case 3:
		pQQSI->clrBOColor = atoi(argv[1]);
		break;
	case 4:
		pQQSI->HKCancelSingle = atoi(argv[1]);
		break;
	case 5:
		pQQSI->HKCancelBat = atoi(argv[1]);
		break;
	case 6:
		pQQSI->HKModify = atoi(argv[1]);
		break;
	case 10:
		pQQSI->ParseBOInfo(argv[1]);
		break;
	}

	return 0;
}


CRecordInfo::CRecordInfo()
{

}

CRecordInfo::~CRecordInfo()
{
	Clear();
}

void CRecordInfo::Load()
{
	CString szDBFile = CApplication::DataDir() + _T("\\conf.dat");
	string szFilePath = UnicodeToUTF8(szDBFile);

	sqlite3 * db = 0;
	char * pErrMsg = 0;
	int ret = 0;

	// 连接数据库
	ret = sqlite3_open(szFilePath.c_str(), &db);

	if (ret != SQLITE_OK)
	{
		sqlite3_close(db);
		ASSERT(0);
	}

	// 执行SQL
	ret = sqlite3_exec(db, "select key,value from record order by key asc", _sql_callback_load_RecordInfo, this, &pErrMsg);
	if (ret != SQLITE_OK)
	{
		ASSERT(0);
		sqlite3_free(pErrMsg);
	}

	// 关闭数据库
	sqlite3_close(db);
}

void CRecordInfo::Save()
{
	CString szDBFile = CApplication::DataDir() + _T("\\conf.dat");
	string szFilePath = UnicodeToUTF8(szDBFile);

	sqlite3 * db = 0;
	char * pErrMsg = 0;
	int ret = 0;

	// 连接数据库
	ret = sqlite3_open(szFilePath.c_str(), &db);

	if (ret != SQLITE_OK)
	{
		sqlite3_close(db);
		ASSERT(0);
	}
	ret = sqlite3_exec(db, "BEGIN;", NULL, NULL, &pErrMsg);

	char sql[256];
	sprintf_s(sql, "update record set value = '%d' where key = '0'", bCancelTip);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update record set value = '%d' where key = '1'", bErrorReSend);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update record set value = '%d' where key = '2'", bWasteReSend);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update record set value = '%d' where key = '3'", clrBOColor);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update record set value = '%d' where key = '4'", HKCancelSingle);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update record set value = '%d' where key = '5'", HKCancelBat);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update record set value = '%d' where key = '6'", HKModify);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update record set value = '%s' where key = '10'", GenBOInfo().c_str());
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);
	
	ret = sqlite3_exec(db, "COMMIT;", NULL, NULL, &pErrMsg);
	// 关闭数据库
	sqlite3_close(db);
}

int CRecordInfo::BOSize()
{
	return vBigOrders.size();
}

CRecordInfo::CBigOrderInfo* CRecordInfo::Item(int idx)
{
	return vBigOrders[idx];
}

void CRecordInfo::ParseBOInfo(const char* xmlInfo)
{
	Clear();

	USES_CONVERSION;
	TiXmlDocument doc;
	if (!doc.Parse( xmlInfo))
	{
		return;
	}

	TiXmlElement* root = doc.RootElement();
	if (root)
	{
		TiXmlElement* child = root->FirstChildElement("Item");
		while (child)
		{
			int count = 0;
			string code;
			child->QueryStringAttribute("code", &code);
			child->QueryIntAttribute("count", &count);
			
			CRecordInfo::CBigOrderInfo* boi = new CRecordInfo::CBigOrderInfo();
			boi->count = count;
			boi->code = A2T(code.c_str());
			vBigOrders.push_back(  boi);

			child = child->NextSiblingElement("Item");
		}
	}
}

std::string CRecordInfo::GenBOInfo()
{
	USES_CONVERSION;

	string sRet;

	TiXmlDocument doc;
	doc.LinkEndChild(new TiXmlDeclaration("1.0", "gb18030", ""));

	TiXmlElement* root = new TiXmlElement("BigOrder");
	doc.LinkEndChild(root);

	for (int i = 0; i < vBigOrders.size(); i++)
	{
		TiXmlElement* item = new TiXmlElement("Item");
		item->SetAttribute("count", vBigOrders[i]->count);
		item->SetAttribute("code", T2A(vBigOrders[i]->code));
		root->LinkEndChild(item);
	}
	
	
	TiXmlPrinter printer;
	doc.Accept(&printer);

	sRet = printer.CStr();
	return sRet;
}

void CRecordInfo::Delete(int idx)
{
	delete vBigOrders[idx];
	vBigOrders.erase(vBigOrders.begin() + idx);
}

void CRecordInfo::Add(CBigOrderInfo* pBOI)
{
	vBigOrders.push_back(pBOI);
}

void CRecordInfo::Clear()
{
	for (auto iter = vBigOrders.begin(); iter != vBigOrders.end(); ++iter)
	{
		delete *iter;
	}
	vBigOrders.clear();
}


//////////////////////////////////////////////////////////////////////////
CStockInfo::CStockInfo()
{

}

CStockInfo::~CStockInfo()
{

}

CString CStockInfo::CodeToName(LPCTSTR code)
{
	auto iter = mapDatas.find(code);
	return iter == mapDatas.end() ? _T("Unkown") : iter->second;
}

void CStockInfo::Load()
{
	USES_CONVERSION;
	string filename = T2A(CApplication::DataDir() + _T("\\Stock.xml"));
	TiXmlDocument doc(filename.c_str());
	if (!doc.LoadFile())
	{
		return;
	}
	
	TiXmlElement* root = doc.RootElement();
	if ( root)
	{
		TiXmlElement* node = root->FirstChildElement("stock");
		while (node)
		{
			TiXmlElement* child = node->FirstChildElement("item");
			while (child)
			{
				string code, name;
				child->QueryStringAttribute("code", &code);
				child->QueryStringAttribute("name", &name);
				mapDatas.insert(make_pair<CString, CString>(A2T(code.c_str()), A2T(name.c_str())));
				child = child->NextSiblingElement("item");
			}
			node = node->NextSiblingElement("stock");
		}
	}

}

//////////////////////////////////////////////////////////////////////////
int _sql_callback_load_Level2Info(void * notused, int argc, char ** argv, char ** szColName)
{
	if (*argv == NULL)
		return 0;

	CLevel2Info* pWnd = (CLevel2Info*)notused;
	ASSERT(pWnd);

	switch (atoi(argv[0]))
	{
	case 0:
		pWnd->clrBid16 = atoi(argv[1]);	break;
	case 1:
		pWnd->clrBid27 = atoi(argv[1]);	break;
	case 2:
		pWnd->clrBid38 = atoi(argv[1]);	break;
	case 3:
		pWnd->clrBid49 = atoi(argv[1]);	break;
	case 4:
		pWnd->clrBid510 = atoi(argv[1]);	break;
	case 5:
		pWnd->clrRise = atoi(argv[1]);	break;
	case 6:
		pWnd->clrFall = atoi(argv[1]);	break;
	case 7:
		pWnd->dbLRSacle = atof(argv[1]);	break;
	case 8:
		pWnd->dbUDSacle = atof(argv[1]);	break;
	case 20:
		pWnd->ParseHKInfo(argv[1]);	break;
	}

	return 0;
}
CLevel2Info::CLevel2Info()
{
	
}

CLevel2Info::~CLevel2Info()
{
	Clear();
}

void CLevel2Info::Save()
{
	CString szDBFile = CApplication::DataDir() + _T("\\conf.dat");
	string szFilePath = UnicodeToUTF8(szDBFile);

	sqlite3 * db = 0;
	char * pErrMsg = 0;
	int ret = 0;

	// 连接数据库
	ret = sqlite3_open(szFilePath.c_str(), &db);

	if (ret != SQLITE_OK)
	{
		sqlite3_close(db);
		ASSERT(0);
	}
	ret = sqlite3_exec(db, "BEGIN;", NULL, NULL, &pErrMsg);

	char sql[2048];
	sprintf_s(sql, "update level2 set value = '%d' where key = '0'", clrBid16);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update level2 set value = '%d' where key = '1'", clrBid27);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update level2 set value = '%d' where key = '2'", clrBid38);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update level2 set value = '%d' where key = '3'", clrBid49);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update level2 set value = '%d' where key = '4'", clrBid510);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update level2 set value = '%d' where key = '5'", clrRise);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update level2 set value = '%d' where key = '6'", clrFall);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update level2 set value = '%.2f' where key = '7'", dbLRSacle);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update level2 set value = '%.2f' where key = '8'", dbUDSacle);
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	sprintf_s(sql, "update level2 set value = '%s' where key = '20'", GenHKInfo().c_str());
	ret = sqlite3_exec(db, sql, NULL, NULL, &pErrMsg);
	ASSERT(ret == 0);

	ret = sqlite3_exec(db, "COMMIT;", NULL, NULL, &pErrMsg);
	// 关闭数据库
	sqlite3_close(db);
}

void CLevel2Info::Load()
{
	CString szDBFile = CApplication::DataDir() + _T("\\conf.dat");
	string szFilePath = UnicodeToUTF8(szDBFile);

	sqlite3 * db = 0;
	char * pErrMsg = 0;
	int ret = 0;

	// 连接数据库
	ret = sqlite3_open(szFilePath.c_str(), &db);

	if (ret != SQLITE_OK)
	{
		sqlite3_close(db);
		ASSERT(0);
	}

	// 执行SQL
	ret = sqlite3_exec(db, "select key,value from level2 order by key asc", _sql_callback_load_Level2Info, this, &pErrMsg);
	if (ret != SQLITE_OK)
	{
		ASSERT(0);
		sqlite3_free(pErrMsg);
	}

	// 关闭数据库
	sqlite3_close(db);
}

int CLevel2Info::HKSize()
{
	return vHotKeys.size();
}

CLevel2Info::CHotKeySet* CLevel2Info::Item(int idx)
{
	return vHotKeys[idx];
}

void CLevel2Info::Delete(int idx)
{
	delete vHotKeys[idx];
	vHotKeys.erase(vHotKeys.begin() + idx);
}

void CLevel2Info::Add(CHotKeySet* pHKS)
{
	vHotKeys.push_back(pHKS);
}

void CLevel2Info::Clear()
{
	for (auto iter = vHotKeys.begin(); iter != vHotKeys.end(); ++iter)
	{
		delete (*iter);
	}
	vHotKeys.clear();
}

void CLevel2Info::ParseHKInfo(const char* xmlInfo)
{
	Clear();

	USES_CONVERSION;
	TiXmlDocument doc;
	if (!doc.Parse(xmlInfo))
	{
		return;
	}

	TiXmlElement* root = doc.RootElement();
	if (root)
	{
		TiXmlElement* child = root->FirstChildElement("Item");
		while (child)
		{
			CLevel2Info::CHotKeySet* pHKI = new CLevel2Info::CHotKeySet();

			child->QueryIntAttribute("Direction", &pHKI->Direction);
			child->QueryIntAttribute("ReSend", &pHKI->ReSend);
			child->QueryIntAttribute("Price", &pHKI->Price);
			child->QueryDoubleAttribute("Offset", &pHKI->Offset);
			child->QueryIntAttribute("Count", &pHKI->Count);
			child->QueryIntAttribute("HotKey", (int*)(&pHKI->HotKey));
			child->QueryIntAttribute("Default", &pHKI->Default);

			vHotKeys.push_back(pHKI);

			child = child->NextSiblingElement("Item");
		}
	}
}

std::string CLevel2Info::GenHKInfo()
{
	USES_CONVERSION;
	string sRet;

// 	vHotKeys.push_back(new CLevel2Info::CHotKeySet());
// 	vHotKeys.push_back(new CLevel2Info::CHotKeySet());
// 	vHotKeys.push_back(new CLevel2Info::CHotKeySet());
// 	vHotKeys.push_back(new CLevel2Info::CHotKeySet());

	TiXmlDocument doc;
	doc.LinkEndChild(new TiXmlDeclaration("1.0", "gb18030", ""));

	TiXmlElement* root = new TiXmlElement("HotKeySetting");
	doc.LinkEndChild(root);

	for (int i = 0; i < vHotKeys.size(); i++)
	{
		TiXmlElement* item = new TiXmlElement("Item");
		item->SetAttribute("Direction", vHotKeys[i]->Direction);
		item->SetAttribute("ReSend", vHotKeys[i]->ReSend);
		item->SetAttribute("Price", vHotKeys[i]->Price);
		item->SetDoubleAttribute("Offset", vHotKeys[i]->Offset);
		item->SetAttribute("Count", vHotKeys[i]->Count);
		item->SetAttribute("HotKey", vHotKeys[i]->HotKey);
		item->SetAttribute("Default", vHotKeys[i]->Default);

		root->LinkEndChild(item);
	}


	TiXmlPrinter printer;
	doc.Accept(&printer);

	sRet = printer.CStr();
	return sRet;
}

CString CLevel2Info::CHotKeySet::HotKeyName()
{
	UINT fuModifiers = (UINT)HIBYTE(HotKey);  // key-modifier flags      
	UINT uVirtKey = (UINT)LOBYTE(HotKey);     // virtual-key code      

//	MapVirtualKey(uVirtKey, 0);

	CString szText;
	TCHAR vkName[64] = { 0 };
	GetKeyNameText((MapVirtualKey(uVirtKey, 0) << 16), vkName, 64);

	if ( fuModifiers & HOTKEYF_CONTROL)
	{
		szText += _T("CTRL + ");
	}
	if (fuModifiers & HOTKEYF_SHIFT)
	{
		szText += _T("SHIFT + ");
	}
	if (fuModifiers & HOTKEYF_ALT)
	{
		szText += _T("ALT + ");
	}
	szText += vkName;
	return szText;
}

CString CLevel2Info::CHotKeySet::ReSendName()
{
	return g_ReSendName[ReSend];
}

CString CLevel2Info::CHotKeySet::PriceName()
{
	return g_PriceName[Price];
}

CString CLevel2Info::CHotKeySet::CountName()
{
	CString szText(_T("Default"));
	if ( Count != 0)
	{
		szText.Format(_T("%u"), Count);
	}
	return szText;
}

CString CLevel2Info::CHotKeySet::DirectionName()
{
	return g_OrderTypeName[Direction];
}

//////////////////////////////////////////////////////////////////////////
CConfig::CConfig()
{
}


CConfig::~CConfig()
{
}

CConfig* CConfig::Inst()
{
	static CConfig _inst;
	static bool bInit = false;
	if (!bInit)
	{
		bInit = true;
		_inst.Init();
	}
	return &_inst;
}

void CConfig::Init()
{
	m_LoginInfo.Load();
	m_StockInfo.Load();
	m_RecordInfo.Load();
	m_Level2Info.Load();
}

CLoginInfo* CConfig::LogInfo()
{
	return &m_LoginInfo;
}

CStockInfo* CConfig::StockInfo()
{
	return &m_StockInfo;
}

CRecordInfo* CConfig::RecordInfo()
{
	return &m_RecordInfo;
}

CLevel2Info* CConfig::Level2Info()
{
	return &m_Level2Info;
}

void CConfig::Save()
{
	m_LoginInfo.Save();
	m_RecordInfo.Save();
	m_Level2Info.Save();
}


