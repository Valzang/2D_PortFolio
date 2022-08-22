#include "Scene_4.h"
#include "Player.h"
#include "Monster.h"
#include "Monster_Flying.h"
#include "Monster_Thorn.h"
#include "Monster_Runner.h"
#include "Monster_SpitFire.h"
#include "Monster_Boss.h"
#include "Platform_SideWall.h"
#include "Platform_Under.h"
#include "Platform_Rotate.h"
#include "Platform_Broken.h"

#include "Core.h"

cScene_4::cScene_4()
{
	SetCurSceneType((INT)SCENE_TYPE::STAGE_14);
	SetSceneImg(L"Image/Scene/Scene4.png");
	BGM_SetAndPlay(L"Sound/BGM/PB_OST_STAGE4.mp3");
}

cScene_4::~cScene_4()
{
	Exit();
}

void cScene_4::Enter()
{
	// 플레이어 추가 및 위치 설정	

	// 몬스터 배치	
	SetMonsterSize(7);			// 몬스터 수

	// 화면 크기에 맞게 배치하기
	Vec2 Resolution = cCore::GetInstance()->GetResolution();

	// Monster Object 추가 ===================================================================================================
	cMonster* MonsterObj = nullptr;
	MonsterObj = new cMonster_Thorn;
	MonsterObj->SetPos(Vec2{ 800.f, 200.f });
	MonsterObj->SetFirstY(MonsterObj->GetPos().y);
	AddObject(MonsterObj, GROUP_TYPE::MONSTER);

	MonsterObj = new cMonster_Thorn;
	MonsterObj->SetPos(Vec2{ 400.f, 200.f });
	MonsterObj->SetFirstY(MonsterObj->GetPos().y);
	AddObject(MonsterObj, GROUP_TYPE::MONSTER);

	MonsterObj = new cMonster_Thorn;
	MonsterObj->SetPos(Vec2{ 600.f, 200.f });
	MonsterObj->SetFirstY(MonsterObj->GetPos().y);
	AddObject(MonsterObj, GROUP_TYPE::MONSTER);

	MonsterObj = new cMonster_SpitFire;
	MonsterObj->SetPos(Vec2{ Resolution.x - 100.f, 360.f });
	AddObject(MonsterObj, GROUP_TYPE::MONSTER);

	MonsterObj = new cMonster_SpitFire;
	MonsterObj->SetPos(Vec2{ 200.f, 360.f });
	AddObject(MonsterObj, GROUP_TYPE::MONSTER);

	MonsterObj = new cMonster_Runner;
	MonsterObj->SetPos(Vec2{ Resolution.x - 200.f, 500.f });
	AddObject(MonsterObj, GROUP_TYPE::MONSTER);
	
	MonsterObj = new cMonster_Runner;
	MonsterObj->SetPos(Vec2{ 200.f, 500.f });
	AddObject(MonsterObj, GROUP_TYPE::MONSTER);

	// 플레이어 ===============================================

	int HP = cSceneManager::GetInstance()->GetPlayerLife();
	cPlayer* PlayerObj = new cPlayer(Vec2(640.f, 540.f), HP);
	AddObject(PlayerObj, GROUP_TYPE::PLAYER);
	// Platform Object 추가	===================================================================================================

	// 3rd Floor ===================================================================

	cPlatform* PlatformObj = nullptr;

	// 2nd Floor ===================================================================
	PlatformObj = new cPlatform_Rotate;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f, Resolution.y / 2.f - 100.f }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);// _ROTATE);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f - 360, Resolution.y / 2.f - 100.f }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f - 400, Resolution.y / 2.f - 100.f }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f + 360, Resolution.y / 2.f - 100.f }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f + 400, Resolution.y / 2.f - 100.f }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);


	// 1st Floor ===================================================================
	PlatformObj = new cPlatform_Rotate;
	PlatformObj->SetPos(Vec2{ 640.f, Resolution.y / 2.f + 60.f }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);// _ROTATE);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f - 360.f, Resolution.y / 2.f + 60.f }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f - 400.f, Resolution.y / 2.f + 60.f }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f + 400.f, Resolution.y / 2.f + 60.f }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f + 360.f, Resolution.y / 2.f + 60.f }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);


	// Zero Floor ==================================================================

	PlatformObj = new cPlatform_Under;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f, Resolution.y - 120.f }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

}

