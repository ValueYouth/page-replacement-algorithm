#pragma once
#include "afxcmn.h"

#include "MyFrame.h"
//#include "PageReplace.h"
// OPT�㷨�Ľṹ��
typedef struct QUEUE
	{
		int* pBase ;
		int  front ;
		int  rear  ;
	} QUEUE ;
/*
// FIFO�㷨�Ľṹ��
typedef struct QUEUE
	{
		int* pBase ;
		int  front ;
		int  rear  ;
	} QUEUEFIFO ;
*/
// LRU�㷨�Ľṹ��
typedef struct LRU  
{  
    int data;  
    int time; //�ƴ���  
} LRU ;
typedef struct TEMP
	{
		LRU* pBase ;
		int  front ;
		int  rear  ;
	} QUEUELRU ;

// LFU�㷨�Ľṹ��
typedef struct LFU  
{  
    int data;  
    int time; //�ƴ���  
} LFU ;
typedef struct TEMP1
	{
		LFU* pBase ;
		int  front ;
		int  rear  ;
	} QUEUELFU ;

// CRunPro �Ի���

class CRunPro : public CDialog
{
	DECLARE_DYNAMIC(CRunPro)

public:
	CRunPro(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRunPro();

// �Ի�������
	enum { IDD = IDD_RUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedReturnmain();
	CListCtrl m_wndListOPT;
	CListCtrl m_wndListFIFO;
	CListCtrl m_wndListLRU;
	CListCtrl m_wndListLFU;
	afx_msg void OnBnClickedStartrun();

	static DWORD WINAPI OPTProc  (LPVOID lpParameter) ; // ���������㷨�߳�
	static DWORD WINAPI FIFOProc (LPVOID lpParameter) ; // �����Ƚ��ȳ��㷨�߳�
	static DWORD WINAPI LRUProc  (LPVOID lpParameter) ; // ����������δʹ���㷨�߳�
	static DWORD WINAPI LFUProc  (LPVOID lpParameter) ; // ��������ʹ���㷨�߳�

	CMyFrame* dlg ;
//	CPageReplace* temp ;
	afx_msg void OnBnClickedSuspend();

	bool m_bFlag ;
	CString strContent ;

public:
//	int m_iLen ;
	// OPT�㷨����غ���
	void InitQueue (QUEUE *pQ) ;	
	bool QueueEmpty (QUEUE *pQ) ;	
	bool QueueFull (QUEUE *pQ) ;	
	bool EnQueue (QUEUE *pQ, int val) ;	
	bool SameQueue (QUEUE *pQ, int num) ;	  //�ж϶�������û�кͽ�Ҫ������е������ͬ 
	void Replace1 (QUEUE *pQ, int* , int ) ; // ����û��㷨

	// FIFO�㷨����غ���
	bool DeQueue (QUEUE* pQ) ;
	bool Replace2 (QUEUE *pQ, int*) ;        // �Ƚ��ȳ��û��㷨

	// LRU�㷨����غ���
	void InitQueueLRU (QUEUELRU *pQ) ;
	bool QueueEmptyLRU (QUEUELRU *pQ) ;
	bool QueueFullLRU (QUEUELRU *pQ) ;
	bool EnQueueLRU (QUEUELRU *pQ, int val) ;
	bool SameQueueLRU (QUEUELRU *pQ, int num) ;
	bool AddTime (QUEUELRU *pQ) ;				// ����һ�����ݵĴ���
	void SetTimeZero (QUEUELRU *pQ, int val) ; // �������Ԫ�������Ԫ����ͬ����������Ϊ0
	int  FindBigTime (QUEUELRU *pQ) ;			// �ҵ�������������
	void Replace3 (QUEUELRU *pQ, int ) ;		// ������δʹ���û��㷨

	void InitQueueLFU (QUEUELFU *pQ) ;		
	bool QueueFullLFU (QUEUELFU *pQ) ;	
	bool EnQueueLFU (QUEUELFU *pQ, int val) ;	
	bool SameQueueLFU (QUEUELFU *pQ, int num) ;	  //�ж϶�������û�кͽ�Ҫ������е������ͬ 
	void Replace4 (QUEUELFU *pQ, int* , int ) ; // ����ʹ���û��㷨

	int m_iOPTTime;
	int m_iLRUTime;
	int m_iLFUTime;
	int m_iFIFOTime;

	HANDLE m_handleOPT ;
	HANDLE m_handleFIFO ;
	HANDLE m_handleLRU ;
	HANDLE m_handleLFU ;
	void fSaveToTxt(CListCtrl* pList);
	afx_msg void OnBnClickedSave();
};

