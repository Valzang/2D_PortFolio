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
	// GetDC�� ����� ReleaseDC�� ��������.
	ReleaseDC(m_hWnd, m_hDC);

	// CreateCompatibleDC�� ����� DeleteDC�� ��������.
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	//cSound::Release();

}


int cCore::Init(HWND _hWnd, POINT _ptResolution)
{
	Gdi_Init();

	// ������ �ڵ��� Core�� �ڵ鿡 �־��ֱ�
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };

	// �۾� â�� ũ�⸦ rt ������� ������ֱ�. ( �������� ������ �޴��ٸ� ������ �������� )
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

	// Core�� �ڵ鿡 ������ �����ŭ ���
	SetWindowPos(m_hWnd, nullptr, 300, 300, rt.right - rt.left, rt.bottom - rt.top, 0);

	// Core�� �ڵ�(from ���� �ڵ�)�� ���� ������ DC�� �������ֱ�
	m_hDC = GetDC(m_hWnd);

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC ����
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	// m_hDC(from ���� �ڵ��� DC)�� �������ֱ�
	m_memDC = CreateCompatibleDC(m_hDC);

	// ���� ���۸� �뵵�� ���� ��Ʈ���� m_memDC�� �־��ְ� ������ ��� �ִ� ��Ʈ���� �����ֱ�
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBitmap);

	// Manager �ʱ�ȭ
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
	// Render���ִ� �κ� =====================================================

	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1); // �� ȭ������ �ʱ�ȭ

	cSceneManager::GetInstance()->Render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		   , m_memDC, 0, 0, SRCCOPY);
	// m_memDC : �׷��ִ� ��ȭ��, m_hDC : ���� ��ȭ��
}
