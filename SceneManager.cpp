#include "SceneManager.h"
#include "Scene_Start.h"

SceneManager::SceneManager()
	: m_curScene(nullptr)
	, m_arrScene {}
{

}
SceneManager::~SceneManager()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (m_arrScene[i] != nullptr)
			delete m_arrScene[i];
	}
}

void SceneManager::Init()
{
	// Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new Scene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	// ���� �� ����
	m_curScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_curScene->Enter();
}

void SceneManager::Update()
{
	m_curScene->Update();
}

void SceneManager::Render(HDC _hdc)
{
	m_curScene->Render(_hdc);
}





/*
SceneManager::~SceneManager()
{
	// GetDC�� ����� ReleaseDC�� ��������.
	ReleaseDC(m_hWnd, m_hDC);

	// CreateCompatibleDC�� ����� DeleteDC�� ��������.
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
*/
