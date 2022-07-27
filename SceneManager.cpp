#include "SceneManager.h"

/*
CCore* CCore::g_pInst = nullptr;

CCore* CCore::GetInstance()
{
	// ���� ȣ�� ��
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



// ���� : ���� �������� �ʾƵ� �ȴ�. �ֳ�? �������� �Ҵ��� �������ϱ�
// ���� : ���α׷� �߰��� ���� �� ����. ������ ������ �������� �Ѵ�.
// => ���� ������ �Ŵ��� ������ �ϴ� Ŭ������ ��쿡 ������.
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

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC ����
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ScreenResolution.x, m_ScreenResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBitmap);
}

void SceneManager::Render()
{
	m_hDC = CreateCompatibleDC(m_hDC);
}

