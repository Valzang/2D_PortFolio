#include "Scene_5.h"
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

cScene_5::cScene_5()
{
	SetCurSceneType((INT)SCENE_TYPE::STAGE_15);
	SetSceneImg(L"Image/Scene/Scene5.png");
	BGM_SetAndPlay(L"Sound/BGM/PB_OST_STAGE_BOSS.mp3");
}

cScene_5::~cScene_5()
{
	Exit();
}

void cScene_5::Enter()
{
	// �÷��̾� �߰� �� ��ġ ����
	int HP = cSceneManager::GetInstance()->GetPlayerLife();
	cPlayer* PlayerObj = new cPlayer(Vec2(640.f, 540.f), HP);
	AddObject(PlayerObj, GROUP_TYPE::PLAYER);


	// ���� ��ġ	
	SetMonsterSize(1);			// ���� ��

	// ȭ�� ũ�⿡ �°� ��ġ�ϱ�
	Vec2 Resolution = cCore::GetInstance()->GetResolution();

	// Monster Object �߰� ===================================================================================================
	cMonster* MonsterObj = nullptr;
	MonsterObj = new cMonster_Boss;
	MonsterObj->SetPos(Vec2{ 1100.f, 380.f });
	AddObject(MonsterObj, GROUP_TYPE::MONSTER);


	// Platform Object �߰�	===================================================================================================

	// 3rd Floor ===================================================================

	cPlatform* PlatformObj = nullptr;
	PlatformObj = new cPlatform_Rotate;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f, Resolution.y / 2.f - 230 }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);// _ROTATE);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f - 360, Resolution.y / 2.f - 230 }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f + 360, Resolution.y / 2.f - 230 }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	// 2nd Floor ===================================================================
	PlatformObj = new cPlatform_Rotate;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f, Resolution.y / 2.f - 80 }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);// _ROTATE);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f - 360, Resolution.y / 2.f - 80 }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f + 360, Resolution.y / 2.f - 80 }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);


	// 1st Floor ===================================================================
	PlatformObj = new cPlatform_Rotate;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f, Resolution.y / 2.f + 70 }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);// _ROTATE);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f - 360.f, Resolution.y / 2.f + 70 }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f + 360, Resolution.y / 2.f + 70 }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);


	// Zero Floor ==================================================================

	PlatformObj = new cPlatform_SideWall;
	PlatformObj->SetPos(Vec2{ (PlatformObj->GetScale().x / 2.f), Resolution.y / 2.f });
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform_SideWall;
	PlatformObj->SetPos(Vec2{ Resolution.x - (PlatformObj->GetScale().x / 2.f), Resolution.y / 2.f }); // �߽���ǥ..?	
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform_Under;
	//float temp = ;
	//float temp2 = Resolution.y - PlatformObj->GetScale().y / 2.f;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f, Resolution.y - 120.f }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

}
