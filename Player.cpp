#include "Player.h"
#include "TimeManager.h"
#include "KeyManager.h"

#include "Bomb.h"

#include "SceneManager.h"
#include "Scene.h"

void cPlayer::Update()
{
	Vec2 Pos = GetPos();

	// DELTA_TIME으로 시간동기화 해서 이동

	if (KEY_CHECK(KEY::I, KEY_STATE::HOLD))
	{
		Pos.y -= 200.f * DELTA_TIME;
	}
	if (KEY_CHECK(KEY::K, KEY_STATE::HOLD))
	{
		Pos.y += 200.f * DELTA_TIME;
	}
	if (KEY_CHECK(KEY::J, KEY_STATE::HOLD))
	{
		Pos.x -= 200.f * DELTA_TIME;
	}
	if (KEY_CHECK(KEY::L, KEY_STATE::HOLD))
	{
		Pos.x += 200.f * DELTA_TIME;
	}
	

	if (KEY_CHECK(KEY::A, KEY_STATE::DOWN))
	{
		CreateBomb();
	}
	SetPos(Pos);
}

void cPlayer::CreateBomb()
{
	Vec2 bomb_Pos = GetPos();
	bomb_Pos.y -= GetScale().y / 2.f;

	// 폭탄 오브젝트
	cBomb* bomb = new cBomb;
	bomb->SetPos(bomb_Pos);
	bomb->SetScale(Vec2(25.f, 25.f));
	bomb->SetDirection(true);

	cScene* curScene = cSceneManager::GetInstance()->GetCurScene();
	curScene->AddObject(bomb, GROUP_TYPE::DEFAULT);
}
