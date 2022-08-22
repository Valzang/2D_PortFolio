#include "SceneManager.h"
#include "Scene_1.h"
#include "Scene_2.h"
#include "Scene_3.h"
#include "Scene_4.h"
#include "Scene_5.h"
#include "Scene_Intro.h"
#include "Scene_Ending.h"

cSceneManager::cSceneManager()
	: m_curScene(nullptr)
	, m_arrScene {}
	, m_curSceneLevel(0)
	, m_Restart(false)
	, m_PlayerLifeCount(0)
	, m_Score(0)
	, m_ScoreImg(nullptr)
{
	m_ScoreImg = Image::FromFile((WCHAR*)L"Image/UI/Number.png");
	SetImgAttr();
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
			m_arrScene[(UINT)SCENE_TYPE::STAGE_11] = new cScene_1;
			m_curScene = m_arrScene[(UINT)SCENE_TYPE::STAGE_11];
			break;
		case (INT)SCENE_TYPE::STAGE_12:
			m_arrScene[(UINT)SCENE_TYPE::STAGE_12] = new cScene_2;
			m_curScene = m_arrScene[(UINT)SCENE_TYPE::STAGE_12];
			break;
		case (INT)SCENE_TYPE::STAGE_13:
			m_arrScene[(UINT)SCENE_TYPE::STAGE_13] = new cScene_3;
			m_curScene = m_arrScene[(UINT)SCENE_TYPE::STAGE_13];
			break;
		case (INT)SCENE_TYPE::STAGE_14:
			m_arrScene[(UINT)SCENE_TYPE::STAGE_14] = new cScene_4;
			m_curScene = m_arrScene[(UINT)SCENE_TYPE::STAGE_14];
			break;
		case (INT)SCENE_TYPE::STAGE_15:
			m_arrScene[(UINT)SCENE_TYPE::STAGE_15] = new cScene_5;
			m_curScene = m_arrScene[(UINT)SCENE_TYPE::STAGE_15];
			break;
		case (INT)SCENE_TYPE::ENDING:
			m_arrScene[(UINT)SCENE_TYPE::ENDING] = new cScene_Ending;
			m_curScene = m_arrScene[(UINT)SCENE_TYPE::ENDING];
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
	if(t_MonsterCount >= 0)
		m_curScene->Render(_hdc);
	else
	{
		delete m_arrScene[m_curSceneLevel];
		m_arrScene[m_curSceneLevel++] = nullptr;		
		if (m_curSceneLevel == (INT)SCENE_TYPE::END)
			m_curSceneLevel = (INT)SCENE_TYPE::START;
		Init();
	}

	if (m_Score > 0)
		Score_Render(_hdc);
}

void cSceneManager::Score_Render(HDC _hdc)
{
	Graphics graphics_Score(_hdc);

	string Score_Str = to_string(m_Score);
	int w = m_ScoreImg->GetWidth() / 10;
	int h = m_ScoreImg->GetHeight();
	for (int i = 0 ; i < Score_Str.size() ; ++i)
	{
		graphics_Score.DrawImage(m_ScoreImg,
								Rect(160+22*i, 20, w, h),
								w*(Score_Str[i]-'0'), 0, w, h, UnitPixel, &m_imgAttr);
	}
}

