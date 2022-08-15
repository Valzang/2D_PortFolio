#include "Core.h"
#include "Object.h"

cCore::cCore() : m_hBit(NULL), m_hDC(NULL)
, m_hWnd(NULL), m_memDC(NULL), m_ptResolution({ 0, 0 })
{
	//cSound::Init();
}

cCore::~cCore()
{
	Gdi_End();
	// GetDC로 만든건 ReleaseDC로 지워야함.
	ReleaseDC(m_hWnd, m_hDC);

	// CreateCompatibleDC로 만든건 DeleteDC로 지워야함.
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	//cSound::Release();

}


int cCore::Init(HWND _hWnd, POINT _ptResolution)
{
	Gdi_Init();

	// 메인의 핸들을 Core의 핸들에 넣어주기
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };

	// 작업 창의 크기를 rt 사이즈로 만들어주기. ( 기존에는 윈도우 메뉴바를 포함한 사이즈임 )
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

	// Core의 핸들에 지정한 사이즈만큼 출력
	SetWindowPos(m_hWnd, nullptr, 300, 300, rt.right - rt.left, rt.bottom - rt.top, 0);

	// Core의 핸들(from 메인 핸들)로 부터 가져온 DC를 복사해주기
	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링 용도의 비트맵과 DC 제작
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	// m_hDC(from 메인 핸들의 DC)를 복사해주기
	m_memDC = CreateCompatibleDC(m_hDC);

	// 이중 버퍼링 용도로 만든 비트맵을 m_memDC에 넣어주고 기존에 들고 있던 비트맵을 지워주기
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBitmap);

	// Manager 초기화
	cTimeManager::GetInstance()->Init();
	cKeyManager::GetInstance()->Init();
	cSceneManager::GetInstance()->Init();

	return S_OK;
}


void cCore::Progress()
{

	cTimeManager::GetInstance()->Update();
	if (DELTA_TIME >= 0.014f)
	{
		cKeyManager::GetInstance()->Update();
		cSceneManager::GetInstance()->Update();
		Render();	
	}
}

void cCore::Update()
{
}

void cCore::Render()
{
	// Render해주는 부분 =====================================================

	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1); // 빈 화면으로 초기화

	cSceneManager::GetInstance()->Render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		   , m_memDC, 0, 0, SRCCOPY);
	// m_memDC : 그려주는 도화지, m_hDC : 메인 도화지
}
