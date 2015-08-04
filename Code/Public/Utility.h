
#pragma once
#include <string>
using namespace std;

#include <gdiplus.h>
using namespace Gdiplus;


// ����Դ�м���Pngͼ��GDI+ Image
AFX_EXT_API BOOL PngFromIDResource( UINT nID, Image * & pImg); 

// ����Guid
AFX_EXT_API TCHAR* NewGuid(TCHAR* guidBuf);

// ����ͼƬ���ļ�
AFX_EXT_API BOOL SaveBitmapToFile(HBITMAP hBitmap, LPCTSTR lpFileName );



// Utf�ַ�תUnicode
AFX_EXT_API CString  UTF8ToUnicode(const char* UTF8);

// Unicode�ַ�תUtf
AFX_EXT_API std::string  UnicodeToUTF8(CString& wstr);

// �����ȼ���ֵ������ע���ȼ�
AFX_EXT_API void ParseHotKey(DWORD hotkey, DWORD& wVirtualKeyCode, DWORD& wModifiers);

// ��(HHMMSSmmm)���θ�ʽ��Ϊ�ַ���
AFX_EXT_API CString FormatTime(UINT t);

// �۸���㣬������˴���ļ۸�ת��Ϊ���ؼ۸�
AFX_EXT_API double PriceTrans(double price);