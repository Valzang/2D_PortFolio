#pragma once
#include "CustomDefine.h"

class cScene;

class cSceneManager
{
	SINGLETON2(cSceneManager);

private:
	cScene* m_arrScene[(UINT)SCENE_TYPE::END]; // 가지고 있는 씬 목록
	cScene* m_curScene; // 현재 씬
	
public:
	void Init();
	void Update();
	void Render(HDC _hdc);

	cScene* GetCurScene() { return m_curScene; }
};
