#pragma once
#include "afxwin.h"
class CSplashWnd :
	public CWnd
{
public:
	CSplashWnd(void);
	~CSplashWnd(void);

protected:
	CBitmap m_bitmap;//初始画面位图   
	static CSplashWnd* m_pSplashWnd;//指向初始画面的指针 

public:
	void ShowSplashScreen(CWnd* pParentWnd);
//	BOOL Create(void);
	BOOL Create(CWnd* pParentWnd);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void PostNcDestroy();
};

