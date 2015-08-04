
#include "stdafx.h"
#include "Utility.h"


int _GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

BOOL PngFromIDResource( UINT nID, Image * & pImg )
{
	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(nID),_T("PNG"));
	HRSRC hRsrc = ::FindResource ( hInst,MAKEINTRESOURCE(nID),_T("PNG")); // type  
	if (!hRsrc)  
		return FALSE;  
	// load resource into memory  
	DWORD len = SizeofResource(hInst, hRsrc);  
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);  
	if (!lpRsrc)  
		return FALSE;  
	// Allocate global memory on which to create stream  
	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);  
	BYTE* pmem = (BYTE*)GlobalLock(m_hMem);  
	memcpy(pmem,lpRsrc,len);  
	IStream* pstm;  
	CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);  
	// load from stream  
	pImg=Gdiplus::Image::FromStream(pstm);  
	// free/release stuff  
	GlobalUnlock(m_hMem);  
	pstm->Release();  
	FreeResource(lpRsrc);  
	return TRUE;
}

int _GetEncoderClsid( const WCHAR* format, CLSID* pClsid )
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes
	ImageCodecInfo* pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return -1;  // Failure
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure
	GetImageEncoders(num, size, pImageCodecInfo);
	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}   
	}
	free(pImageCodecInfo);
	return -1;  // Failure
}

AFX_EXT_API TCHAR* NewGuid( TCHAR* guidBuf )
{
	GUID guid;
	if(S_OK == ::CoCreateGuid( &guid))
	{
#ifdef _UNICODE
		swprintf(guidBuf, 64,
			_T("{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}"),
			guid.Data1,
			guid.Data2,
			guid.Data3,
			guid.Data4[0], guid.Data4[1],
			guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
#else
		sprintf(guidBuf, 
			"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			guid.Data1,
			guid.Data2,
			guid.Data3,
			guid.Data4[0], guid.Data4[1],
			guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
#endif
	}
	return guidBuf;
}


AFX_EXT_API BOOL SaveBitmapToFile(HBITMAP hBitmap, LPCTSTR lpFileName )
{ 
	HDC hDC; //设备描述表 
	int iBits; //当前显示分辨率下每个像素所占字节数 
	WORD wBitCount; //位图中每个像素所占字节数 
	DWORD dwPaletteSize=0, //定义调色板大小， 位图中像素字节大小 ，位图文件大小 ， 写入文件字节数 
		dwBmBitsSize, 
		dwDIBSize, dwWritten; 
	BITMAP Bitmap; //位图属性结构 
	BITMAPFILEHEADER bmfHdr; //位图文件头结构 
	BITMAPINFOHEADER bi; //位图信息头结构 
	LPBITMAPINFOHEADER lpbi; //指向位图信息头结构 

	HANDLE fh, hDib, hPal,hOldPal=NULL; //定义文件，分配内存句柄，调色板句柄 

	//计算位图文件每个像素所占字节数 
	HDC hWndDC = CreateDC(_T("DISPLAY"),NULL,NULL,NULL); 
	hDC = ::CreateCompatibleDC( hWndDC ) ; 
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES); 
	DeleteDC(hDC); 

	if (iBits <= 1) 
		wBitCount = 1; 
	else if (iBits <= 4) 
		wBitCount = 4; 
	else if (iBits <= 8) 
		wBitCount = 8; 
	else if (iBits <= 24) 
		wBitCount = 24; 
	else 
		wBitCount = 24 ; 

	//计算调色板大小 
	if (wBitCount <= 8) 
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD); 

	//设置位图信息头结构 
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap); 
	bi.biSize = sizeof(BITMAPINFOHEADER); 
	bi.biWidth = Bitmap.bmWidth; 
	bi.biHeight = Bitmap.bmHeight; 
	bi.biPlanes = 1; 
	bi.biBitCount = wBitCount; 
	bi.biCompression = BI_RGB; 
	bi.biSizeImage = 0; 
	bi.biXPelsPerMeter = 0; 
	bi.biYPelsPerMeter = 0; 
	bi.biClrUsed = 0; 
	bi.biClrImportant = 0; 

	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount+31)/32) * 4 * Bitmap.bmHeight ; 

	//为位图内容分配内存 
	hDib = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER)); 
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib); 
	*lpbi = bi; 

	// 处理调色板 
	hPal = GetStockObject(DEFAULT_PALETTE); 
	if (hPal) 
	{ 
		hDC = ::GetDC(NULL); 
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE); 
		RealizePalette(hDC); 
	} 

	// 获取该调色板下新的像素值 
	GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight, 
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) 
		+dwPaletteSize, 
		(LPBITMAPINFO ) 
		lpbi, DIB_RGB_COLORS); 

	//恢复调色板 
	if (hOldPal) 
	{ 
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE); 
		RealizePalette(hDC); 
		::ReleaseDC(NULL, hDC); 
	} 

	//创建位图文件 
	fh = CreateFile(lpFileName, GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL); 

	if (fh == INVALID_HANDLE_VALUE) 
		return FALSE; 

	// 设置位图文件头 
	bmfHdr.bfType = 0x4D42; // "BM" 
	dwDIBSize = sizeof(BITMAPFILEHEADER) 
		+ sizeof(BITMAPINFOHEADER) 
		+ dwPaletteSize + dwBmBitsSize; 
	bmfHdr.bfSize = dwDIBSize; 
	bmfHdr.bfReserved1 = 0; 
	bmfHdr.bfReserved2 = 0; 
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) 
		+ (DWORD)sizeof(BITMAPINFOHEADER) 
		+ dwPaletteSize; 

	// 写入位图文件头 
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL); 

	// 写入位图文件其余内容 
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, 
		&dwWritten, NULL); 

	//清除 
	GlobalUnlock(hDib); 
	GlobalFree(hDib); 
	CloseHandle(fh); 

	return TRUE; 
}


size_t g_f_wctou8(char * dest_str, const wchar_t src_wchar)
{
	int count_bytes = 0;
	wchar_t byte_one = 0, byte_other = 0x3f; // 用于位与运算以提取位值0x3f--->00111111
	unsigned char utf_one = 0, utf_other = 0x80; // 用于"位或"置标UTF-8编码0x80--->1000000
	wchar_t tmp_wchar = L'0'; // 用于宽字符位置析取和位移(右移位)
	unsigned char tmp_char = L'0';
	if (!src_wchar)//
		return (size_t)-1;
	for (;;) // 检测字节序列长度
	{
		if (src_wchar <= 0x7f){ // <=01111111
			count_bytes = 1; // ASCII字符: 0xxxxxxx( ~ 01111111)
			byte_one = 0x7f; // 用于位与运算, 提取有效位值, 下同
			utf_one = 0x0;
			break;
		}
		if ((src_wchar > 0x7f) && (src_wchar <= 0x7ff)){ // <=0111,11111111
			count_bytes = 2; // 110xxxxx 10xxxxxx[1](最多个位, 简写为*1)
			byte_one = 0x1f; // 00011111, 下类推(1位的数量递减)
			utf_one = 0xc0; // 11000000
			break;
		}
		if ((src_wchar > 0x7ff) && (src_wchar <= 0xffff)){ //0111,11111111<=11111111,11111111
			count_bytes = 3; // 1110xxxx 10xxxxxx[2](MaxBits: 16*1)
			byte_one = 0xf; // 00001111
			utf_one = 0xe0; // 11100000
			break;
		}
		if ((src_wchar > 0xffff) && (src_wchar <= 0x1fffff)){ //对UCS-4的支持..
			count_bytes = 4; // 11110xxx 10xxxxxx[3](MaxBits: 21*1)
			byte_one = 0x7; // 00000111
			utf_one = 0xf0; // 11110000
			break;
		}
		if ((src_wchar > 0x1fffff) && (src_wchar <= 0x3ffffff)){
			count_bytes = 5; // 111110xx 10xxxxxx[4](MaxBits: 26*1)
			byte_one = 0x3; // 00000011
			utf_one = 0xf8; // 11111000
			break;
		}
		if ((src_wchar > 0x3ffffff) && (src_wchar <= 0x7fffffff)){
			count_bytes = 6; // 1111110x 10xxxxxx[5](MaxBits: 31*1)
			byte_one = 0x1; // 00000001
			utf_one = 0xfc; // 11111100
			break;
		}
		return (size_t)-1; // 以上皆不满足则为非法序列
	}
	// 以下几行析取宽字节中的相应位, 并分组为UTF-8编码的各个字节
	tmp_wchar = src_wchar;
	for (int i = count_bytes; i > 1; i--)
	{ // 一个宽字符的多字节降序赋值
		tmp_char = (unsigned char)(tmp_wchar & byte_other);///后位与byte_other 00111111
		dest_str[i - 1] = (tmp_char | utf_other);/// 在前面加----跟或
		tmp_wchar >>= 6;//右移位
	}
	//这个时候i=1
	//对UTF-8第一个字节位处理，
	//第一个字节的开头"1"的数目就是整个串中字节的数目
	tmp_char = (unsigned char)(tmp_wchar & byte_one);//根据上面附值得来，有效位个数
	dest_str[0] = (tmp_char | utf_one);//根据上面附值得来1的个数
	// 位值析取分组__End!
	return count_bytes;
}

CString UTF8ToUnicode(const char* UTF8)
{
	CString strUnicode;        //返回值
	if (UTF8 == NULL)
		return strUnicode;

	DWORD dwUnicodeLen;        //转换后Unicode的长度
	TCHAR *pwText;            //保存Unicode的指针
	
	//获得转换后的长度，并分配内存
	dwUnicodeLen = MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, NULL, 0);
	pwText = new TCHAR[dwUnicodeLen];
	if (!pwText)
	{
		return strUnicode;
	}
	//转为Unicode
	MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, pwText, dwUnicodeLen);
	//转为CString
	strUnicode.Format(_T("%s"), pwText);
	//清除内存
	delete[]pwText;
	//返回转换好的Unicode字串
	return strUnicode;
}

std::string UnicodeToUTF8(CString& wstr)
{
	wchar_t wc = L'1';
	char c[10] = "1";//申请一个缓存
	size_t r = 0; //size_t unsigned integer Result of sizeof operator
	int i = 0;
	string sRet;
	
	for (i = 0; i < wstr.GetLength(); i++)
	{
		wc = wstr.GetAt(i);//得到一个宽字符
		r = g_f_wctou8(c, wc);//将一个宽字符按UTF-8格式转换到p地址
		if (r == -1)//出错判断
			AfxMessageBox(_T("wcs_to_pchar error"));
		sRet.push_back(c[0]);//第一个值附给p
		if (r > 1)
		{
			for (size_t x = 1; x < r; x++)
			{
				sRet.push_back(c[x]);//第一个值附给p
			}
		}
	}
	
	return sRet;
}

AFX_EXT_API void ParseHotKey(DWORD hotkey, DWORD& wVirtualKeyCode, DWORD& wModifiers)
{
	wVirtualKeyCode = LOBYTE(hotkey);
	DWORD modifiertmp = HIBYTE(hotkey);
	wModifiers = 0;

	if (modifiertmp & HOTKEYF_SHIFT)
	{
		wModifiers &= MOD_SHIFT;
	}
	if (modifiertmp & HOTKEYF_CONTROL)
	{
		wModifiers &= MOD_CONTROL;
	}
	if (modifiertmp & HOTKEYF_ALT)
	{
		wModifiers &= MOD_ALT;
	}
}

AFX_EXT_API CString FormatTime(UINT t)
{
	CString szText, szRet;
	szText.Format(_T("%u"), t);
	szRet.Format(_T("%s:%s:%s.%s"), szText.Left(2), szText.Mid(2, 2), szText.Mid(4, 2), szText.Right(3));
	return szRet;
}

AFX_EXT_API double PriceTrans(double price)
{
	return price / 10000.0;
}
