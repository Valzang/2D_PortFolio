#pragma once
#include "CustomDefine.h"

class cScene;

class cSceneManager
{
	SINGLETON2(cSceneManager);

private:
	cScene* m_arrScene[(UINT)SCENE_TYPE::END]; // ������ �ִ� �� ���
	cScene* m_curScene; // ���� ��
	int		m_curSceneLevel;
	bool	m_Restart;

	int		m_PlayerLifeCount;
	int		m_Score;
	
public:
	void Init();
	void Update();
	void Render(HDC _hdc);

	void ConnectPlayerInfo(int _Life) { m_PlayerLifeCount = _Life;}
	int GetPlayerLife() { return m_PlayerLifeCount; }
	void SetScore(int _Score) { m_Score = _Score; }
	int GetScore() { return m_Score; }

	cScene* GetCurScene() { return m_curScene; }
};
