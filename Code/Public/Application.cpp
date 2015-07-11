// Application.cpp: implementation of the TApplication class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Application.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CString CApplication::MainDir()
{
  HMODULE   module   =   GetModuleHandle( NULL);     
  TCHAR   buf[MAX_PATH];     
  GetModuleFileName(module, buf, sizeof(buf));    
  PathRemoveFileSpec(buf);
  return CString(buf);
}

CString CApplication::TempDir()
{
	TCHAR path[MAX_PATH];
	::GetTempPath( MAX_PATH, path);
	return CString( path);
}

CString CApplication::LogDir()
{
   TCHAR buf[MAX_PATH];
   StrCpy( buf, MainDir());
   return CString( StrCat(buf, _T("\\Log")));
}


CString CApplication::ExeFileName()
{
  HMODULE module = GetModuleHandle(0);     
  TCHAR   buf[MAX_PATH];     
  GetModuleFileName( module, buf, MAX_PATH);     
  return CString(buf);	
}


CString CApplication::ImageDir()
{
	TCHAR buf[MAX_PATH];
	StrCpy( buf, MainDir());
	return CString( StrCat(buf, _T("\\Image")));
}

CString CApplication::AppTempDir()
{
	TCHAR buf[MAX_PATH];
	StrCpy( buf, MainDir());
	return CString( StrCat(buf, _T("\\Temp")));
}

CString CApplication::ConfigDir()
{
	TCHAR buf[MAX_PATH];
	StrCpy( buf, MainDir());
	return CString( StrCat(buf, _T("\\Config")));
}
