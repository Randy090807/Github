
#include "stdafx.h"
#include "Utility.h"


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

AFX_EXT_API int _GetEncoderClsid( const WCHAR* format, CLSID* pClsid )
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
	HDC hDC; //�豸������ 
	int iBits; //��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ��� 
	WORD wBitCount; //λͼ��ÿ��������ռ�ֽ��� 
	DWORD dwPaletteSize=0, //�����ɫ���С�� λͼ�������ֽڴ�С ��λͼ�ļ���С �� д���ļ��ֽ��� 
		dwBmBitsSize, 
		dwDIBSize, dwWritten; 
	BITMAP Bitmap; //λͼ���Խṹ 
	BITMAPFILEHEADER bmfHdr; //λͼ�ļ�ͷ�ṹ 
	BITMAPINFOHEADER bi; //λͼ��Ϣͷ�ṹ 
	LPBITMAPINFOHEADER lpbi; //ָ��λͼ��Ϣͷ�ṹ 

	HANDLE fh, hDib, hPal,hOldPal=NULL; //�����ļ��������ڴ�������ɫ���� 

	//����λͼ�ļ�ÿ��������ռ�ֽ��� 
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

	//�����ɫ���С 
	if (wBitCount <= 8) 
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD); 

	//����λͼ��Ϣͷ�ṹ 
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

	//Ϊλͼ���ݷ����ڴ� 
	hDib = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER)); 
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib); 
	*lpbi = bi; 

	// �����ɫ�� 
	hPal = GetStockObject(DEFAULT_PALETTE); 
	if (hPal) 
	{ 
		hDC = ::GetDC(NULL); 
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE); 
		RealizePalette(hDC); 
	} 

	// ��ȡ�õ�ɫ�����µ�����ֵ 
	GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight, 
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) 
		+dwPaletteSize, 
		(LPBITMAPINFO ) 
		lpbi, DIB_RGB_COLORS); 

	//�ָ���ɫ�� 
	if (hOldPal) 
	{ 
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE); 
		RealizePalette(hDC); 
		::ReleaseDC(NULL, hDC); 
	} 

	//����λͼ�ļ� 
	fh = CreateFile(lpFileName, GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL); 

	if (fh == INVALID_HANDLE_VALUE) 
		return FALSE; 

	// ����λͼ�ļ�ͷ 
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

	// д��λͼ�ļ�ͷ 
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL); 

	// д��λͼ�ļ��������� 
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, 
		&dwWritten, NULL); 

	//��� 
	GlobalUnlock(hDib); 
	GlobalFree(hDib); 
	CloseHandle(fh); 

	return TRUE; 
}