#include "SceneManager.h"
#include "Scene_Start.h"
#include "Scene_Intro.h"

cSceneManager::cSceneManager()
	: m_curScene(nullptr)
	, m_arrScene {}
	, m_curSceneLevel(1)
	, m_Restart(false)
{
	
}
cSceneManager::~cSceneManager()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (m_arrScene[i] != NULL)
		{
			delete m_arrScene[i];
			m_arrScene[i] = nullptr;
		}
	}
}

void cSceneManager::Init()
{
	switch (m_curSceneLevel)
	{
		case (INT)SCENE_TYPE::START:
			m_arrScene[(UINT)SCENE_TYPE::START] = new cScene_Intro;
			m_curScene = m_arrScene[(UINT)SCENE_TYPE::START];
			break;
		case (INT)SCENE_TYPE::STAGE_11:
			m_arrScene[(UINT)SCENE_TYPE::STAGE_11] = new cScene_Start;
			m_curScene = m_arrScene[(UINT)SCENE_TYPE::STAGE_11];
			break;
		case (INT)SCENE_TYPE::STAGE_12:
			break;
		case (INT)SCENE_TYPE::STAGE_13:
			break;
		case (INT)SCENE_TYPE::STAGE_14:
			break;
		case (INT)SCENE_TYPE::STAGE_15:
			break;
	}
	// Scene 생성
	//m_arrScene[(UINT)SCENE_TYPE::TOOL] = new cScene_Intro;
	//m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	// 현재 씬 지정
	//m_curScene = m_arrScene[(UINT)SCENE_TYPE::TOOL];
	m_curScene->Enter();

}

void cSceneManager::Update()
{
	m_curScene->Update();
	if (m_curScene->GetContinue())
		m_Restart = true;
	else if (m_Restart)
	{
		delete m_arrScene[m_curSceneLevel];
		m_arrScene[m_curSceneLevel] = nullptr;
		m_curSceneLevel = (INT)SCENE_TYPE::START;
		m_Restart = false;
		Init();
	}
}

void cSceneManager::Render(HDC _hdc)
{
	int t_MonsterCount = m_curScene->GetMonsterSize();
	if(t_MonsterCount > 0)
		m_curScene->Render(_hdc);
	else
	{
		delete m_arrScene[m_curSceneLevel];
		m_arrScene[m_curSceneLevel++] = nullptr;
		Init();
	}
}

