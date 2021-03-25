// DBSqliteFun.cpp : implementation file
//

#include "stdafx.h"
#include "DBSqliteFun.h"
#include "FileStruct.h"
#include "../����/Config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

int GBKToUTF8(unsigned char * lpGBKStr,unsigned char * lpUTF8Str,int nUTF8StrLen)
{
    wchar_t * lpUnicodeStr = NULL;
    int nRetLen = 0;
	
	//���GBK�ַ���ΪNULL������˳�
    if(!lpGBKStr) return 0;
	
	//��ȡת����Unicode���������Ҫ���ַ��ռ䳤��
    nRetLen = ::MultiByteToWideChar(CP_ACP,0,(char *)lpGBKStr,-1,NULL,NULL);  
	//ΪUnicode�ַ����ռ�
    lpUnicodeStr = new WCHAR[nRetLen + 1];  
	//ת����Unicode����
    nRetLen = ::MultiByteToWideChar(CP_ACP,0,(char *)lpGBKStr,-1,lpUnicodeStr,nRetLen);
	//ת��ʧ��������˳�
    if(!nRetLen) return 0;
	
	//��ȡת����UTF8���������Ҫ���ַ��ռ䳤��
    nRetLen = ::WideCharToMultiByte(CP_UTF8,0,lpUnicodeStr,-1,NULL,0,NULL,NULL);  
    
	if(!lpUTF8Str)  //���������Ϊ���򷵻�ת������Ҫ�Ŀռ��С
    {
        if(lpUnicodeStr) delete []lpUnicodeStr;
        return nRetLen;
    }
    
    if(nUTF8StrLen < nRetLen)  //���������������Ȳ������˳�
    {
        if(lpUnicodeStr) delete []lpUnicodeStr;
        return 0;
    }
	
	//ת����UTF8����
    nRetLen = ::WideCharToMultiByte(CP_UTF8,0,lpUnicodeStr,-1,(char *)lpUTF8Str,nUTF8StrLen,NULL,NULL);  
    
    if(lpUnicodeStr) delete []lpUnicodeStr;
    
    return nRetLen;
}

CDBSqliteFun::CDBSqliteFun()
{
	m_pSqliteDB = NULL;
}

CDBSqliteFun::~CDBSqliteFun()
{
	CloseDatabase();
}

int CDBSqliteFun::OpenDatabase(CString strDbPath)
{
	char szpath[1024] = {0};
	GBKToUTF8((unsigned char*)strDbPath.GetBuffer(0),(unsigned char*)szpath,sizeof(szpath));
	return sqlite3_open(szpath,&m_pSqliteDB);
}

int CDBSqliteFun::CloseDatabase()
{
	return sqlite3_close(m_pSqliteDB);;
}

int CDBSqliteFun::ExeSqlTransaction(const char *pSql)
{
	int ret = 0;
	ret  = sqlite3_exec(m_pSqliteDB, "begin transaction", 0, 0, &m_pError); //��ʼһ������
	if(ret != SQLITE_OK)
	{
		return ret;
	}
	ret = sqlite3_exec(m_pSqliteDB, pSql, 0, 0, &m_pSqlError);
	if(ret != SQLITE_OK)
	{
		sqlite3_exec(m_pSqliteDB, "rollback transaction", 0, 0, &m_pError); //�ع�����
		return ret;
	}
	return sqlite3_exec( m_pSqliteDB, "commit transaction", 0, 0, &m_pError); //�ύ����
}

int CDBSqliteFun::Sqlite3_get_table(const char *zSql, char ***pazResult, int *pnRow, int *pnColumn)
{
	return sqlite3_get_table(m_pSqliteDB,zSql,pazResult,pnRow,pnColumn,&m_pSqlError);
}

int CDBSqliteFun::Sqlite3_prepare(const char *zSql,  int nByte,  sqlite3_stmt **ppStmt,  const char **pzTail)
{
	return sqlite3_prepare(m_pSqliteDB,zSql,nByte,ppStmt,pzTail);
}
