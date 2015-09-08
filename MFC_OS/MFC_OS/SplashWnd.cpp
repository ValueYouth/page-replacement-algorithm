#include "stdafx.h"
#include "SplashWnd.h"

CSplashWnd* CSplashWnd::m_pSplashWnd; 

CSplashWnd::CSplashWnd(void)
{
}


CSplashWnd::~CSplashWnd(void)
{
}


void CSplashWnd::ShowSplashScreen(CWnd* pParentWnd)
{
	if(m_pSplashWnd!=NULL) return;  
	m_pSplashWnd=new CSplashWnd;  
	if(!m_pSplashWnd->Create(pParentWnd))  
		//������ʼ���洰��   
		delete m_pSplashWnd;  
	else  
		m_pSplashWnd->UpdateWindow();  
	//��ʾ��ʼ���洰��   
}


//BOOL CSplashWnd::Create(void)
//{
//	return 0;
//}


BOOL CSplashWnd::Create(CWnd* pParentWnd)
{
	if(!m_bitmap.LoadBitmap(313))  
		//����λͼ   
		return FALSE;  
	BITMAP bm;  
	m_bitmap.GetBitmap(&bm);  
	return CreateEx(0,AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),  
	NULL, WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, pParentWnd->GetSafeHwnd(), NULL);//��������ܴ��ڵ��Ӵ���
}
BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CenterWindow();  
	SetTimer(1,2000,NULL); //ʱ�����   

	return 0;
}


void CSplashWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	CDC dcImage;  
	if(!dcImage.CreateCompatibleDC(&dc)) return;  
	BITMAP bm;  
	m_bitmap.GetBitmap(&bm);  
	CBitmap* pOldBitmap=dcImage.SelectObject(&m_bitmap);  
	dc.BitBlt(0,0,bm.bmWidth,bm.bmHeight,&dcImage,0,0,SRCCOPY);  
	dcImage.SelectObject(pOldBitmap);  
}


void CSplashWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

//	CWnd::OnTimer(nIDEvent);
	DestroyWindow(); //���ٳ�ʼ���洰��   
	AfxGetMainWnd()->UpdateWindow();  
	CWnd::OnTimer(nIDEvent);
}


void CSplashWnd::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	DestroyWindow();  
	CWnd::PostNcDestroy();
}
