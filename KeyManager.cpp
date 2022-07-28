#include "KeyManager.h"

cKeyManager::cKeyManager()
{

}

cKeyManager::~cKeyManager()
{

}


void cKeyManager::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(KeyInfo { KEY_STATE::NONE, false });
	}
}

void cKeyManager::Update()
{
	//포커싱 된 윈도우가 누구인지
	HWND hWnd = GetFocus();

	// 포커싱 된 윈도우가 있다면
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// 키가 눌려있다면
			if (GetAsyncKeyState(arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].wasPushed)
					m_vecKey[i].mKeyState = KEY_STATE::HOLD;
				else
					m_vecKey[i].mKeyState = KEY_STATE::DOWN;
				m_vecKey[i].wasPushed = true;
			}
			else
			{
				// 이전에 눌려있었다면
				if (m_vecKey[i].wasPushed)
					m_vecKey[i].mKeyState = KEY_STATE::UP;
				else
					m_vecKey[i].mKeyState = KEY_STATE::NONE;
				m_vecKey[i].wasPushed = false;
			}
		}
	}

	// 포커싱 된 윈도우가 없다면
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].wasPushed = false;

			if (m_vecKey[i].mKeyState == KEY_STATE::DOWN
				|| m_vecKey[i].mKeyState == KEY_STATE::HOLD)
				m_vecKey[i].mKeyState = KEY_STATE::UP;
			else if (m_vecKey[i].mKeyState == KEY_STATE::UP)
				m_vecKey[i].mKeyState = KEY_STATE::NONE;
		}
	}
}

KEY_STATE cKeyManager::GetKeyState(KEY _key)
{
	return m_vecKey[(int)_key].mKeyState;
}
