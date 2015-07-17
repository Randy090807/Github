
#pragma once
#include <string>
using namespace std;

#include <gdiplus.h>
using namespace Gdiplus;


// 从资源中加载Png图像到GDI+ Image
AFX_EXT_API BOOL PngFromIDResource( UINT nID, Image * & pImg); 

// 生成Guid
AFX_EXT_API TCHAR* NewGuid(TCHAR* guidBuf);

// 保存图片到文件
AFX_EXT_API BOOL SaveBitmapToFile(HBITMAP hBitmap, LPCTSTR lpFileName );



// Utf字符转Unicode
AFX_EXT_API CString  UTF8ToUnicode(char* UTF8);

// Unicode字符转Utf
AFX_EXT_API std::string  UnicodeToUTF8(CString& wstr);

// 解析热键的值，用于注册热键
AFX_EXT_API void ParseHotKey(DWORD hotkey, DWORD& wVirtualKeyCode, DWORD& wModifiers);
