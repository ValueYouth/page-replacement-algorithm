#pragma once
#include "afxcmn.h"


// CMyFrame �Ի���

class CMyFrame : public CDialog
{
	DECLARE_DYNAMIC(CMyFrame)

public:
	CMyFrame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyFrame();

// �Ի�������
	enum { IDD = IDD_MYFRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit5();
	int m_iStayCount;
	CString m_strAllPage;
//	CString m_strGetTime;
//	CString m_strBreakTime;
//	CString m_strFastTime;
	virtual BOOL OnInitDialog();
	CListCtrl m_wndListCtrl;
	int m_iMax;
	int m_iMin;
	int m_iPageNum;
    int m_iTemp[1000] ; //�������飬�洢������Լ������ҳ������
	afx_msg void OnBnClickedResolve();
	afx_msg void OnBnClickedRandom();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedListctrl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangePagenum();
	BOOL m_bFastYN;
	int m_iBreakTime;
	int m_iFastTime;
	int m_iGetTime;
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeStaycount();
	afx_msg void OnBnClickedButton2();
};
