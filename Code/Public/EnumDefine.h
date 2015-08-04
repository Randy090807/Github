#pragma once

// 定单类型名称
static LPCTSTR g_OrderTypeName[] =
{
	_T("普通买入"), _T("普通卖出"), _T("担保品买入"), _T("担保品卖出"), _T("融资买入"), _T("融券卖出"), _T("约券卖出"),
};

// 定单类型Value
static LPCTSTR g_OrderTypeVal[] =
{
	_T("1a"), _T("2a"), _T("1b"), _T("2b"), _T("1c"), _T("2c"), _T("2d"),
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

// 订单状态
static LPCTSTR g_StatusName[] =
{
	_T("未报"), _T("待报"), _T("已报"), _T("已报待撤"), _T("部分待撤"), _T("部分已撤"), 
	_T("已撤"), _T("部分完成"), _T("已成"), _T("已成"), _T("废单")
};