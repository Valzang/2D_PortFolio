#include "SceneManager.h"

/*
CCore* CCore::g_pInst = nullptr;

CCore* CCore::GetInstance()
{
	// 최초 호출 시
	if (g_pInst == nullptr)
	{
		g_pInst = new CCore;
	}

	return g_pInst;
}

void CCore::Release()
{
	if (nullptr != g_pInst)
	{
		delete g_pInst;
		g_pInst = nullptr;
	}
}



// 장점 : 굳이 지워주지 않아도 된다. 왜냐? 동적으로 할당을 안했으니까
// 단점 : 프로그램 중간에 지울 수 없다. 종료할 때까지 가져가야 한다.
// => 따라서 가벼운 매니저 역할을 하는 클래스의 경우에 유용함.
CCore2* CCore2::GetInstance()
{
	static CCore2 core;
	return &core;
}
*/


SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

void SceneManager::Init(HDC hdc, HWND hWnd, HBITMAP hBIt, POINT ScreenResolution)
{
	m_hWnd = hWnd;
	m_ScreenResolution = ScreenResolution;

	RECT rt = { 0, 0, m_ScreenResolution.x, m_ScreenResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링 용도의 비트맵과 DC 제작
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ScreenResolution.x, m_ScreenResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBitmap);
}

void SceneManager::Render()
{
	m_hDC = CreateCompatibleDC(m_hDC);
}

