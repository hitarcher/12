
// Sqlite3TestDlg.h : ͷ�ļ�
//

#pragma once
#include "SqliteFun.h"
#include "CommonFun.h"
// CSqlite3TestDlg �Ի���
class CSqlite3TestDlg : public CDialogEx
{
// ����
public:
	CSqlite3TestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SQLITE3TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CSqliteFun m_pSqldb;																		 // ���ݿ���

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
