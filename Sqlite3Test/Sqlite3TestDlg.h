
// Sqlite3TestDlg.h : 头文件
//

#pragma once
#include "SqliteFun.h"
#include "CommonFun.h"
// CSqlite3TestDlg 对话框
class CSqlite3TestDlg : public CDialogEx
{
// 构造
public:
	CSqlite3TestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SQLITE3TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CSqliteFun m_pSqldb;																		 // 数据库类

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
