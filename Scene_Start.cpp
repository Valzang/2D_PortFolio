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
	// �÷��̾� �߰� �� ��ġ ����
	cPlayer* PlayerObj = new cPlayer;
	PlayerObj->SetPos(Vec2 { 640.f, 384.f });
	AddObject(PlayerObj, GROUP_TYPE::PLAYER);


	// ���� ��ġ
	SetMonsterSize(10);			// ���� ��
	float MoveDist = 40.f;		// ������ �ൿ �ݰ�
	float ObjectScale = 81.f;	// ���� ������ ũ��

	// ȭ�� ũ�⿡ �°� ��ġ�ϱ�
	Vec2 Resolution = CCore::GetInstance()->GetResolution();
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
}

void cScene_Start::Exit() // �����鼭 ���� �÷��̾ ���� ������ �� �Ŵ����� �Ѱ������ ��..?
{
}
