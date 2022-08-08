#include "Scene_Start.h"
#include "Player.h"
#include "Monster.h"
#include "Platform_SideWall.h"
#include "Platform_Under.h"
#include "Platform_Rotate.h"

#include "Core.h"

cScene_Start::cScene_Start()
{
	SetSceneImg(L"Image/Scene1.png");
}

cScene_Start::~cScene_Start()
{
}

void cScene_Start::Enter()
{
	// �÷��̾� �߰� �� ��ġ ����
	cPlayer* PlayerObj = new cPlayer;
	PlayerObj->SetPos(Vec2 { 640.f, 300.f });
	AddObject(PlayerObj, GROUP_TYPE::PLAYER);


	// ���� ��ġ	
	SetMonsterSize(10);			// ���� ��
	float MoveDist = 40.f;		// ������ �ൿ �ݰ�
	float ObjectScale = 81.f;	// ���� ������ ũ��

	// ȭ�� ũ�⿡ �°� ��ġ�ϱ�
	Vec2 Resolution = cCore::GetInstance()->GetResolution();
	float temp = (Resolution.x - ((MoveDist+ ObjectScale /2.f) * 2)) / (float)(GetMonsterSize()-1);

	//Monster Object �߰�
	cMonster* MonsterObj = nullptr;
	for (int i = 0; i < GetMonsterSize(); ++i)
	{
		MonsterObj = new cMonster;
		MonsterObj->SetPos(Vec2 { (MoveDist + ObjectScale / 2.f) + temp*(float)i, 50.f });
		MonsterObj->SetCenterPos(MonsterObj->GetPos());
		MonsterObj->SetMaxDist(MoveDist);
		AddObject(MonsterObj, GROUP_TYPE::MONSTER);		
	}

	//SetPlatformSize(6);

	//Platform Object �߰�
	cPlatform* PlatformObj = nullptr;
	PlatformObj = new cPlatform_Rotate;
	PlatformObj->SetPos(Vec2 { Resolution.x / 2.f, Resolution.y / 2.f+120 }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM_ROTATE);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2 { Resolution.x / 2.f - 360, Resolution.y / 2.f + 120 }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f + 360, Resolution.y / 2.f + 120 }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform_SideWall;
	PlatformObj->SetPos(Vec2{ (PlatformObj->GetScale().x / 2.f), Resolution.y / 2.f });
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform_SideWall;
	PlatformObj->SetPos(Vec2{ Resolution.x - (PlatformObj->GetScale().x / 2.f), Resolution.y / 2.f }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	PlatformObj = new cPlatform_Under;
	PlatformObj->SetPos(Vec2{ Resolution.x / 2.f, Resolution.y - (PlatformObj->GetScale().y / 2.f) }); // �߽���ǥ..?
	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);

	//for (; i < GetPlatformSize(); ++i)
	//{
	//	PlatformObj = new cPlatform;
	//	PlatformObj->SetPos(Vec2 { (MoveDist + ObjectScale / 2.f) + temp * (float)i, 50.f });
	//	PlatformObj->SetCenterPos(PlatformObj->GetPos());
	//	AddObject(PlatformObj, GROUP_TYPE::PLATFORM);
	//}
}

void cScene_Start::Exit() // �����鼭 ���� �÷��̾ ���� ������ �� �Ŵ����� �Ѱ������ ��..?
{
}
