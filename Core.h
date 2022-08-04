#pragma once
#include "CustomDefine.h"
#include "TimeManager.h"
#include "SceneManager.h"

class cCore
{
	SINGLETON2(cCore)
private:
	HWND	m_hWnd;	// ���� ������ �ڵ�
	POINT	m_ptResolution; // ���� ������ �ػ�
	HDC		m_hDC;			// ���� ������ �ڵ鿡�� ������ DC
	HDC		m_memDC;		// m_hDC �������� m_memDC ( �׷��ֱ� ���� �뵵�� )
	HBITMAP m_hBit;

public:
	int Init(HWND _hWnd, POINT _ptResolution);

	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
	void Progress();
	void Update();
	void Render();
};

