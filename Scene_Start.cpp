#include "Scene_Start.h"
#include "Player.h"
#include "Monster.h"

#include "Core.h"

cScene_Start::cScene_Start()
{
	SetSceneImg(L"Image/Scene1.png");
}

cScene_Start::~cScene_Start()
{
	DeleteSceneImg();
}

void cScene_Start::Enter()
{
	// 플레이어 추가 및 위치 설정
	cPlayer* PlayerObj = new cPlayer;
	PlayerObj->SetPos(Vec2 { 640.f, 384.f });
	AddObject(PlayerObj, GROUP_TYPE::PLAYER);


	// 몬스터 배치
	int MonCount = 10;			// 몬스터 수
	float MoveDist = 40.f;		// 몬스터의 행동 반경
	float ObjectScale = 81.f;	// 몬스터 사진의 크기

	// 화면 크기에 맞게 배치하기
	Vec2 Resolution = CCore::GetInstance()->GetResolution();
	float temp = (Resolution.x - ((MoveDist+ ObjectScale /2.f) * 2)) / (float)(MonCount-1);

	//Monster Object 추가
	cMonster* MonsterObj = nullptr;
	for (int i = 0; i < MonCount; ++i)
	{
		MonsterObj = new cMonster;
		MonsterObj->SetPos(Vec2 { (MoveDist + ObjectScale / 2.f) + temp*(float)i, 50.f });
		MonsterObj->SetCenterPos(MonsterObj->GetPos());
		MonsterObj->SetMaxDist(MoveDist);
		AddObject(MonsterObj, GROUP_TYPE::MONSTER);		
	}
}

void cScene_Start::Exit()
{
}
