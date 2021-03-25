
// Sqlite3TestDlg.cpp : 实现文件
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


// CSqlite3TestDlg 消息处理程序

BOOL CSqlite3TestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码22
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


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSqlite3TestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSqlite3TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSqlite3TestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strSqlInsertCotent = "";
	strSqlInsertCotent.Format("INSERT INTO CLOTH VALUES('1','MA')");
	m_pSqldb.ExeSqlTransaction(strSqlInsertCotent.GetBuffer(0));
}


void CSqlite3TestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
