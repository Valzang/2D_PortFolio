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
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new Scene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	// 현재 씬 지정
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
	// GetDC로 만든건 ReleaseDC로 지워야함.
	ReleaseDC(m_hWnd, m_hDC);

	// CreateCompatibleDC로 만든건 DeleteDC로 지워야함.
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
*/
