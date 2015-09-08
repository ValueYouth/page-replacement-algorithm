// MyFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_OS.h"
#include "MyFrame.h"
#include "afxdialogex.h"

//#include "CMFC_OSView.h"

#include "RunPro.h"
#include <time.h>

static int m_iTemp[1000] ; //�������飬�洢������Լ������ҳ������
// CMyFrame �Ի���

IMPLEMENT_DYNAMIC(CMyFrame, CDialog)

CMyFrame::CMyFrame(CWnd* pParent /*=NULL*/)
	: CDialog(CMyFrame::IDD, pParent)
	, m_iStayCount(3)
	, m_strAllPage(_T(""))
	//, m_strGetTime(_T("8"))
	//, m_strBreakTime(_T("20"))
	//, m_strFastTime(_T("1"))
	, m_iMax(9)
	, m_iMin(0)
	, m_iPageNum(20)
	, m_bFastYN(FALSE)
	, m_iBreakTime(20)
	, m_iFastTime(1)
	, m_iGetTime(8)
{

}

CMyFrame::~CMyFrame()
{
}

void CMyFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STAYCOUNT, m_iStayCount);
	DDV_MinMaxInt(pDX, m_iStayCount, 1, 10);
	DDX_Text(pDX, IDC_ALLPAGE, m_strAllPage);
	//  DDX_Text(pDX, IDC_GETTIME, m_strGetTime);
	//  DDX_Text(pDX, IDC_BREAKTIME, m_strBreakTime);
	//  DDX_Text(pDX, IDC_FASTTIME, m_strFastTime);
	DDX_Control(pDX, IDC_LISTCTRL, m_wndListCtrl);
	DDX_Text(pDX, IDC_MAX, m_iMax);
	DDX_Text(pDX, IDC_MIN, m_iMin);
	DDX_Text(pDX, IDC_PAGENUM, m_iPageNum);
	DDX_Check(pDX, IDC_FASTYN, m_bFastYN);
	DDX_Text(pDX, IDC_BREAKTIME, m_iBreakTime);
	DDX_Text(pDX, IDC_FASTTIME, m_iFastTime);
	DDX_Text(pDX, IDC_GETTIME, m_iGetTime);
}


BEGIN_MESSAGE_MAP(CMyFrame, CDialog)
	ON_BN_CLICKED(IDC_RESOLVE, &CMyFrame::OnBnClickedResolve)
	ON_BN_CLICKED(IDC_RANDOM, &CMyFrame::OnBnClickedRandom)
	ON_BN_CLICKED(IDOK, &CMyFrame::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CLEAR, &CMyFrame::OnBnClickedClear)
	ON_BN_CLICKED(IDCANCEL, &CMyFrame::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_STAYCOUNT, &CMyFrame::OnEnChangeStaycount)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyFrame::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMyFrame ��Ϣ�������


BOOL CMyFrame::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_wndListCtrl.InsertColumn (0, _T("���"), LVCFMT_CENTER, 128) ;				//�趨��һ��
	m_wndListCtrl.InsertColumn (1, _T("ҳ���"), LVCFMT_LEFT, 128) ;			//�趨�ڶ���
	m_wndListCtrl.SetExtendedStyle (LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT) ;	//����������


	return TRUE;  // return TRUE unless you set the focus to a control

}


void CMyFrame::OnBnClickedResolve()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData() ;

	if (m_strAllPage.GetLength() == m_iPageNum)		// �ж������ҳ�������Ԥ���Ƿ����
	{
		// forѭ����ȷ������ҳ��ŵķ�Χ�Ƿ����Ԥ������
		for (int i = 0; i < m_strAllPage.GetLength(); i++)
		{
			CString str1, str2 ;

			m_iTemp[i] = m_strAllPage.GetAt (i) - '0' ;
			if (m_iTemp[i] >= m_iMin && m_iTemp[i] <= m_iMax)	// ������ϣ��������ݵ��б�չʾ
			{
				str1.Format (_T("%d"), i) ;
				m_wndListCtrl.InsertItem (i, str1) ;
				str2.Format (_T("%c"), m_strAllPage.GetAt (i)) ;
				m_wndListCtrl.SetItemText (i, 1, str2) ;	
			}
			else
			{
				MessageBox (_T("����ҳ�淶Χ������Ԥ��������\n���������룡"), 
					_T("��ʾ��Ϣ"), MB_OKCANCEL | MB_ICONINFORMATION ) ;
				m_wndListCtrl.DeleteAllItems() ;
				break ;
			}
			if (i == m_strAllPage.GetLength() - 1)
			{
//			Sleep (500) ;
//			MessageBox (_T("�������У�����������δ֪����"), 
//				_T("����"), MB_OKCANCEL | MB_ICONWARNING ) ;
			}
		}
	}
	else
	{
		MessageBox (_T("����ҳ�����������Ԥ��������\n���������룡"), 
			_T("��ʾ��Ϣ"), MB_OKCANCEL | MB_ICONINFORMATION ) ;
		
	}
}


void CMyFrame::OnBnClickedRandom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData() ;

	int i, m_iNum = 0; 
	srand( (unsigned)time( NULL ) );
	for ( i = 0; i < m_iPageNum; i++)
	{
		m_iNum = rand() % (m_iMax - m_iMin) + m_iMin ;
		m_iTemp[i] = m_iNum ;
	}

	CString str1, str2 ;

	for (int j = 0; j < m_iPageNum; j++)
		{
			str1.Format (_T("%d"), j) ;
			m_wndListCtrl.InsertItem (j, str1) ;
			str2.Format (_T("%d"), m_iTemp[j]) ;
			m_wndListCtrl.SetItemText (j, 1, str2) ;	
		}

//	Sleep (500) ;
//	MessageBox (_T("�������У�����������δ֪����"), 
//		_T("����"), MB_OKCANCEL | MB_ICONWARNING ) ;
}


void CMyFrame::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CDialog::OnOK();
	CRunPro dlg ;
	dlg.dlg = this;
	dlg.DoModal() ;
}


void CMyFrame::OnBnClickedClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_wndListCtrl.DeleteAllItems() ;
}


void CMyFrame::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_wndListCtrl.DeleteAllItems() ;
	CDialog::OnCancel();
}


void CMyFrame::OnEnChangeStaycount()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�


	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMyFrame::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecuteW (NULL, _T("open"), _T("ҳ���û��㷨.txt"), NULL, NULL, SW_SHOWMAXIMIZED) ;
}
