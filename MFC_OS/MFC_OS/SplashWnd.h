#pragma once
#include "afxwin.h"
class CSplashWnd :
	public CWnd
{
public:
	CSplashWnd(void);
	~CSplashWnd(void);

protected:
	CBitmap m_bitmap;//��ʼ����λͼ   
	static CSplashWnd* m_pSplashWnd;//ָ���ʼ�����ָ�� 

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

