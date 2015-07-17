#include "StdAfx.h"
#include "Logger.h"
#include "Application.h"

#pragma warning(disable:4996)

#define USE_LOGGER	1

CLogger::CLogger(void)
{
#if USE_LOGGER
	char filename[MAX_PATH] = {0};
	COleDateTime dt(COleDateTime::GetCurrentTime());

	sprintf( filename, "%s\\%04d%02d%02d%.txt", CApplication::LogDir(), 
		dt.GetYear(),dt.GetMonth(),dt.GetDay());
	_f.open(filename, ios::out || ios::app);
#endif
}


CLogger::~CLogger(void)
{
#if USE_LOGGER
	_f.close();
#endif
}

void CLogger::WriteB( const char* content, int len )
{
#if USE_LOGGER
	WriteHeader();
	_f.write( content, len);
	_f << endl;
#endif
}

// void CLogger::Write( char* content )
// {
// 	WriteHeader();
// 	_f << content << endl;
// }

void CLogger::Write( char* content, ... )
{
#if USE_LOGGER
	WriteHeader();

	_f << content;

	va_list marker;
	va_start( marker, content );     
	while( 1 )
	{
		char* p = va_arg( marker, char*);
		if ( p == NULL)
			break;
		_f << p;
	}
	va_end( marker );              /* Reset variable arguments.      */
	_f << endl;

#endif
}

void CLogger::WriteHeader()
{
	COleDateTime dt(COleDateTime::GetCurrentTime());
	CStringA header;
	header.Format( "[%04d-%02d-%02d %02d:%02d:%02d]\t",
		dt.GetYear(),dt.GetMonth(),dt.GetDay(),dt.GetHour(),dt.GetMinute(),dt.GetSecond());
	_f << header;
}

CLogger* CLogger::Inst()
{
	static CLogger _loger;
	return &_loger;
}
