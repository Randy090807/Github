
#pragma once

AFX_EXT_API BOOL PngFromIDResource( UINT nID, Image * & pImg); 

AFX_EXT_API int _GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

AFX_EXT_API TCHAR* NewGuid(TCHAR* guidBuf);

AFX_EXT_API BOOL SaveBitmapToFile(HBITMAP hBitmap, LPCTSTR lpFileName );