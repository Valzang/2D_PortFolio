#include "Monster_Boss.h"
#include "Scene.h"
#include "Wave.h"

cMonster_Boss::cMonster_Boss() : m_isDamaging(false), m_prevHP(4), m_isAttacking(false)
{
	m_MonsterImg = Image::FromFile((WCHAR*)L"Image/Monster/Monster_Boss.png");
	m_curGroupType = (INT)GROUP_TYPE::MONSTER_BOSS;
	SetScale(Vec2((float)m_MonsterImg->GetWidth() / 10.f, (float)m_MonsterImg->GetHeight()/2.f));
	Vec2 temp = GetScale();
	SetHP(4);
	SetImgAttr();
	SetDirection(1);
}

cMonster_Boss::~cMonster_Boss()
{
	int _Score = cSceneManager::GetInstance()->GetScore() + 5000;
	cSceneManager::GetInstance()->SetScore(_Score);
	if (m_MonsterImg != NULL)
	{
		delete m_MonsterImg;
		m_MonsterImg = nullptr;
	}
}

bool cMonster_Boss::Update()
{
	if (m_prevHP != GetHP())
	{
		m_isDamaging = true;
		m_prevHP = GetHP();
	}
	if(!m_isAttacking)
		SensePlayer();
	return true;
}

void cMonster_Boss::Render(HDC _hdc)
{
	static int curFrame = 0;
	Graphics graphics(_hdc);

	int w = m_MonsterImg->GetWidth() / 10;
	int h = m_MonsterImg->GetHeight() / 2;

	int xStart = (curFrame / 2) * w;

	int yStart = 0;
	if (m_isDamaging)
	{
		yStart = h;
		if (curFrame == 19)
			m_isDamaging = false;		
	}

	curFrame = curFrame >= 19 ? 0 : curFrame + 1;

	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();
	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_MonsterImg, Rect((int)Pos.x - (int)Scale.x / 2, (int)Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());
}

void cMonster_Boss::SensePlayer()
{
	if (cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[(INT)GROUP_TYPE::PLAYER].size() == 0)
		return;
	cObject* curPlayer = cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[(INT)GROUP_TYPE::PLAYER][0];
	float curPlayer_x = curPlayer->GetPos().x;
	float curPlayer_y = curPlayer->GetPos().y;

	float curMonster_x = GetPos().x;
	float curMonster_top = GetPos().y - GetScale().y / 2.f;
	float curMonster_down = GetPos().y + GetScale().y / 2.f;

	if (curPlayer_y <= curMonster_down
		&& curPlayer_y >= curMonster_top)
	{
		CreateWave();
	}
}

void cMonster_Boss::CreateWave()
{
	m_isAttacking = true;
	Vec2 Wave_Pos = GetPos();
	if (GetDirection() == 1)
		Wave_Pos.x += GetScale().x;
	else
		Wave_Pos.x -= GetScale().x;
	// 웨이브 오브젝트
	cWave* Wave = new cWave(Wave_Pos, GetDirection(), this);

	cScene* curScene = cSceneManager::GetInstance()->GetCurScene();
	curScene->AddObject(Wave, GROUP_TYPE::WAVE);
}
