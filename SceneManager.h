#pragma once

#include "CustomDefine.h"

class SceneManager
{
	SINGLETON2(SceneManager);

private:
	HWND m_hWnd = NULL;							// ������ �ڵ�
	POINT m_ScreenResolution = { 0, 0 };		// ������ �ػ�
	HDC m_hDC = NULL;							// �����쿡 �׸� DC
	HBITMAP m_hBit = NULL;
	HDC m_memDC = NULL;
	
	


public:
	void Init(HDC hdc, HWND hWnd, HBITMAP hBIt, POINT ScreenResolution);

	void Render();
};

/*
class CCore2
{
private:
	CCore2() {}
	~CCore2() {};

public:
	static CCore2* GetInstance();

};



// �̱��� ���� ���ο�
class CCore
{
private:
	// static ������ ������ ������ �����Ǹ�, �ʱ�ȭ�� �ѹ��� ������ ��.
	// ���� 2�� �̻� �ҷ��� �ʱ�ȭ�� ������� ����.
	static CCore* g_pInst;

private:
	// private�� �����ڿ� �Ҹ��ڸ� �������ν�, ��ü ������ �Ժη� ���� ���ϰԲ�
	CCore() {}
	~CCore() {}

public:
	// ���� ������ ���� ��ü�� ������ �ʰ� ���� �����ϰԲ�.
	static CCore* GetInstance();

	static void Release();

};
*/