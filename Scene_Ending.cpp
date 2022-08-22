#include "Scene_Ending.h"
#include "Scene_Intro.h"
#include "KeyManager.h"
#include "Core.h"

cScene_Ending::cScene_Ending()
{
	SetCurSceneType((INT)SCENE_TYPE::ENDING);
	SetSceneImg(L"Image/Scene/Ending.png");
	BGM_SetAndPlay(L"Sound/BGM/PB_OST_Ending.mp3");
}

cScene_Ending::~cScene_Ending()
{
}

void cScene_Ending::Enter()
{
	// 몬스터 배치	
	SetMonsterSize(1);			// 몬스터 수
}

