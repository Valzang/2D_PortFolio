#include "Core.h"
#include "Object.h"


CCore::CCore() : m_hBit(NULL), m_hDC(NULL)
, m_hWnd(NULL), m_memDC(NULL), m_ptResolution({ 0, 0 })
{

}

CCore::~CCore()
{
	// GetDC로 만든건 ReleaseDC로 지워야함.
	ReleaseDC(m_hWnd, m_hDC);

	// CreateCompatibleDC로 만든건 DeleteDC로 지워야함.
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}




int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링 용도의 비트맵과 DC 제작
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBitmap);

	// Manager 초기화
	cTimeManager::GetInstance()->Init();
	cKeyManager::GetInstance()->Init();
	cSceneManager::GetInstance()->Init();

	return S_OK;
}


void CCore::Progress()
{

	cTimeManager::GetInstance()->Update();
	cKeyManager::GetInstance()->Update();
	cSceneManager::GetInstance()->Update();


	// Rendering

	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	cSceneManager::GetInstance()->Render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		   , m_memDC, 0, 0, SRCCOPY);

}

void CCore::Update()
{
}

void CCore::Render()
{
}
