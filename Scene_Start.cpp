#include "Scene_Start.h"
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

cScene_Start::cScene_Start()
{
	SetCurSceneType((INT)SCENE_TYPE::STAGE_11);
	SetSceneImg(L"Image/Scene/Scene1.png");
	BGM_SetAndPlay(L"Sound/BGM/PB_OST_STAGE1.mp3");
}

cScene_Start::~cScene_Start()
{	
}

void cScene_Start::Enter()
{
	// 플레이어 추가 및 위치 설정
	cPlayer* PlayerObj = new cPlayer(Vec2(640.f,600.f));
	AddObject(PlayerObj, GROUP_TYPE::PLAYER);


	// 몬스터 배치	
	SetMonsterSize(5);			// 몬스터 수

	// 화면 크기에 맞게 배치하기
	Vec2 Resolution = cCore::GetInstance()->GetResolution();
	cUI_Manager::GetInstance()->Init();

	// Monster Object 추가 ===================================================================================================
	cMonster* MonsterObj = nullptr;
	MonsterObj = new cMonster_Flying;
	MonsterObj->SetPos(Vec2{ 200.f, Resolution.y - MonsterObj->GetScale().y * 2.5f });
	//Vec2 curcurPos = MonsterObj->GetPos();
	MonsterObj->SetFirstY(MonsterObj->GetPos().y);

	AddObject(MonsterObj, GROUP_TYPE::MONSTER);

	MonsterObj = new cMonster_Thorn;
	MonsterObj->SetPos(Vec2 { 200.f, Resolution.y - MonsterObj->GetScale().y * 4.f });

	AddObject(MonsterObj, GROUP_TYPE::MONSTER);

	MonsterObj = new cMonster_Runner;
	MonsterObj->SetPos(Vec2 { 200.f, Resolution.y - MonsterObj->GetScale().y * 8.8f });

	AddObject(MonsterObj, GROUP_TYPE::MONSTER);
	

	MonsterObj = new cMonster_Boss;
	//MonsterObj = new cMonster_SpitFire;
	MonsterObj->SetPos(Vec2 { 200.f, Resolution.y - MonsterObj->GetScale().y * 5.f });

	AddObject(MonsterObj, GROUP_TYPE::MONSTER);


	// Platform Object 추가	===================================================================================================

	// 3rd Floor ===================================================================

	cPlatform* PlatformObj = nullptr;
	PlatformObj = new cPlatform_Rotate;
	PlatformObj->SetPos(Vec2 { Resolution.x / 2.f, Resolution.y / 2.f - 180 }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);// _ROTATE);


	PlatformObj = new cPlatform_Broken;
	PlatformObj->SetPos(Vec2 { Resolution.x / 2.f + 360, Resolution.y - 340.f }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform_Broken;
	PlatformObj->SetPos(Vec2 { Resolution.x / 2.f + 300, Resolution.y - 340.f }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);



	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2 { Resolution.x / 2.f - 360, Resolution.y / 2.f - 180 }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2 { Resolution.x / 2.f + 360, Resolution.y / 2.f - 180 }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	// 2nd Floor ===================================================================
	PlatformObj = new cPlatform_Rotate;
	PlatformObj->SetPos(Vec2 { Resolution.x / 2.f, Resolution.y / 2.f - 30 }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);// _ROTATE);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2 { Resolution.x / 2.f - 360, Resolution.y / 2.f - 30 }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2 { Resolution.x / 2.f + 360, Resolution.y / 2.f - 30 }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);


	// 1st Floor ===================================================================
	PlatformObj = new cPlatform_Rotate;
	PlatformObj->SetPos(Vec2 { Resolution.x / 2.f, Resolution.y / 2.f+120 }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);// _ROTATE);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2 { Resolution.x / 2.f - 360, Resolution.y / 2.f + 120 }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f + 360, Resolution.y / 2.f + 120 }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);


	// Zero Floor ==================================================================

	PlatformObj = new cPlatform_SideWall;
	PlatformObj->SetPos(Vec2{ (PlatformObj->GetScale().x / 2.f), Resolution.y / 2.f });
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform_SideWall;
	PlatformObj->SetPos(Vec2{ Resolution.x - (PlatformObj->GetScale().x / 2.f), Resolution.y / 2.f }); // 중심좌표..?	
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform_Under;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f, Resolution.y - (PlatformObj->GetScale().y / 2.f) }); // 중심좌표..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

}

void cScene_Start::Exit() // 나가면서 현재 플레이어에 대한 정보를 씬 매니저에 넘겨줘야할 듯..?
{
}
