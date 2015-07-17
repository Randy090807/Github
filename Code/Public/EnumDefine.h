#pragma once

// 定单类型名称
static LPCTSTR g_OrderTypeName[] =
{
	_T("普通买入"), _T("普通卖出"), _T("担保品买入"), _T("担保品卖出"), _T("融资买入"), _T("融券卖出"), _T("约券卖出"),
};

// 定单类型Value
static LPCTSTR g_OrderTypeVal[] =
{
	_T("1a"), _T("2a"), _T("ab"), _T("2b"), _T("1c"), _T("2c"), _T("3d"),
};

// 重发
static LPCTSTR g_ReSendName[] =
{
	_T("不改变"), _T("改变"),
};

// 价位
static LPCTSTR g_PriceName[] =
{
	_T("Bid"), _T("Ask"), _T("涨停价"), _T("跌停价"), _T("开盘价")
};