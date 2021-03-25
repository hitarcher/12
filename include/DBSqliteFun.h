#if !defined(AFX_DBSQLITEFUN_H__DC7062D9_6FF6_4E17_BBD9_87ECF348542B__INCLUDED_)
#define AFX_DBSQLITEFUN_H__DC7062D9_6FF6_4E17_BBD9_87ECF348542B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBSqliteFun.h : header file
//
#include <sqlite3.h>

/////////////////////////////////////////////////////////////////////////////
typedef int (*Sqlite3_Callback)(void*,int,char**, char**);

class CDBSqliteFun
{
// Construction
public:
	CDBSqliteFun();
	virtual ~CDBSqliteFun();
private:
	sqlite3* m_pSqliteDB;
	char*	 m_pError;		//�����ݿ��������
	char*	 m_pSqlError;	//רִָ��sql������
	
public:
	int OpenDatabase(CString strDbPath);	///����Ϊ0 ��ʾ�򿪳ɹ�
	int CloseDatabase();					///����0 ��ʾ�رճɹ�
	int ExeSqlTransaction(const char *pSql);		///ִ��sql���
	int GetTable(int iTableType);				///��ȡ�����Ŷӻ���ر��
public:
	char* GetLastError() {return m_pError;}
	char* GetLastSqlError() {return m_pSqlError;}
	const char* Sqlite3_errmsg() {return sqlite3_errmsg(m_pSqliteDB);}
	int  Sqlite3_get_table(const char *zSql, char ***pazResult, int *pnRow, int *pnColumn);
	int Sqlite3_prepare(const char *zSql,  int nByte,  sqlite3_stmt **ppStmt,  const char **pzTail);

protected:

};

#endif // !defined(AFX_DBSQLITEFUN_H__DC7062D9_6FF6_4E17_BBD9_87ECF348542B__INCLUDED_)
