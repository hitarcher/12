
// Sqlite3Test.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSqlite3TestApp: 
// �йش����ʵ�֣������ Sqlite3Test.cpp
//

class CSqlite3TestApp : public CWinApp
{
public:
	CSqlite3TestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSqlite3TestApp theApp;