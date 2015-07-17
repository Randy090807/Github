#pragma once

#include <fstream>
using namespace std;

class AFX_EXT_CLASS CLogger
{
protected:
	CLogger();
	~CLogger();
public:
	static CLogger* Inst();
	void WriteB( const char* content, int len );
	void Write( char* content, ... );
	
protected:
	void WriteHeader();
	fstream	_f;
};