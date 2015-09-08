#pragma once
#include "afxcmn.h"

#include "MyFrame.h"
//#include "PageReplace.h"
// OPT算法的结构体
typedef struct QUEUE
	{
		int* pBase ;
		int  front ;
		int  rear  ;
	} QUEUE ;
/*
// FIFO算法的结构体
typedef struct QUEUE
	{
		int* pBase ;
		int  front ;
		int  rear  ;
	} QUEUEFIFO ;
*/
// LRU算法的结构体
typedef struct LRU  
{  
    int data;  
    int time; //计次数  
} LRU ;
typedef struct TEMP
	{
		LRU* pBase ;
		int  front ;
		int  rear  ;
	} QUEUELRU ;

// LFU算法的结构体
typedef struct LFU  
{  
    int data;  
    int time; //计次数  
} LFU ;
typedef struct TEMP1
	{
		LFU* pBase ;
		int  front ;
		int  rear  ;
	} QUEUELFU ;

// CRunPro 对话框

class CRunPro : public CDialog
{
	DECLARE_DYNAMIC(CRunPro)

public:
	CRunPro(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRunPro();

// 对话框数据
	enum { IDD = IDD_RUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedReturnmain();
	CListCtrl m_wndListOPT;
	CListCtrl m_wndListFIFO;
	CListCtrl m_wndListLRU;
	CListCtrl m_wndListLFU;
	afx_msg void OnBnClickedStartrun();

	static DWORD WINAPI OPTProc  (LPVOID lpParameter) ; // 声明最优算法线程
	static DWORD WINAPI FIFOProc (LPVOID lpParameter) ; // 声明先进先出算法线程
	static DWORD WINAPI LRUProc  (LPVOID lpParameter) ; // 声明最近最久未使用算法线程
	static DWORD WINAPI LFUProc  (LPVOID lpParameter) ; // 声明最少使用算法线程

	CMyFrame* dlg ;
//	CPageReplace* temp ;
	afx_msg void OnBnClickedSuspend();

	bool m_bFlag ;
	CString strContent ;

public:
//	int m_iLen ;
	// OPT算法的相关函数
	void InitQueue (QUEUE *pQ) ;	
	bool QueueEmpty (QUEUE *pQ) ;	
	bool QueueFull (QUEUE *pQ) ;	
	bool EnQueue (QUEUE *pQ, int val) ;	
	bool SameQueue (QUEUE *pQ, int num) ;	  //判断队列中有没有和将要放入队列的序号相同 
	void Replace1 (QUEUE *pQ, int* , int ) ; // 最佳置换算法

	// FIFO算法的相关函数
	bool DeQueue (QUEUE* pQ) ;
	bool Replace2 (QUEUE *pQ, int*) ;        // 先进先出置换算法

	// LRU算法的相关函数
	void InitQueueLRU (QUEUELRU *pQ) ;
	bool QueueEmptyLRU (QUEUELRU *pQ) ;
	bool QueueFullLRU (QUEUELRU *pQ) ;
	bool EnQueueLRU (QUEUELRU *pQ, int val) ;
	bool SameQueueLRU (QUEUELRU *pQ, int num) ;
	bool AddTime (QUEUELRU *pQ) ;				// 增加一个数据的次数
	void SetTimeZero (QUEUELRU *pQ, int val) ; // 若待入队元素与队中元素相同，将次数置为0
	int  FindBigTime (QUEUELRU *pQ) ;			// 找到次数最大的数字
	void Replace3 (QUEUELRU *pQ, int ) ;		// 最近最久未使用置换算法

	void InitQueueLFU (QUEUELFU *pQ) ;		
	bool QueueFullLFU (QUEUELFU *pQ) ;	
	bool EnQueueLFU (QUEUELFU *pQ, int val) ;	
	bool SameQueueLFU (QUEUELFU *pQ, int num) ;	  //判断队列中有没有和将要放入队列的序号相同 
	void Replace4 (QUEUELFU *pQ, int* , int ) ; // 最少使用置换算法

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

