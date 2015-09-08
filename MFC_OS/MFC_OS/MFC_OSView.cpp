
// MFC_OSView.cpp : CMFC_OSView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC_OS.h"
#endif

#include "MFC_OSDoc.h"
#include "MFC_OSView.h"

#include "MyFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_OSView

IMPLEMENT_DYNCREATE(CMFC_OSView, CView)

BEGIN_MESSAGE_MAP(CMFC_OSView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_BN_CLICKED (IDC_OK, OnBtnDown1)
	ON_BN_CLICKED (IDC_QUIT, OnBtnDown2)

	ON_WM_TIMER()
	ON_WM_ICONERASEBKGND()
	ON_WM_CTLCOLOR()
//	ON_WM_CLOSE()
//ON_COMMAND(IDC_OK, &CMFC_OSView::OnOk)
//ON_COMMAND(IDC_OK, &CMFC_OSView::OnOk)
//ON_COMMAND(IDCANCEL, &CMFC_OSView::OnIdcancel)
END_MESSAGE_MAP()

// CMFC_OSView 构造/析构

CMFC_OSView::CMFC_OSView()
{
	// TODO: 在此处添加构造代码
	m_nWidth = 0 ;

	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP1); ///加载位图 
	m_brushBackground.CreatePatternBrush(&bmp); ///创建位图画刷 
}

CMFC_OSView::~CMFC_OSView()
{
}

BOOL CMFC_OSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFC_OSView 绘制

void CMFC_OSView::OnDraw(CDC* pDC)
{
	CMFC_OSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	// TODO: 在此处为本机数据添加绘制代码
	CClientDC dc (this) ;
	TEXTMETRIC tm1 ;
	dc.GetTextMetrics (&tm1) ;

	CFont m_font ;
	m_font.CreatePointFont (200, _T("华文行楷")) ;
	CFont* pOldFont = pDC->SelectObject (&m_font) ;

	

//	str1.LoadStringW (IDS_MAKER) ;
//	pDC->TextOutW (10, tm1.tmHeight * 2 + 30, str1) ;

	CRect rect; 
	GetClientRect(rect); //取得客户区域 
	pDC-> FillRect(rect,&m_brushBackground);  //用背景画刷填充区域 

	CString str, str1 ;

	str.LoadStringW (IDS_WELCOME) ;
	pDC->SetBkMode (TRANSPARENT) ;		   //将其背景设置为透明
	pDC->SetTextColor (RGB (255, 250, 250)) ;//设置字体为黄色 
	pDC->TextOutW (110, 0, str) ;

	pDC->SelectObject (pOldFont) ;

}


// CMFC_OSView 打印

BOOL CMFC_OSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFC_OSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFC_OSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFC_OSView 诊断

#ifdef _DEBUG
void CMFC_OSView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_OSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_OSDoc* CMFC_OSView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_OSDoc)));
	return (CMFC_OSDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_OSView 消息处理程序


int CMFC_OSView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_btn1.Create(_T("开始"), WS_CHILD | WS_VISIBLE , CRect (160, 240, 250, 280),
		this, 1001) ;
	m_btn1.ShowWindow (SW_SHOWNORMAL) ;

	m_btn2.Create(_T("退出"), WS_CHILD | WS_VISIBLE , CRect (330, 240, 420, 280),
		this, 1002) ;
	m_btn2.ShowWindow (SW_SHOWNORMAL) ;

	SetTimer (1, 100, NULL) ;
		return 0;
}

void CMFC_OSView::OnBtnDown1 ()
{
	CMyFrame dlg ;
	dlg.DoModal () ;	

//	CMyFrame* pDlg = new CMyFrame() ;
//	pDlg->Create (IDD_MYFRAME, this ) ;
//	pDlg->ShowWindow (SW_NORMAL) ;
	
}

void CMFC_OSView::OnBtnDown2 ()
{

	if ( IDYES == MessageBox( _T("      ---确认退出么？---"),_T( ""), MB_YESNO | MB_ICONQUESTION ))
	{
		PostQuitMessage (0) ;

	}

	

}

void CMFC_OSView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_nWidth += 5 ;

	CClientDC dc(this) ;
	TEXTMETRIC tm ;
	dc.GetTextMetrics (&tm) ;

	CRect rect, rect1, rect2 ;
	rect.left   = 200 ;									// 获取矩形左上角x坐标
	rect.right  = m_nWidth;								// 获取矩形右下角x坐标
	rect.top    = 80 ;										//.........左上角y坐标
	rect.bottom = /*tm.tmHeight*/400 ;							//.........右下角y坐标
	dc.SetTextColor (RGB (255, 0, 10)) ;

	CString str("制作者：终结者小组");
//	str.LoadStringW (str) ;
	dc.SetBkMode (1) ;		//使背景透明
	dc.DrawText (str, rect, DT_LEFT);

	dc.SetTextColor (RGB (0,240,0)) ;
	rect1.left   = 220 ;									// 获取矩形左上角x坐标
	rect1.right  = m_nWidth;								// 获取矩形右下角x坐标
	rect1.top    = 120 ;										//.........左上角y坐标
	rect1.bottom = /*tm.tmHeight*/400 ;		
	CString str1("制作日期：2015年1月6日") ;
	dc.DrawText (str1, rect1, DT_LEFT) ;

	dc.SetTextColor (RGB (20,0,255)) ;
	rect2.left   = 240 ;									// 获取矩形左上角x坐标
	rect2.right  = m_nWidth;								// 获取矩形右下角x坐标
	rect2.top    = 160 ;										//.........左上角y坐标
	rect2.bottom = /*tm.tmHeight*/600 ;		
	CString str2("Welcome, Users !") ;
	dc.DrawText (str2, rect2, DT_LEFT) ;

	CView::OnTimer(nIDEvent);
}



