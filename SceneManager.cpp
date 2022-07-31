#include "SceneManager.h"
#include "Scene_Start.h"

cSceneManager::cSceneManager()
	: m_curScene(nullptr)
	, m_arrScene {}
{

}
cSceneManager::~cSceneManager()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (m_arrScene[i] != nullptr)
		{
			//m_arrScene[i]->DeleteSceneImg();
			delete m_arrScene[i];
			m_arrScene[i] = nullptr;
		}
	}
}

void cSceneManager::Init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new cScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	// 현재 씬 지정
	m_curScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_curScene->Enter();
}

void cSceneManager::Update()
{
	m_curScene->Update();
}

void cSceneManager::Render(HDC _hdc)
{
	int t_MonsterCount = m_curScene->GetMonsterSize();
	if(t_MonsterCount > 0)
		m_curScene->Render(_hdc);
	else
	{
		delete m_curScene;
	}
}

