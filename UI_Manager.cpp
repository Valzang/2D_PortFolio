#include "UI_Manager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Player.h"


cUI_Manager::cUI_Manager() : m_curPlayer(nullptr), m_Score(0), m_PlayerHP(0), m_imgAttr(),
							m_PlayerLife_Pos(), m_PlayerLife_Scale(), m_PlayerLifeImg(nullptr),
							m_LifeCount_Pos(), m_LifeCount_Scale(), m_PlayerLifeCountImg(nullptr)
{
	m_PlayerLifeImg = Image::FromFile((WCHAR*)L"Image/Player_HP_count.png");
	m_PlayerLife_Scale = Vec2((float)m_PlayerLifeImg->GetWidth(), (float)m_PlayerLifeImg->GetHeight());

	m_PlayerLifeCountImg = Image::FromFile((WCHAR*)L"Image/Number.png");
	m_LifeCount_Scale = Vec2((float)m_PlayerLifeCountImg->GetWidth()/10.f, (float)m_PlayerLifeCountImg->GetHeight());

	SetImgAttr();
}

cUI_Manager::~cUI_Manager()
{
	if (m_PlayerLifeImg != NULL)
	{
		delete m_PlayerLifeImg;
		m_PlayerLifeImg = nullptr;
	}
	if (m_PlayerLifeCountImg != NULL)
	{
		delete m_PlayerLifeCountImg;
		m_PlayerLifeCountImg = nullptr;
	}
}

void cUI_Manager::Init()
{
	Set_PlayerLife_Pos(Vec2(Get_LifeCount_Scale().x*1.5f, Get_LifeCount_Scale().y*1.5f));
	Set_LifeCount_Pos(Vec2(Get_PlayerLife_Pos().x + Get_PlayerLife_Scale().x/2.f, Get_PlayerLife_Pos().y + 7.f));
	if(cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[(INT)GROUP_TYPE::PLAYER].size() != 0)
		m_curPlayer = dynamic_cast<cPlayer*>(cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[(INT)GROUP_TYPE::PLAYER][0]);
}

void cUI_Manager::Update()
{
	if(m_curPlayer != NULL)
		m_PlayerHP = m_curPlayer->GetHP();
}

void cUI_Manager::Render(HDC _hdc)
{
	if (m_curPlayer == NULL)
		return;
	Graphics graphics_Life(_hdc);
	Graphics graphics_LifeCount(_hdc);

	int Life_w = (int)m_PlayerLife_Scale.x;
	int Life_h = (int)m_PlayerLife_Scale.y;

	Vec2 LifeCount_Pos = m_LifeCount_Pos;
	Vec2 LifeCount_Scale = m_LifeCount_Scale;

	int LifeCount_w = (int)m_LifeCount_Scale.x;
	int LifeCount_h = (int)m_LifeCount_Scale.y;

	int xStart = LifeCount_w * m_PlayerHP;

	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics_Life.DrawImage(m_PlayerLifeImg, 
							Rect((int)m_PlayerLife_Pos.x - Life_w / 2,	(int)m_PlayerLife_Pos.y - Life_h / 2,Life_w, Life_h),
							0, 0, Life_w, Life_h, UnitPixel, GetImgAttr());
	graphics_LifeCount.DrawImage(m_PlayerLifeCountImg, 
								 Rect((int)m_LifeCount_Pos.x - LifeCount_w / 2, (int)m_LifeCount_Pos.y - LifeCount_h / 2, LifeCount_w, LifeCount_h), 
								 xStart, 0, LifeCount_w, LifeCount_h, UnitPixel, GetImgAttr());
}
