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


// ���ƣ�Ӧ�ó���
// �����������¼Ӧ�ó���Ļ�����Ϣ
class AFX_EXT_CLASS CApplication  
{
public:
	// ��ִ���ļ�����(��Ŀ¼)
	static CString ExeFileName();
	// ��Ӧ�ó���·��,·����û��'\'
	static CString MainDir();
	// ��ʱ�ļ����Ŀ¼,·����û��'\'
	static CString TempDir();
	// ��־�ļ����Ŀ¼,,·����û��'\'
	static CString LogDir();
	// ͼ���ļ����Ŀ¼,·����û��'\'
	static CString ImageDir();
	// ��������ʱĿ¼,·����û��'\'
	static CString AppTempDir();
	// �����ļ����Ŀ¼,·����û��'\'
	static CString ConfigDir();
};
