
// MFC_OSView.h : CMFC_OSView 类的接口
//

#pragma once


class CMFC_OSView : public CView
{
protected: // 仅从序列化创建
	CMFC_OSView();
	DECLARE_DYNCREATE(CMFC_OSView)

// 特性
public:
	CMFC_OSDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFC_OSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	CButton m_btn1, m_btn2 ;
	int m_nWidth;
	CBrush m_brushBackground;


	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtnDown1 () ;
	afx_msg void OnBtnDown2 () ;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnIconEraseBkgnd(CDC* pDC);
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnClose();
//	afx_msg void OnOk();
//	afx_msg void OnOk();
//	afx_msg void OnIdcancel();
};

#ifndef _DEBUG  // MFC_OSView.cpp 中的调试版本
inline CMFC_OSDoc* CMFC_OSView::GetDocument() const
   { return reinterpret_cast<CMFC_OSDoc*>(m_pDocument); }
#endif

