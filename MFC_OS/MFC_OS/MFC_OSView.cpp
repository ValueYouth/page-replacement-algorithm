
// MFC_OSView.cpp : CMFC_OSView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CMFC_OSView ����/����

CMFC_OSView::CMFC_OSView()
{
	// TODO: �ڴ˴���ӹ������
	m_nWidth = 0 ;

	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP1); ///����λͼ 
	m_brushBackground.CreatePatternBrush(&bmp); ///����λͼ��ˢ 
}

CMFC_OSView::~CMFC_OSView()
{
}

BOOL CMFC_OSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFC_OSView ����

void CMFC_OSView::OnDraw(CDC* pDC)
{
	CMFC_OSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CClientDC dc (this) ;
	TEXTMETRIC tm1 ;
	dc.GetTextMetrics (&tm1) ;

	CFont m_font ;
	m_font.CreatePointFont (200, _T("�����п�")) ;
	CFont* pOldFont = pDC->SelectObject (&m_font) ;

	

//	str1.LoadStringW (IDS_MAKER) ;
//	pDC->TextOutW (10, tm1.tmHeight * 2 + 30, str1) ;

	CRect rect; 
	GetClientRect(rect); //ȡ�ÿͻ����� 
	pDC-> FillRect(rect,&m_brushBackground);  //�ñ�����ˢ������� 

	CString str, str1 ;

	str.LoadStringW (IDS_WELCOME) ;
	pDC->SetBkMode (TRANSPARENT) ;		   //���䱳������Ϊ͸��
	pDC->SetTextColor (RGB (255, 250, 250)) ;//��������Ϊ��ɫ 
	pDC->TextOutW (110, 0, str) ;

	pDC->SelectObject (pOldFont) ;

}


// CMFC_OSView ��ӡ

BOOL CMFC_OSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFC_OSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFC_OSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMFC_OSView ���

#ifdef _DEBUG
void CMFC_OSView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_OSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_OSDoc* CMFC_OSView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_OSDoc)));
	return (CMFC_OSDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_OSView ��Ϣ�������


int CMFC_OSView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_btn1.Create(_T("��ʼ"), WS_CHILD | WS_VISIBLE , CRect (160, 240, 250, 280),
		this, 1001) ;
	m_btn1.ShowWindow (SW_SHOWNORMAL) ;

	m_btn2.Create(_T("�˳�"), WS_CHILD | WS_VISIBLE , CRect (330, 240, 420, 280),
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

	if ( IDYES == MessageBox( _T("      ---ȷ���˳�ô��---"),_T( ""), MB_YESNO | MB_ICONQUESTION ))
	{
		PostQuitMessage (0) ;

	}

	

}

void CMFC_OSView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_nWidth += 5 ;

	CClientDC dc(this) ;
	TEXTMETRIC tm ;
	dc.GetTextMetrics (&tm) ;

	CRect rect, rect1, rect2 ;
	rect.left   = 200 ;									// ��ȡ�������Ͻ�x����
	rect.right  = m_nWidth;								// ��ȡ�������½�x����
	rect.top    = 80 ;										//.........���Ͻ�y����
	rect.bottom = /*tm.tmHeight*/400 ;							//.........���½�y����
	dc.SetTextColor (RGB (255, 0, 10)) ;

	CString str("�����ߣ��ս���С��");
//	str.LoadStringW (str) ;
	dc.SetBkMode (1) ;		//ʹ����͸��
	dc.DrawText (str, rect, DT_LEFT);

	dc.SetTextColor (RGB (0,240,0)) ;
	rect1.left   = 220 ;									// ��ȡ�������Ͻ�x����
	rect1.right  = m_nWidth;								// ��ȡ�������½�x����
	rect1.top    = 120 ;										//.........���Ͻ�y����
	rect1.bottom = /*tm.tmHeight*/400 ;		
	CString str1("�������ڣ�2015��1��6��") ;
	dc.DrawText (str1, rect1, DT_LEFT) ;

	dc.SetTextColor (RGB (20,0,255)) ;
	rect2.left   = 240 ;									// ��ȡ�������Ͻ�x����
	rect2.right  = m_nWidth;								// ��ȡ�������½�x����
	rect2.top    = 160 ;										//.........���Ͻ�y����
	rect2.bottom = /*tm.tmHeight*/600 ;		
	CString str2("Welcome, Users !") ;
	dc.DrawText (str2, rect2, DT_LEFT) ;

	CView::OnTimer(nIDEvent);
}



