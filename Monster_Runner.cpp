#include "Monster_Runner.h"
#include "Scene.h"
#include "SceneManager.h"

enum Behavior_Tree { Stay, Change_Direction, Forward, Retreat, Run };
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> state(0, 2);
uniform_int_distribution<int> forward_time(2, 4);
uniform_int_distribution<int> stay_time(1, 2);

cMonster_Runner::cMonster_Runner()
	:m_BehaviorTime(), m_CurBehaviorState(0), m_ChangeBehavior(true)
{
	m_MonsterImg = Image::FromFile((WCHAR*)L"Image/Monster_Runner.png");	
	m_curGroupType = (INT)GROUP_TYPE::MONSTER_RUNNER;
	SetScale(Vec2((float)m_MonsterImg->GetWidth() / 4.f, (float)m_MonsterImg->GetHeight()/ 2.f));
	SetHP(1);
	SetImgAttr();
	SetDirection(1);
}

cMonster_Runner::~cMonster_Runner()
{
	if (m_MonsterImg != NULL)
	{
		delete m_MonsterImg;
		m_MonsterImg = nullptr;
	}
}

bool cMonster_Runner::Update()
{
	if (GetHP() <= 0)
		return false;
	Vec2 CurPos = GetPos();

	if (GetRotating())
	{
		float diff = CurPos.x - GetRotator()->GetPos().x;
		m_CurBehaviorState = Stay;

		// �÷����� �߽ɺ��� ������ ���� ��
		if (diff > 0)
		{
			//������ ���� ���ư����� ��
			if (GetRotateDir())
			{
				if (GetDirection() == 1)
				{
					SetDirection(-1);
					m_MonsterImg->RotateFlip(RotateNoneFlipX);
				}				
				m_Speed = (m_Speed + diff) * 3.f;
				m_Dir.y = -1.2f;
				SetOnPlatform(false);
				SetShoot(true);
			}
			//������ �Ʒ��� �������� �� ��
			else
			{
				SetOnPlatform(false);
				SetThruRotate(true);
			}
		}
		// �÷����� �߽ɺ��� ������ ���� ��
		else
		{
			//������ ���� ���ư����� ��
			if (GetRotateDir())
			{
				if (GetDirection() == -1)
				{
					SetDirection(1);
					m_MonsterImg->RotateFlip(RotateNoneFlipX);
				}
				m_Speed = (m_Speed + -diff) * 3.f;
				m_Dir.y = -1.2f;
				SetOnPlatform(false);
				SetShoot(true);				
			}
			//������ �Ʒ��� �������� �� ��
			else
			{
				SetOnPlatform(false);
				SetThruRotate(true);
			}
		}
		SetRotating(false);
	}
	if (GetShoot())
	{		
		CurPos.y += 800.f * m_Dir.y * DELTA_TIME;
		if (m_Dir.y <= 2)
			// ������ �׸��Բ� ������ ������ ���� ��� ���������ֱ�.
			m_Dir.y += 6.f * DELTA_TIME;
		if (GetDirection() == 1) // ���� �����϶�
			CurPos.x += (float)(m_Speed * DELTA_TIME); // �ٶ󺸴� ���⿡ �°Բ�			
		else // ���� ������ ��
			CurPos.x -= (float)(m_Speed  * DELTA_TIME); // �ٶ󺸴� ���⿡ �°Բ�								
	}
	else
	{
		if (!isOnPlatform() || GetThruRotate())
			CurPos.y += 800.f * DELTA_TIME;
		else
			m_Speed = 200.f;

		switch (m_CurBehaviorState)
		{
			case Forward:
				CurPos.x += DELTA_TIME * m_Speed * GetDirection();
				break;
				
			case Run:
				CurPos.x += DELTA_TIME * m_Speed * GetDirection();
				CollisionCheck(this, (INT)GROUP_TYPE::PLAYER);
				break;
			case Retreat:
				CurPos.x -= DELTA_TIME * (m_Speed / 1.5f) * GetDirection();
				break;
			default:
				break;
		}

		m_BehaviorTime -= DELTA_TIME;


		if (!SenseBomb())
			SensePlayer();

		if (m_BehaviorTime <= 0.f && m_CurBehaviorState != Run)
			m_ChangeBehavior = true;

		if (m_ChangeBehavior)
			ChooseBehavior();
	}

	

	SetPos(CurPos);
	CollisionCheck(this, (INT)GROUP_TYPE::PLATFORM);	
	SetPosOtherside();
	return true;
}

void cMonster_Runner::Render(HDC _hdc)
{
	static int curFrame = 0;
	Graphics graphics(_hdc);

	int w = m_MonsterImg->GetWidth() / 4;
	int h = m_MonsterImg->GetHeight() / 2;

	int xStart = (curFrame/2) * w;
	curFrame = curFrame >= 7 ? 0 : curFrame + 1;

	int yStart = 0;

	if (m_CurBehaviorState == Run)
		yStart = h;

	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();
	//											�������� ���ݸ�ŭ ���ִ� ������ �⺻������ �׸���� ���ʻ�ܿ������� �׷��ֱ� ������ �׸��� ������ �ٲ��ֱ� ����.
	graphics.DrawImage(m_MonsterImg, Rect((int)Pos.x - (int)Scale.x / 2, (int)Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());
}


void cMonster_Runner::ChooseBehavior()
{
	switch (state(gen))
	{
		case Stay:
		{
			m_CurBehaviorState = Stay;
			m_BehaviorTime = (double)stay_time(gen);
			m_ChangeBehavior = false;
		}
		break;
		case Change_Direction:
		{
			m_MonsterImg->RotateFlip(RotateNoneFlipX);
			m_CurBehaviorState = Stay;
			m_BehaviorTime = (double)stay_time(gen);
			SetDirection(-GetDirection());
			m_ChangeBehavior = false;
		}
		break;
		case Forward:
		{
			m_CurBehaviorState = Forward;
			m_BehaviorTime = (double)forward_time(gen);
			m_ChangeBehavior = false;
			m_Speed = 100.f;
		}
		break;
	}
}

void cMonster_Runner::SensePlayer()
{
	if (cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[(INT)GROUP_TYPE::PLAYER].size() == 0)
		return;
	cObject* curPlayer = cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[(INT)GROUP_TYPE::PLAYER][0];
	float curPlayer_x = curPlayer->GetPos().x;
	float curPlayer_y = curPlayer->GetPos().y;

	float curMonster_x = GetPos().x;
	float curMonster_top = GetPos().y - GetScale().y / 2.f;
	float curMonster_down = GetPos().y + GetScale().y / 2.f;

	if (GetDirection() == 1
		&& curMonster_x <= curPlayer_x)
	{
		if (curPlayer_y <= curMonster_down
			&& curPlayer_y >= curMonster_top)
		{
			m_CurBehaviorState = Run;
			m_ChangeBehavior = false;
			m_Speed = 200.f;
		}
	}
	else if (GetDirection() == -1 && curMonster_x >= curPlayer_x)
	{
		if (curPlayer_y <= curMonster_down
			&& curPlayer_y >= curMonster_top)
		{
			m_CurBehaviorState = Run;
			m_ChangeBehavior = false;
			m_Speed = 200.f;
		}
	}
	else if (m_BehaviorTime < 0.f)
		m_ChangeBehavior = true;
}

bool cMonster_Runner::SenseBomb()
{
	if (cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[(INT)GROUP_TYPE::BOMB].size() == 0)
		return false;
	cObject* curBomb = cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[(INT)GROUP_TYPE::BOMB][0];
	float curBomb_x = curBomb->GetPos().x;
	float curBomb_y = curBomb->GetPos().y;

	float curMonster_x = GetPos().x;
	float curMonster_top = GetPos().y - GetScale().y / 2.f;
	float curMonster_down = GetPos().y + GetScale().y / 2.f;

	if (GetDirection() == 1
		&& curMonster_x <= curBomb_x)
	{
		if (curBomb_y <= curMonster_down
			&& curBomb_y >= curMonster_top)
		{
			m_CurBehaviorState = Retreat;
			m_ChangeBehavior = false;
			m_Speed = 100.f;
			return true;
		}
	}
	else if (GetDirection() == -1 
			 && curMonster_x >= curBomb_x)
	{
		if (curBomb_y <= curMonster_down
			&& curBomb_y >= curMonster_top)
		{
			m_CurBehaviorState = Retreat;
			m_ChangeBehavior = false;
			m_Speed = 100.f;
			return true;
		}
	}
	else if (m_BehaviorTime < 0.f)
		m_ChangeBehavior = true;

	return false;
}
