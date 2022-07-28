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
			delete m_arrScene[i];
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
	m_curScene->Render(_hdc);
}

