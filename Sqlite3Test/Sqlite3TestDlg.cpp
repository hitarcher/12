
// Sqlite3TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sqlite3Test.h"
#include "Sqlite3TestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CommTbl.h"
#include <iostream>
using namespace std;

#include "json.hpp"
using json = nlohmann::json;




CSqlite3TestDlg::CSqlite3TestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SQLITE3TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSqlite3TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSqlite3TestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSqlite3TestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSqlite3TestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSqlite3TestDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CSqlite3TestDlg ��Ϣ�������

BOOL CSqlite3TestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������22
	if (CheckFileExist("cloth.db") == FALSE)
	{
		m_pSqldb.OpenDatabase(GetFullPath("cloth.db"));
// 		strSqlUpDate.Format("UPDATE MSGRECORD SET UPLOAD=1 WHERE MSGID=%s", sMsgInfo.strMsgId);
// 		strSqlInsert.Format("INSERT INTO MSGRECORD(MSGID,BANKORSTAFF,MSGTYPE,MSGCONTENT,MSGNAME,WORKID,MSGPHONE,UPLOAD,EXAMINE,MSGTIME) \
// 				VALUES(%s,'%s','%s','%s','%s','%s','%s',0,0,'%s')",
// 			sMsgInfo.strMsgId, sMsgInfo.strBankOrStaff, sMsgInfo.strMsgType, sMsgInfo.strMsgContent,
// 			sMsgInfo.strMsgName, sMsgInfo.strWorkId, sMsgInfo.strMsgPhone, sMsgInfo.strMsgTime);
		CString stSqlCreateTable = "";
		stSqlCreateTable.Format("CREATE TABLE CLOTH (ID INT,SEX VARCHAR(255))");
		m_pSqldb.ExeSqlTransaction(stSqlCreateTable.GetBuffer(0));
	}
	else
	{
		m_pSqldb.OpenDatabase(GetFullPath("cloth.db"));
	}


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSqlite3TestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSqlite3TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSqlite3TestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strSqlInsertCotent = "";
	strSqlInsertCotent.Format("INSERT INTO CLOTH VALUES('1','MA')");
	m_pSqldb.ExeSqlTransaction(strSqlInsertCotent.GetBuffer(0));
}


void CSqlite3TestDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strSqlDeleteCotent = "";
	strSqlDeleteCotent.Format("DELETE FROM CLOTH WHERE ID =1 OR SEX = 'MA'");
	m_pSqldb.ExeSqlTransaction(strSqlDeleteCotent.GetBuffer(0));

}

struct MsgInfo
{
	CString strMsgId;
	CString strBankOrStaff;
	CString strMsgType;
	CString strMsgContent;
	CString strMsgPhone;
	CString strWorkId;
	CString strMsgName;
	CString strMsgTime;
};
void CSqlite3TestDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strSqlGetCotent = "";
	strSqlGetCotent.Format("SELECT DISTINCT * FROM CLOTH");
	CCommTbl<CCommTbl<std::string>> SqlList = m_pSqldb.GetTable(strSqlGetCotent.GetBuffer(0));
	json jShowMsg = nullptr;
	if (SqlList.size() > 0)
	{
		json jBankMsg;
		json jSplicing;

		for (int i = 0; i < SqlList.size(); ++i)
		{
// 			jSplicing["CONTENT"] = SqlList[i][3].<std::string>().c_str();
// 			jSplicing["RECIPIENT"] = SqlList[i][4].c_str();
// 			jSplicing["TIME"] = SqlList[i][9].c_str();
// 
			jBankMsg.push_back(jSplicing);
		}

		jShowMsg["data"]["bankLeaveList"] = jBankMsg;
	}

}
