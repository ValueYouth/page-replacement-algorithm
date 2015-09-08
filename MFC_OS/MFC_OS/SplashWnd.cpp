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
		//创建初始画面窗口   
		delete m_pSplashWnd;  
	else  
		m_pSplashWnd->UpdateWindow();  
	//显示初始画面窗口   
}


//BOOL CSplashWnd::Create(void)
//{
//	return 0;
//}


BOOL CSplashWnd::Create(CWnd* pParentWnd)
{
	if(!m_bitmap.LoadBitmap(313))  
		//载入位图   
		return FALSE;  
	BITMAP bm;  
	m_bitmap.GetBitmap(&bm);  
	return CreateEx(0,AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),  
	NULL, WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, pParentWnd->GetSafeHwnd(), NULL);//创建主框架窗口的子窗口
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
	SetTimer(1,2000,NULL); //时间控制   

	return 0;
}


void CSplashWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CWnd::OnPaint()
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

//	CWnd::OnTimer(nIDEvent);
	DestroyWindow(); //销毁初始画面窗口   
	AfxGetMainWnd()->UpdateWindow();  
	CWnd::OnTimer(nIDEvent);
}


void CSplashWnd::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	DestroyWindow();  
	CWnd::PostNcDestroy();
}
