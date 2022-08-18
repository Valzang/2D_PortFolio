#include "Scene_Intro.h"
#include "Scene_Start.h"
#include "Player.h"
#include "KeyManager.h"
#include "Monster_Flying.h"
#include "Core.h"

cScene_Intro::cScene_Intro()
{
	SetCurSceneType((INT)SCENE_TYPE::START);
	SetSceneImg(L"Image/Intro.png");
	BGM_SetAndPlay(L"Sound/BGM/PB_OST_STAGE_PVP.mp3");
}

cScene_Intro::~cScene_Intro()
{	
}

//void cScene_Intro::Update()
//{
//	//if (KEY_CHECK(KEY::A, KEY_STATE::DOWN))
//	
//}
//
//void cScene_Intro::Render(HDC _hdc)
//{
//	//Gdiplus::Graphics graphics(_hdc);
//	//Gdiplus::Graphics graphics_Alram(_hdc);
//	//int w = GetSceneImg()->GetWidth();
//	//int h = GetSceneImg()->GetHeight();
//	//
//	//graphics.DrawImage(GetSceneImg(), Rect(0, 0, w, h), 0, 0, w, h, UnitPixel, &m_imgAttr);
//	//
//	//w = (int)Alram_Scale.x;
//	//h = (int)Alram_Scale.y;
//	// // Rect가 위치
//	//graphics_Alram.DrawImage(m_IntroAlramImg, Rect((int)Alram_Pos.x - w/2, (int)Alram_Pos.y - h / 2, (int)Alram_Pos.x + w / 2, (int)Alram_Pos.y + h / 2), 0, 0, w, h, UnitPixel, &m_imgAttr);
//}

void cScene_Intro::Enter()
{
		// 플레이어 추가 및 위치 설정
	//cPlayer* PlayerObj = new cPlayer(Vec2(640.f, 400.f));
	//AddObject(PlayerObj, GROUP_TYPE::PLAYER);

	// 몬스터 배치	
	SetMonsterSize(1);			// 몬스터 수

	// 화면 크기에 맞게 배치하기
	Vec2 Resolution = cCore::GetInstance()->GetResolution();

	// Monster Object 추가 ===================================================================================================
	cMonster* MonsterObj = nullptr;
	MonsterObj = new cMonster_Flying;
	MonsterObj->SetPos(Vec2 { 200.f, Resolution.y - MonsterObj->GetScale().y * 2.5f });
	//Vec2 curcurPos = MonsterObj->GetPos();
	MonsterObj->SetFirstY(MonsterObj->GetPos().y);

	AddObject(MonsterObj, GROUP_TYPE::MONSTER);

}

void cScene_Intro::Exit()
{
}
