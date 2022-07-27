#pragma once
#include "CustomDefine.h"

class Scene;

class SceneManager
{
	SINGLETON2(SceneManager);

private:
	Scene* m_arrScene[(UINT)SCENE_TYPE::END]; // 가지고 있는 씬 목록
	Scene* m_curScene; // 현재 씬
	
public:
	void Init();
	void Update();
	void Render(HDC _hdc);
};
