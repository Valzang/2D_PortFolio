#include "Scene_Start.h"
#include "Player.h"
#include "Monster.h"

#include "Core.h"

void cScene_Start::Enter()
{
	// Object 추가
	cObject* PlayerObj = new cPlayer;

	// Object 위치, 크기 설정
	PlayerObj->SetPos(Vec2 { 640.f, 384.f });
	PlayerObj->SetScale(Vec2 {100.f, 100.f});
	AddObject(PlayerObj, GROUP_TYPE::DEFAULT);


	// 몬스터 배치
	int MonCount = 10;

	float MoveDist = 40.f;
	float ObjectScale = 81.f;

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
		//MonsterObj->SetScale(Vec2 { ObjectScale, ObjectScale });
		AddObject(MonsterObj, GROUP_TYPE::DEFAULT);		
	}
	

}

void cScene_Start::Exit()
{
}
