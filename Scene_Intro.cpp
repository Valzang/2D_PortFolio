#include "Scene_Intro.h"
#include "Scene_1.h"
#include "Player.h"
#include "KeyManager.h"
#include "Monster_Flying.h"
#include "Core.h"

cScene_Intro::cScene_Intro()
{
	SetCurSceneType((INT)SCENE_TYPE::START);
	SetSceneImg(L"Image/Scene/Intro.png");
	BGM_SetAndPlay(L"Sound/BGM/PB_OST_Intro.mp3");
}

cScene_Intro::~cScene_Intro()
{	
}

void cScene_Intro::Enter()
{
	// 몬스터 배치	
	SetMonsterSize(1);			// 몬스터 수
	cSceneManager::GetInstance()->SetScore(0);
}

void cScene_Intro::Exit()
{
}
