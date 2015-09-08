// RunPro.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_OS.h"
#include "RunPro.h"
#include "afxdialogex.h"

#include "MyFrame.h"
//#include "PageReplace.h"

// CRunPro 对话框

IMPLEMENT_DYNAMIC(CRunPro, CDialog)

CRunPro::CRunPro(CWnd* pParent /*=NULL*/)
	: CDialog(CRunPro::IDD, pParent)
	, m_iOPTTime(0)
	, m_iLRUTime(0)
	, m_iLFUTime(0)
	, m_iFIFOTime(0)
{
//	dlg->m_iStayCount = dlg->m_iStayCount ;
	strContent = "" ;
}

CRunPro::~CRunPro()
{
}

void CRunPro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPTLIST, m_wndListOPT);
	DDX_Control(pDX, IDC_FIFOLIST, m_wndListFIFO);
	DDX_Control(pDX, IDC_LRULIST, m_wndListLRU);
	DDX_Control(pDX, IDC_LFULIST, m_wndListLFU);
	DDX_Text(pDX, IDC_OPTTIME, m_iOPTTime);
	DDX_Text(pDX, IDC_LRUTIME, m_iLRUTime);
	DDX_Text(pDX, IDC_LFUTIME, m_iLFUTime);
	DDX_Text(pDX, IDC_FIFOTIME, m_iFIFOTime);
}


BEGIN_MESSAGE_MAP(CRunPro, CDialog)
	ON_BN_CLICKED(IDC_RETURNMAIN, &CRunPro::OnBnClickedReturnmain)
	ON_BN_CLICKED(IDC_STARTRUN, &CRunPro::OnBnClickedStartrun)
	ON_BN_CLICKED(IDC_SUSPEND, &CRunPro::OnBnClickedSuspend)
	ON_BN_CLICKED(IDC_SAVE, &CRunPro::OnBnClickedSave)
END_MESSAGE_MAP()


// CRunPro 消息处理程序


void CRunPro::OnBnClickedReturnmain()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	CMyFrame dlg ;
	dlg.DoModal() ;

}


void CRunPro::OnBnClickedStartrun()
{
	// TODO: 在此添加控件通知处理程序代码
	m_wndListOPT.InsertColumn (0, _T("Project"), LVCFMT_LEFT, 50) ;
	m_wndListOPT.SetExtendedStyle (LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT) ;
	m_wndListFIFO.InsertColumn (0, _T("Project"), LVCFMT_LEFT, 50) ;
	m_wndListFIFO.SetExtendedStyle (LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT) ;
	m_wndListLRU.InsertColumn (0, _T("Project"), LVCFMT_LEFT, 50) ;
	m_wndListLRU.SetExtendedStyle (LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT) ;
	m_wndListLFU.InsertColumn (0, _T("Project"), LVCFMT_LEFT, 50) ;
	m_wndListLFU.SetExtendedStyle (LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT) ;

	int m_iLength = dlg->m_iPageNum ;

	for (int i = 0; i < m_iLength; i++)
	{
		CString str1 ;
		str1.Format (_T("%d"), dlg->m_iTemp[i]) ;

		m_wndListOPT.InsertColumn (i+1, str1, LVCFMT_LEFT, 25) ;
		m_wndListFIFO.InsertColumn (i+1, str1, LVCFMT_LEFT, 25) ;
		m_wndListLRU.InsertColumn (i+1, str1, LVCFMT_LEFT, 25) ;
		m_wndListLFU.InsertColumn (i+1, str1, LVCFMT_LEFT, 25) ;
	}

	for (int j = 0; j < dlg->m_iStayCount; j++)
	{
		CString str2 ;
		str2.Format (_T("Block%d"), j + 1) ;
		// OPT
		m_wndListOPT.InsertItem (j, str2) ;

		if (j == dlg->m_iStayCount - 1)
		{
			m_wndListOPT.InsertItem (j + 1, _T("Hit ?")) ;
			m_wndListOPT.InsertItem (j + 2, _T("UseTime")) ;
		}
		// FIFO
		m_wndListFIFO.InsertItem (j, str2) ;

		if (j == dlg->m_iStayCount - 1)
		{
			m_wndListFIFO.InsertItem (j + 1, _T("Hit ?")) ;
			m_wndListFIFO.InsertItem (j + 2, _T("UseTime")) ;
		}
		// LRU
		m_wndListLRU.InsertItem (j, str2) ;

		if (j == dlg->m_iStayCount - 1)
		{
			m_wndListLRU.InsertItem (j + 1, _T("Hit ?")) ;
			m_wndListLRU.InsertItem (j + 2, _T("UseTime")) ;
		}
		// LFU
		m_wndListLFU.InsertItem (j, str2) ;

		if (j == dlg->m_iStayCount - 1)
		{
			m_wndListLFU.InsertItem (j + 1, _T("Hit ?")) ;
			m_wndListLFU.InsertItem (j + 2, _T("UseTime")) ;
		}
	}

//	m_wndListOPT.InsertItem (j + 1, _T("是否命中")) ;
//	m_wndListOPT.InsertItem (j + 2, _T("所用时间")) ;

	 m_handleOPT = CreateThread (NULL, NULL, CRunPro::OPTProc, (LPVOID)this, NULL, NULL) ;
	 m_handleFIFO = CreateThread (NULL, NULL, CRunPro::FIFOProc, (LPVOID)this, NULL, NULL) ;
	 m_handleLRU = CreateThread (NULL, NULL, CRunPro::LRUProc, (LPVOID)this, NULL, NULL) ;
	 m_handleLFU = CreateThread (NULL, NULL, CRunPro::LFUProc, (LPVOID)this, NULL, NULL) ;
}

DWORD WINAPI CRunPro::OPTProc  (LPVOID lpParameter)
{
	CRunPro* dlgOPT = (CRunPro*)lpParameter ;
	CMyFrame* myframe_opt = dlgOPT->dlg ;
//	m_idlg->m_iStayCount = myframe->m_iPageNum + 1 ;
	QUEUE Q ;
	dlgOPT->InitQueue(&Q) ;

	int m_iAllTime = 0 ;	// 记录总时间
	int m_iNum    = 0 ;  // 记录缺页的次数
	int m_iLength = myframe_opt->m_iPageNum ;
    int j, k = 1;
	for(int i = 0; i < m_iLength; i++)
	{
		CString str1, str2 ;

		if (!((dlgOPT->QueueFull)(&Q)) && !((dlgOPT->SameQueue)(&Q, myframe_opt->m_iTemp[i])))
		{
			dlgOPT->EnQueue(&Q, myframe_opt->m_iTemp[i]) ;
			for (j = 0; j < myframe_opt->m_iStayCount; j++)
			{
				if (Q.pBase[j] < 0)
				{
					dlgOPT->m_wndListOPT.SetItemText (j, k, _T("")) ;
				}
				else
				{
					str1.Format (_T("%d"), Q.pBase[j]) ;
					dlgOPT->m_wndListOPT.SetItemText (j, k, str1) ;
				}
			}
			dlgOPT->m_wndListOPT.SetItemText (j, k, _T("N")) ;

			j++ ;

			int m_iTime = myframe_opt->m_iBreakTime + 3 * myframe_opt->m_iGetTime ;
			str2.Format (_T("%d"), m_iTime) ;
			dlgOPT->m_wndListOPT.SetItemText (j, k, str2) ;

			m_iAllTime += m_iTime ;

			m_iNum++ ;
		}
		else if (((dlgOPT->QueueFull)(&Q)) && !((dlgOPT->SameQueue)(&Q, myframe_opt->m_iTemp[i])))
		{
			dlgOPT->Replace1 (&Q, myframe_opt->m_iTemp, i) ;	

			for (j = 0; j < myframe_opt->m_iStayCount; j++)
			{
					str1.Format (_T("%d"), Q.pBase[j]) ;
					dlgOPT->m_wndListOPT.SetItemText (j, k, str1) ;
			}
			dlgOPT->m_wndListOPT.SetItemText (j, k, _T("N")) ;

			j++ ;

			int m_iTime1 = myframe_opt->m_iBreakTime + 3 * myframe_opt->m_iGetTime ;
			str2.Format (_T("%d"), m_iTime1) ;
			dlgOPT->m_wndListOPT.SetItemText (j, k, str2) ;

			m_iAllTime += m_iTime1 ;

			m_iNum++ ;
		}
		else
		{
			j = myframe_opt->m_iStayCount ;
			dlgOPT->m_wndListOPT.SetItemText (j, k, _T("Y")) ;

			j++ ;
			if (myframe_opt->m_bFastYN)
			{
				int m_iTime2 = myframe_opt->m_iFastTime + myframe_opt->m_iGetTime ;
				str2.Format (_T("%d"), m_iTime2) ;
				dlgOPT->m_wndListOPT.SetItemText (j, k, str2) ;

				m_iAllTime += m_iTime2 ;
			}
			else
			{
				int m_iTime3 =  myframe_opt->m_iGetTime * 2;
				str2.Format (_T("%d"), m_iTime3) ;
				dlgOPT->m_wndListOPT.SetItemText (j, k, str2) ;

				m_iAllTime += m_iTime3 ;
			}
		}

		k++;
		Sleep (750) ;
	}

	// 所有的时间
	CString str3 ;
	str3.Format (_T("%d"), m_iAllTime) ;
	dlgOPT->GetDlgItem (IDC_OPTTIME)->SetWindowTextW (str3) ;

	// 中断的次数
	CString str4 ;
	str4.Format (_T("%d"), m_iNum) ;
	dlgOPT->GetDlgItem (IDC_OPTBREAKTIME)->SetWindowTextW (str4) ;

	// 命中率
	CString str5 ;
	str5.Format (_T("%3.2f"), (1 - ((float)m_iNum / m_iLength)) * 100 ) ;
	dlgOPT->GetDlgItem (IDC_OPTGOAL)->SetWindowTextW (str5 + _T("%")) ;

	return 0 ;
}

DWORD WINAPI CRunPro::FIFOProc  (LPVOID lpParameter)
{
	CRunPro* dlgFIFO = (CRunPro*)lpParameter ;
	CMyFrame* myframe_fifo = dlgFIFO->dlg ;

	int m_iAllTime = 0 ;	// 记录总时间
	int m_iNum    = 0 ;  // 记录缺页的次数
	int m_iLength = myframe_fifo->m_iPageNum ;
    int j, k = 1;

	QUEUE fifo ;
	dlgFIFO->InitQueue (&fifo) ;

	for(int i = 0; i < m_iLength; i++)
	{
		CString str1, str2 ;

		if (!((dlgFIFO->QueueFull)(&fifo)) && !((dlgFIFO->SameQueue)(&fifo, myframe_fifo->m_iTemp[i])))
		{
			dlgFIFO->EnQueue(&fifo, myframe_fifo->m_iTemp[i]) ;
			for (j = 0; j < myframe_fifo->m_iStayCount; j++)
			{
				if (fifo.pBase[j] < 0)
				{
					dlgFIFO->m_wndListFIFO.SetItemText (j, k, _T("")) ;
				}
				else
				{
					str1.Format (_T("%d"), fifo.pBase[j]) ;
					dlgFIFO->m_wndListFIFO.SetItemText (j, k, str1) ;
				}
			}
			dlgFIFO->m_wndListFIFO.SetItemText (j, k, _T("N")) ;

			j++ ;

			int m_iTime = myframe_fifo->m_iBreakTime + 3 * myframe_fifo->m_iGetTime ;
			str2.Format (_T("%d"), m_iTime) ;
			dlgFIFO->m_wndListFIFO.SetItemText (j, k, str2) ;

			m_iAllTime += m_iTime ;

			m_iNum++ ;
		}
		else if (((dlgFIFO->QueueFull)(&fifo)) && !((dlgFIFO->SameQueue)(&fifo, myframe_fifo->m_iTemp[i])))
		{
			dlgFIFO->DeQueue (&fifo) ;
			dlgFIFO->EnQueue (&fifo, myframe_fifo->m_iTemp[i]) ;

			int m_iHead = fifo.front ;
			for (j = 0; j < myframe_fifo->m_iStayCount; j++)
			{
				 str2.Format(_T("%d"), fifo.pBase[m_iHead]) ;
				 dlgFIFO->m_wndListFIFO.SetItemText (j, k, str2) ;

				 m_iHead = (m_iHead + 1) % (myframe_fifo->m_iStayCount + 1) ;
			}
			dlgFIFO->m_wndListFIFO.SetItemText (j, k, _T("N")) ;

			j++ ;
			int m_iTime1 = myframe_fifo->m_iBreakTime + 3 * myframe_fifo->m_iGetTime ;
			str2.Format (_T("%d"), m_iTime1) ;
			dlgFIFO->m_wndListFIFO.SetItemText (j, k, str2) ;

			m_iAllTime += m_iTime1 ;

			m_iNum++ ;
		}
		else
		{
			j = myframe_fifo->m_iStayCount ;
			dlgFIFO->m_wndListFIFO.SetItemText (j, k, _T("Y")) ;

			j++ ;
			if (myframe_fifo->m_bFastYN)
			{
				int m_iTime2 = myframe_fifo->m_iFastTime + myframe_fifo->m_iGetTime ;
				str2.Format (_T("%d"), m_iTime2) ;
				dlgFIFO->m_wndListFIFO.SetItemText (j, k, str2) ;

				m_iAllTime += m_iTime2 ;
			}
			else
			{
				int m_iTime3 =  myframe_fifo->m_iGetTime * 2 ;
				str2.Format (_T("%d"), m_iTime3) ;
				dlgFIFO->m_wndListFIFO.SetItemText (j, k, str2) ;

				m_iAllTime += m_iTime3 ;
			}
		}

		k++;
		Sleep (750) ;
	}

	CString str3 ;
	str3.Format (_T("%d"), m_iAllTime) ;
	dlgFIFO->GetDlgItem (IDC_FIFOTIME)->SetWindowTextW (str3) ;

	// 中断的次数
	CString str4 ;
	str4.Format (_T("%d"), m_iNum) ;
	dlgFIFO->GetDlgItem (IDC_FIFOBREAKTIME)->SetWindowTextW (str4) ;

	CString str5 ;
	str5.Format (_T("%3.2f"), (1 - ((float)m_iNum / m_iLength)) * 100 ) ;
	dlgFIFO->GetDlgItem (IDC_FIFOGOAL)->SetWindowTextW (str5 + _T("%")) ;

	return 0 ;
}

DWORD WINAPI CRunPro::LRUProc  (LPVOID lpParameter)
{
	CRunPro* dlgLRU = (CRunPro*)lpParameter ;
	CMyFrame* myframe_lru = dlgLRU->dlg ;

	int m_iAllTime = 0 ;	// 记录总时间
	int m_iNum    = 0 ;  // 记录缺页的次数
	int m_iLength = myframe_lru->m_iPageNum ;
    int j, k = 1;

	QUEUELRU lru ;
	dlgLRU->InitQueueLRU (&lru) ;

	for(int i = 0; i < m_iLength; i++)
	{
		CString str1, str2 ;

		if (!((dlgLRU->QueueFullLRU)(&lru)) && !((dlgLRU->SameQueueLRU)(&lru, myframe_lru->m_iTemp[i])))
		{
			dlgLRU->EnQueueLRU (&lru, myframe_lru->m_iTemp[i]) ;
			for (j = 0; j < myframe_lru->m_iStayCount; j++)
			{
				if (lru.pBase[j].data < 0)
				{
					dlgLRU->m_wndListLRU.SetItemText (j, k, _T("")) ;
				}
				else
				{
					str1.Format (_T("%d"), lru.pBase[j].data) ;
					dlgLRU->m_wndListLRU.SetItemText (j, k, str1) ;
				}
			}
			dlgLRU->m_wndListLRU.SetItemText (j, k, _T("N")) ;

			j++ ;

			int m_iTime = myframe_lru->m_iBreakTime + 3 * myframe_lru->m_iGetTime ;
			str2.Format (_T("%d"), m_iTime) ;
			dlgLRU->m_wndListLRU.SetItemText (j, k, str2) ;

			m_iAllTime += m_iTime ;

			m_iNum++ ;
		}
		else if ((dlgLRU->QueueFullLRU(&lru)) && !((dlgLRU->SameQueueLRU)(&lru, myframe_lru->m_iTemp[i])))
		{
			dlgLRU->Replace3 (&lru, myframe_lru->m_iTemp[i] ) ;

			for (j = 0; j < myframe_lru->m_iStayCount; j++)
			{
					str1.Format (_T("%d"), lru.pBase[j].data) ;
					dlgLRU->m_wndListLRU.SetItemText (j, k, str1) ;
			}
			dlgLRU->m_wndListLRU.SetItemText (j, k, _T("N")) ;

			j++ ;

			int m_iTime1 = myframe_lru->m_iBreakTime + 3 * myframe_lru->m_iGetTime ;
			str2.Format (_T("%d"), m_iTime1) ;
			dlgLRU->m_wndListLRU.SetItemText (j, k, str2) ;

			m_iAllTime += m_iTime1 ;

			m_iNum++ ;
		}
		else
		{
			dlgLRU->SetTimeZero (&lru, myframe_lru->m_iTemp[i]) ;

			j = myframe_lru->m_iStayCount ;
			dlgLRU->m_wndListLRU.SetItemText (j, k, _T("Y")) ;

			j++ ;
			if (myframe_lru->m_bFastYN)
			{
				int m_iTime2 = myframe_lru->m_iFastTime + myframe_lru->m_iGetTime ;
				str2.Format (_T("%d"), m_iTime2) ;
				dlgLRU->m_wndListLRU.SetItemText (j, k, str2) ;

				m_iAllTime += m_iTime2 ;
			}
			else
			{
				int m_iTime3 =  myframe_lru->m_iGetTime * 2;
				str2.Format (_T("%d"), m_iTime3) ;
				dlgLRU->m_wndListLRU.SetItemText (j, k, str2) ;

				m_iAllTime += m_iTime3 ;
			}

		}

		k++;
		Sleep (750) ;

		dlgLRU->AddTime (&lru) ;
	}
	
	CString str3 ;
	str3.Format (_T("%d"), m_iAllTime) ;
	dlgLRU->GetDlgItem (IDC_LRUTIME)->SetWindowTextW (str3) ;

	// 中断的次数
	CString str4 ;
	str4.Format (_T("%d"), m_iNum) ;
	dlgLRU->GetDlgItem (IDC_LRUBREAKTIME)->SetWindowTextW (str4) ;

	CString str5 ;
	str5.Format (_T("%3.2f"), (1 - ((float)m_iNum / m_iLength)) * 100 ) ;
	dlgLRU->GetDlgItem (IDC_LRUGOAL)->SetWindowTextW (str5 + _T("%")) ;

	return 0 ;
}

DWORD WINAPI CRunPro::LFUProc  (LPVOID lpParameter)
{
	CRunPro* dlgLFU = (CRunPro*)lpParameter ;
	CMyFrame* myframe_lfu = dlgLFU->dlg ;

	int m_iAllTime = 0 ;	// 记录总时间
	int m_iNum    = 0 ;  // 记录缺页的次数
	int m_iLength = myframe_lfu->m_iPageNum ;
    int j, k = 1;

	QUEUELFU lfu ;
	dlgLFU->InitQueueLFU (&lfu) ;

	for(int i = 0; i < m_iLength; i++)
	{
		CString str1, str2 ;

		if (!((dlgLFU->QueueFullLFU)(&lfu)) && !((dlgLFU->SameQueueLFU)(&lfu, myframe_lfu->m_iTemp[i])))
		{
			dlgLFU->EnQueueLFU (&lfu, myframe_lfu->m_iTemp[i]) ;
			for (j = 0; j < myframe_lfu->m_iStayCount; j++)
			{
				if (lfu.pBase[j].data < 0)
				{
					dlgLFU->m_wndListLFU.SetItemText (j, k, _T("")) ;
				}
				else
				{
					str1.Format (_T("%d"), lfu.pBase[j].data) ;
					dlgLFU->m_wndListLFU.SetItemText (j, k, str1) ;
				}
			}
			dlgLFU->m_wndListLFU.SetItemText (j, k, _T("N")) ;

			j++ ;

			int m_iTime = myframe_lfu->m_iBreakTime + 3 * myframe_lfu->m_iGetTime ;
			str2.Format (_T("%d"), m_iTime) ;
			dlgLFU->m_wndListLFU.SetItemText (j, k, str2) ;

			m_iAllTime += m_iTime ;

			m_iNum++ ;
		}
		else if ((dlgLFU->QueueFullLFU(&lfu)) && !((dlgLFU->SameQueueLFU)(&lfu, myframe_lfu->m_iTemp[i])))
		{
			dlgLFU->Replace4 (&lfu, myframe_lfu->m_iTemp, i) ;

			for (j = 0; j < myframe_lfu->m_iStayCount; j++)
			{
					str1.Format (_T("%d"), lfu.pBase[j].data) ;
					dlgLFU->m_wndListLFU.SetItemText (j, k, str1) ;
			}
			dlgLFU->m_wndListLFU.SetItemText (j, k, _T("N")) ;

			j++ ;

			int m_iTime1 = myframe_lfu->m_iBreakTime + 3 * myframe_lfu->m_iGetTime ;
			str2.Format (_T("%d"), m_iTime1) ;
			dlgLFU->m_wndListLFU.SetItemText (j, k, str2) ;

			m_iAllTime += m_iTime1 ;

			m_iNum++ ;
		}
		else
		{
			j = myframe_lfu->m_iStayCount ;
			dlgLFU->m_wndListLFU.SetItemText (j, k, _T("Y")) ;

			j++ ;
			if (myframe_lfu->m_bFastYN)
			{
				int m_iTime2 = myframe_lfu->m_iFastTime + myframe_lfu->m_iGetTime ;
				str2.Format (_T("%d"), m_iTime2) ;
				dlgLFU->m_wndListLFU.SetItemText (j, k, str2) ;

				m_iAllTime += m_iTime2 ;
			}
			else
			{
				int m_iTime3 =  myframe_lfu->m_iGetTime * 2;
				str2.Format (_T("%d"), m_iTime3) ;
				dlgLFU->m_wndListLFU.SetItemText (j, k, str2) ;

				m_iAllTime += m_iTime3 ;
			}

		}

		k++;
		Sleep (750) ;
	}
	
	CString str3 ;
	str3.Format (_T("%d"), m_iAllTime) ;
	dlgLFU->GetDlgItem (IDC_LFUTIME)->SetWindowTextW (str3) ;

	// 中断的次数
	CString str4 ;
	str4.Format (_T("%d"), m_iNum) ;
	dlgLFU->GetDlgItem (IDC_LFUBREAKTIME)->SetWindowTextW (str4) ;

	CString str5 ;
	str5.Format (_T("%3.2f"), (1 - ((float)m_iNum / m_iLength)) * 100 ) ;
	dlgLFU->GetDlgItem (IDC_LFUGOAL)->SetWindowTextW (str5 + _T("%")) ;
	
	return 0 ;
}

void CRunPro::OnBnClickedSuspend()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bFlag)
	{
		m_bFlag = FALSE ;
		SuspendThread (m_handleOPT) ;
		SuspendThread (m_handleFIFO) ;
		SuspendThread (m_handleLRU) ;
		SuspendThread (m_handleLFU) ;
		GetDlgItem (IDC_SUSPEND)->SetWindowTextW (_T("继续")) ;
	}
	else
	{
//		AfxBeginThread ((AFX_THREADPROC)Thread1Proc, this/*, THREAD_PRIORITY_IDLE*/) ;
//		AfxBeginThread ((AFX_THREADPROC)Thread2Proc, this) ;

		m_bFlag = TRUE ;
		ResumeThread (m_handleOPT) ;
		ResumeThread (m_handleFIFO) ;
		ResumeThread (m_handleLRU) ;
		ResumeThread (m_handleLFU) ;
		GetDlgItem (IDC_SUSPEND)->SetWindowTextW (_T("暂停")) ;
	}
}

void CRunPro::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	strContent += _T("OPT：") ;
	strContent += "\r\n\r\n" ;
	fSaveToTxt(&m_wndListOPT) ;
	strContent += "\r\n" ;

	strContent += _T("FIFO：") ;
	strContent += "\r\n\r\n" ;
	fSaveToTxt(&m_wndListFIFO) ;
	strContent += "\r\n" ;

	strContent += _T("LRU：") ;
	strContent += "\r\n\r\n" ;
	fSaveToTxt(&m_wndListLRU) ;
	strContent += "\r\n" ;

	strContent += _T("LFU：") ;
	strContent += "\r\n\r\n" ;
	fSaveToTxt(&m_wndListLFU) ;

	try
	{
		CStdioFile m_cFile;

		m_cFile.Open(_T("页面置换算法.txt"), CFile::modeCreate | CFile::modeWrite |CFile::typeText | CFile::typeUnicode) ;
		m_cFile.WriteString (strContent) ;

		m_cFile.Close() ;

		
	}
	catch (CFileException* e)
	{
		e->ReportError() ;
		e->Delete() ;
	}

	MessageBox (_T("数据已保存成功，请返回主界面查看日志！"), _T("提示信息"), 
		MB_OKCANCEL | MB_ICONINFORMATION) ;
}

// 四种置换算法




void CRunPro::InitQueue (QUEUE* pQ)	//初始化队列
{
	int N = dlg->m_iStayCount + 1 ; 

    pQ->pBase = (int*)malloc(sizeof(int ) * N) ; // N为数组长度  
    pQ->front = 0 ;  
    pQ->rear  = 0 ;
}

bool CRunPro::QueueFull(QUEUE* pQ)
{
	int N = dlg->m_iStayCount+1;  

    if ((pQ->rear +1) % N == pQ->front) //循环队列
	{
        return TRUE;  
	}
    else
	{
        return FALSE;
	}
}

bool CRunPro::QueueEmpty(QUEUE* pQ) //判断队列是否是空
{
	int N = dlg->m_iStayCount + 1 ;

	if (pQ->front == pQ->rear)
	{
		return TRUE ;
	}
	else
	{
		return FALSE ;
	}
}

bool CRunPro::EnQueue (QUEUE *pQ, int val)	// 向内存中添加页面
{
	int N = dlg->m_iStayCount + 1 ;
	if (QueueFull (pQ))
	{
		return FALSE ;
	}
	else
	{
		pQ->pBase[pQ->rear] = val; // 压栈在队尾  
        pQ->rear = (pQ->rear+1) % N;  // rear加1
		
		return TRUE ;
	}
}

bool CRunPro::DeQueue (QUEUE* pQ) // 出队操作
{
	int N = dlg->m_iStayCount + 1 ;

	if (QueueEmpty (pQ))
	{
		return FALSE ;
	}
	else
	{
//		*pVal = pQ->pBase[pQ->front] ;
		pQ->front = (pQ->front + 1) % N ;
		return TRUE ;
	}
}

bool CRunPro::SameQueue (QUEUE *pQ, int val) // 判断队列中有没有和将要放入队列的序号相同
{
	int N = dlg->m_iStayCount + 1 ;
	int iTemp = pQ->front ;

	while ( iTemp != pQ->rear)  //循环检查队列中有没有缺页
    {  
        if ( pQ->pBase[iTemp] == val)  
		{
			return TRUE ;
		}  
        iTemp = (iTemp+1) % N ;  
    }

	return FALSE ;
}

//MemArr表示所有的页面（数组）,iPos表示将要进入内存的页面号下标（在数组中）
void CRunPro::Replace1 (QUEUE *pQ, int* MemArr, int iPos) 
{
	int iTemp[30] ;
	int N = dlg->m_iPageNum ;

	for (int i = 0; i < pQ->rear; i++)
	{
		for (int j = iPos + 1; j < N; j++)
		{
			 if (MemArr[j] == pQ->pBase[i])
			 {
				iTemp[i] = j - iPos ;
			 }

			 if ((j + 1) == N)
			 {
				iTemp[i] = j - iPos + 1 ;
			 }

			 if (MemArr[j] == pQ->pBase[i])
			 {
				break ;
			 }
		}
	}

	int k = 0 ; 
	int iNum = iTemp[0] ;

	for (int m = 1; m < pQ->rear; m++)
	{
		if (iNum < iTemp[m])
		{
			iNum = iTemp[m] ;
			k = m ;
		}
	}

	pQ->pBase[k] = MemArr[iPos] ;

}

bool CRunPro::Replace2 (QUEUE* pQ, int* pVal)	// 先进先出置换算法
{

	int N = dlg->m_iStayCount + 1 ;

	if (QueueEmpty (pQ))
	{
		return FALSE ;
	}
	else
	{
		*pVal = pQ->pBase[pQ->front] ;
		pQ->front = (pQ->front + 1) % N ;
		return TRUE ;
	}
}


//最近最久未使用算法的相关函数
void CRunPro::InitQueueLRU (QUEUELRU *pQ)
{
	int N = dlg->m_iStayCount + 1 ;
	pQ->pBase = (LRU*)malloc(sizeof(LRU) * N);  
    pQ->front = pQ->rear = 0;  //初始化为0
}

bool CRunPro::QueueFullLRU(QUEUELRU* pQ)
{
	int N = dlg->m_iStayCount+1;  

    if ((pQ->rear +1) % N == pQ->front) //循环队列
	{
        return TRUE;  
	}
    else
	{
        return FALSE;
	}
}

bool CRunPro::QueueEmptyLRU(QUEUELRU* pQ) //判断队列是否是空
{
	int N = dlg->m_iStayCount + 1 ;

	if (pQ->front == pQ->rear)
	{
		return TRUE ;
	}
	else
	{
		return FALSE ;
	}
}

bool CRunPro::EnQueueLRU (QUEUELRU *pQ, int val)
{
	int N = dlg->m_iStayCount + 1 ;

	if( QueueFullLRU(pQ) )  
    {  
        return FALSE ;  
    }  
    else  
    {  
        pQ->pBase[pQ->rear].data = val ; // 压栈在队尾  
        pQ->pBase[pQ->rear].time = 0 ;   // 初始化次数为0  
        pQ->rear = (pQ->rear+1) % N;  

        return TRUE ;  
    }  
}
/*
bool CRunPro::DeQueue (QUEUELRU* pQ, int* pVal) // 出队操作
{
	int N = dlg->m_iStayCount + 1 ;

	if (QueueEmptyLRU (pQ))
	{
		return FALSE ;
	}
	else
	{
		*pVal = pQ->pBase[pQ->front].data ; // 把出队的元素保存起来  
        pQ->front = (pQ->front+1)%N ; 

        return FALSE ;
	}
}
*/

bool CRunPro::SameQueueLRU (QUEUELRU *pQ, int val)
{
	int N = dlg->m_iStayCount + 1 ;
	int iTemp = pQ->front ;

	while ( iTemp != pQ->rear)  //循环检查队列中有没有缺页
    {  
        if ( pQ->pBase[iTemp].data == val)  
		{
			return TRUE ;
		}  
        iTemp = (iTemp+1) % N ;  
    }

	return FALSE ;
}

bool CRunPro::AddTime (QUEUELRU *pQ)
{
	int N = dlg->m_iStayCount + 1 ;
	int m_iHead = pQ->front ;
	while (m_iHead != pQ->rear)
	{
		pQ->pBase[m_iHead].time++  ;

		m_iHead = (m_iHead + 1) % N ;

	}
	return TRUE ;
}

void CRunPro::SetTimeZero (QUEUELRU *pQ, int val)
{

	int N = dlg->m_iStayCount + 1 ;
	int m_iHead = pQ->front ;

	while( m_iHead != pQ->rear)  
    {  
        if( pQ->pBase[m_iHead].data == val)  
        {  
            pQ->pBase[m_iHead].time = 0;  
        }  
        m_iHead = (m_iHead + 1) % N;  
    }  
}

int CRunPro::FindBigTime (QUEUELRU *pQ)
{

	int N = dlg->m_iStayCount + 1 ;
	int m_iHead = pQ->front ;
	int iMax = m_iHead ;
	int MaxTime = pQ->pBase[pQ->front].time ;

	while( m_iHead != pQ->rear)  
    {  
        if( pQ->pBase[m_iHead].time > MaxTime)  
        {  
            iMax = m_iHead ; 
			MaxTime = pQ->pBase[m_iHead].time ;  
        } 

        m_iHead = (m_iHead + 1) % N;  
    }  
    return iMax ;
}

void CRunPro::Replace3 (QUEUELRU *pQ, int val)
{
	int MaxTime = FindBigTime (pQ) ; 
 
    pQ->pBase[MaxTime].data = val ;  
    pQ->pBase[MaxTime].time = 0 ;
}


// 最少使用的相关函数
void CRunPro::InitQueueLFU (QUEUELFU *pQ)
{
	int N = dlg->m_iStayCount + 1 ;
	pQ->pBase = (LFU*)malloc(sizeof(LFU) * N);  
    pQ->front = pQ->rear = 0;  //初始化为0
}

bool CRunPro::QueueFullLFU (QUEUELFU *pQ)
{
	int N = dlg->m_iStayCount+1;  

    if ((pQ->rear +1) % N == pQ->front) //循环队列
	{
        return TRUE;  
	}
    else
	{
        return FALSE;
	}
}
	
bool CRunPro::EnQueueLFU (QUEUELFU *pQ, int val)
{
	int N = dlg->m_iStayCount + 1 ;

	if( QueueFullLFU(pQ) )  
    {  
        return FALSE ;  
    }  
    else  
    {  
        pQ->pBase[pQ->rear].data = val ; // 压栈在队尾  
        pQ->pBase[pQ->rear].time = 1 ;   // 初始化次数为0  
        pQ->rear = (pQ->rear+1) % N;  

        return TRUE ;  
    }
}
	
bool CRunPro::SameQueueLFU (QUEUELFU *pQ, int val)	  //判断队列中有没有和将要放入队列的序号相同 
{
	int N = dlg->m_iStayCount + 1 ;
	int iTemp = pQ->front ;

	while ( iTemp != pQ->rear)  //循环检查队列中有没有缺页
    {  
        if ( pQ->pBase[iTemp].data == val)  
		{
			pQ->pBase[iTemp].time++ ;
			return TRUE ;
		}  
        iTemp = (iTemp+1) % N ;  
    }

	return FALSE ;
}
	
void CRunPro::Replace4 (QUEUELFU *pQ, int* MemArr, int val) // 最少使用置换算法
{
	int b = 0, m_iMinVisitTime = pQ->pBase[0].time ;

	for (int i = 1; i < pQ->rear; i++)
	{
		if (m_iMinVisitTime >= pQ->pBase[i].time)
		{
			m_iMinVisitTime = pQ->pBase[i].time ;
			b = i ;
		}
	}
	pQ->pBase[b].data = MemArr[val] ;
	pQ->pBase[b].time = 1 ;
}

void CRunPro::fSaveToTxt(CListCtrl* pList)
{
//	CString strFile = _T("C:\\页面置换算法.txt") ;
//	CString strContent = _T("") ; // 存储表格内容
	
	int m_iRowCount = pList->GetItemCount() ;
	int m_iColCount = pList->GetHeaderCtrl()->GetItemCount() ; // 取得列数

	for (int i = 0; i < m_iRowCount; i++)
	{
		CString strLine ;	// 行文本

		for (int j = 0; j < m_iColCount; j++)
		{
			strLine += pList->GetItemText (i, j) ;
			strLine += "\t" ;
		}

		strContent += strLine ;
		strContent += "\r\n" ;
	}

/*	try
	{
		CStdioFile m_cFile;

		m_cFile.Open(_T("页面置换算法.txt"), CFile::modeCreate | CFile::modeWrite |CFile::typeText | CFile::typeUnicode) ;
		m_cFile.WriteString (strContent) ;

		m_cFile.Close() ;

		
	}
	catch (CFileException* e)
	{
		e->ReportError() ;
		e->Delete() ;
	}
*/
}



