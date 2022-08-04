#pragma once
#include "CustomDefine.h"
#include "TimeManager.h"
#include "SceneManager.h"

class cCore
{
	SINGLETON2(cCore)
private:
	HWND	m_hWnd;	// 메인 윈도우 핸들
	POINT	m_ptResolution; // 메인 윈도우 해상도
	HDC		m_hDC;			// 메인 윈도우 핸들에서 가져온 DC
	HDC		m_memDC;		// m_hDC 복사해준 m_memDC ( 그려주기 위한 용도로 )
	HBITMAP m_hBit;

public:
	int Init(HWND _hWnd, POINT _ptResolution);

	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
	void Progress();
	void Update();
	void Render();
};

