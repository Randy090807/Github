/********************************************************************
	created:	2010/12/07
	created:	7:12:2010   11:03
	filename: 	Application.h
	file path:	Public
	file base:	Application
	file ext:	h
	author:		Randy
	
	purpose:	
*********************************************************************/

#pragma once


// 名称：应用程序
// 描述：负责记录应用程序的基本信息
class AFX_EXT_CLASS CApplication  
{
public:
	// 可执行文件名称(带目录)
	static CString ExeFileName();
	// 主应用程序路径,路径后没有'\'
	static CString MainDir();
	// 临时文件存放目录,路径后没有'\'
	static CString TempDir();
	// 日志文件存放目录,,路径后没有'\'
	static CString LogDir();
	// 图标文件存放目录,路径后没有'\'
	static CString ImageDir();
	// 本程序临时目录,路径后没有'\'
	static CString AppTempDir();
	// 配置文件存放目录,路径后没有'\'
	static CString ConfigDir();
};
