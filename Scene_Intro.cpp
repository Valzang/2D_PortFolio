#include "Scene_Intro.h"
#include "Scene_Start.h"
#include "KeyManager.h"

cScene_Intro::cScene_Intro() : m_IntroAlramImg(nullptr), Alram_Pos(Vec2(640.f, 550.f)), Alram_Scale()
{
}

cScene_Intro::~cScene_Intro()
{
	if (m_IntroAlramImg != NULL)
	{
		delete m_IntroAlramImg;
		m_IntroAlramImg = nullptr;
	}
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
//	// // Rect°¡ À§Ä¡
//	//graphics_Alram.DrawImage(m_IntroAlramImg, Rect((int)Alram_Pos.x - w/2, (int)Alram_Pos.y - h / 2, (int)Alram_Pos.x + w / 2, (int)Alram_Pos.y + h / 2), 0, 0, w, h, UnitPixel, &m_imgAttr);
//}

void cScene_Intro::Enter()
{
	SetSceneImg(L"Image/Intro.png");
	m_IntroAlramImg = Image::FromFile(L"Image/Intro_Alram.png");
	Alram_Scale.x = (float)m_IntroAlramImg->GetWidth();
	Alram_Scale.y = (float)m_IntroAlramImg->GetHeight();
	BGM_SetAndPlay(L"Sound/BGM/PB_OST_STAGE_PVP.mp3");
}

void cScene_Intro::Exit()
{
}
