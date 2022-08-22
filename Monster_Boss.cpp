#include "Monster_Boss.h"
#include "Monster_Flying.h"
#include "Monster_Thorn.h"
#include "Monster_Runner.h"
#include "Monster_SpitFire.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Wave.h"

cMonster_Boss::cMonster_Boss() : m_prevHP(4), m_isAttacking(false), m_curFrame(0), m_NonDamage(false), m_AttackTime(0.f), DiffPos(), m_PosCount(0)
{
	m_MonsterImg = Image::FromFile((WCHAR*)L"Image/Monster/Monster_Boss.png");
	m_curGroupType = (INT)GROUP_TYPE::MONSTER_BOSS;
	SetScale(Vec2((float)m_MonsterImg->GetWidth() / 10.f, (float)m_MonsterImg->GetHeight()/2.f));
	Vec2 temp = GetScale();
	SetHP(4);
	SetImgAttr();
	SetDirection(-1);	
	DiffPos[0] = Vec2(180.f, 80.f); 
	DiffPos[1] = Vec2(1100.f, 230.f); 
	DiffPos[2] = Vec2(180.f, 230.f);
	DiffPos[3] = Vec2(1100.f, 80.f);
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
	cout << "현재 몬스터 수 : " << cSceneManager::GetInstance()->GetCurScene()->GetMonsterSize() << "\t보스 HP : " << GetHP() << '\n';
	if (GetHP() < 0 && !m_NonDamage)
		return false;

	if (cSceneManager::GetInstance()->GetCurScene()->GetMonsterSize() == 1 && m_NonDamage)
	{
		m_NonDamage = false;
	}	

	if (m_prevHP != GetHP())
	{		
		if (m_NonDamage)
		{
			SetDamaging(false);
			SetHP(GetHP() + 1);
		}
		else
		{			
			m_prevHP = GetHP();
			BGM_SetAndPlay(L"Sound/EFFECT/Boss_Damage.wav");
			m_curFrame = 0;
		}
		
		
	}
	if(!m_isAttacking && !isDamaging() && m_AttackTime == 0.f && !m_NonDamage)
		SensePlayer();

	if (m_AttackTime > 0.f)
		m_AttackTime -= DELTA_TIME;
	else if (m_AttackTime < 0.f)
		m_AttackTime = 0.f;


	return true;
}

void cMonster_Boss::Render(HDC _hdc)
{
	Graphics graphics(_hdc);

	int w = m_MonsterImg->GetWidth() / 10;
	int h = m_MonsterImg->GetHeight() / 2;

	int xStart = (m_curFrame / 2) * w;
	int yStart = 0;
	if (isDamaging() && !m_NonDamage)
	{
		xStart = (m_curFrame / 3) * w;
		yStart = h;
		if (m_curFrame == 29)
		{
			SetDamaging(false);
			SetDirection(-GetDirection());
			m_MonsterImg->RotateFlip(RotateNoneFlipX);
			SetPos(DiffPos[m_PosCount]);

			m_NonDamage = true;
			cSceneManager::GetInstance()->GetCurScene()->SetMonsterSize(4);
			for (int i = 0; i < 4; ++i)
			{
				if (i == m_PosCount)
					continue;
				cMonster* MonsterObj = nullptr;
				switch (GetHP())
				{
					case 3:
						MonsterObj = new cMonster_Flying;
						break;
					case 2:
						MonsterObj = new cMonster_Thorn;
						break;
					case 1:
						MonsterObj = new cMonster_Runner;
						break;
					case 0:
						MonsterObj = new cMonster_SpitFire;
						break;
				}
				MonsterObj->SetPos(DiffPos[i]);
				MonsterObj->SetFirstY(MonsterObj->GetPos().y);
				cSceneManager::GetInstance()->GetCurScene()->AddObject(MonsterObj, GROUP_TYPE::MONSTER);
			}
			++m_PosCount;
		}
		m_curFrame = m_curFrame >= 29 ? 0 : m_curFrame + 1;
	}
	else
		m_curFrame = m_curFrame >= 19 ? 0 : m_curFrame + 1;

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
		Wave_Pos.x += GetScale().x/2.f;
	else
		Wave_Pos.x -= GetScale().x/2.f;
	// 웨이브 오브젝트
	cWave* Wave = new cWave(Wave_Pos, GetDirection(), this);

	cScene* curScene = cSceneManager::GetInstance()->GetCurScene();
	curScene->AddObject(Wave, GROUP_TYPE::WAVE);
}
