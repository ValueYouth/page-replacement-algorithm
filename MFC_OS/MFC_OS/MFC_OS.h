
// MFC_OS.h : MFC_OS Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFC_OSApp:
// �йش����ʵ�֣������ MFC_OS.cpp
//

class CMFC_OSApp : public CWinAppEx
{
public:
	CMFC_OSApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFC_OSApp theApp;
