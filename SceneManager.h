#pragma once
#include "CustomDefine.h"

class Scene;

class SceneManager
{
	SINGLETON2(SceneManager);

private:
	Scene* m_arrScene[(UINT)SCENE_TYPE::END]; // ������ �ִ� �� ���
	Scene* m_curScene; // ���� ��
	
public:
	void Init();
	void Update();
	void Render(HDC _hdc);
};
