// P2P_END.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CP2P_ENDApp:
// �йش����ʵ�֣������ P2P_END.cpp
//

class CP2P_ENDApp : public CWinApp
{
public:
	CP2P_ENDApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CP2P_ENDApp theApp;