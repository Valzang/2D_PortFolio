#include "Monster_SpitFire.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SpitFire.h"

cMonster_SpitFire::cMonster_SpitFire() : m_SpitFireTime(0.f)
{
	m_MonsterImg = Image::FromFile((WCHAR*)L"Image/Monster/Monster_SpitFire.png");
	m_curGroupType = (INT)GROUP_TYPE::MONSTER_RUNNER;
	SetScale(Vec2((float)m_MonsterImg->GetWidth() / 5.f, (float)m_MonsterImg->GetHeight()/ 4.f));
	SetHP(1);
	SetImgAttr();
	SetDirection(1);
}

cMonster_SpitFire::~cMonster_SpitFire()
{
	if (m_MonsterImg != NULL)
	{
		delete m_MonsterImg;
		m_MonsterImg = nullptr;
	}
}

bool cMonster_SpitFire::Update()
{
	if (GetHP() <= 0)
		return false;
	Vec2 CurPos = GetPos();

	if (!isOnPlatform() || GetThruRotate())
	{
		CurPos.y += 600.f * m_Dir.y * DELTA_TIME;
		if (m_Dir.y <= 2)
		{
			// ������ �׸��Բ� ������ ������ ���� ��� ���������ֱ�.
			if (!GetShoot())
				m_Dir.y += 8.f * DELTA_TIME;
			else
				m_Dir.y += 6.f * DELTA_TIME;
		}
		if (GetDirection() == 1) // ���� �����϶�
			CurPos.x += (float)(m_Speed * DELTA_TIME); // �ٶ󺸴� ���⿡ �°Բ�			
		else // ���� ������ ��
			CurPos.x -= (float)(m_Speed * DELTA_TIME); // �ٶ󺸴� ���⿡ �°Բ�								
	}
	else if (GetRotating() && !GetShoot())
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
				m_Speed = (m_Speed + 100.f + diff) * 3.f;
				m_Dir.y = -1.2f;
				SetOnPlatform(false);
				SetShoot(true);
			}
			//������ �Ʒ��� �������� �� ��
			else
			{
				SetOnPlatform(false);
				SetThruRotate(true);
				SetDir(Vec2(0.f, 2.f));
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
				m_Speed = (m_Speed+100.f + -diff) * 3.f;
				m_Dir.y = -1.2f;
				SetOnPlatform(false);
				SetShoot(true);
			}
			//������ �Ʒ��� �������� �� ��
			else
			{
				SetOnPlatform(false);
				SetThruRotate(true);
				SetDir(Vec2(0.f, 2.f));
			}
		}
		SetRotating(false);
	}
	else
	{
		switch (m_CurBehaviorState)
		{
			case Forward:
				CurPos.x += DELTA_TIME * m_Speed * GetDirection();
				break;
			case Retreat:
				CurPos.x -= DELTA_TIME * (m_Speed / 1.5f) * GetDirection();
				break;
			default:
				break;
		}
		m_BehaviorTime -= DELTA_TIME;

		SenseBomb();
		// SpitFireTime�� 0�� �Ǿ��� ������ �÷��̾ �����ؼ� Attack���� �ٲ���
		if (m_SpitFireTime == 0.f)
			SensePlayer();

		if (m_CurBehaviorState == Attack && m_SpitFireTime == 0.f)
		{
			m_SpitFireTime = 4.f;
		}

		if (m_BehaviorTime <= 0.f && m_CurBehaviorState != Attack)
			m_ChangeBehavior = true;

		if (m_ChangeBehavior)
			ChooseBehavior();
	}

	SetPos(CurPos);
	CollisionCheck(this, (INT)GROUP_TYPE::PLATFORM);
	SetPosOtherside();
	return true;
}

void cMonster_SpitFire::Render(HDC _hdc)
{
	static int curFrame = 0;
	Graphics graphics(_hdc);

	int w = m_MonsterImg->GetWidth() / 5;
	int h = m_MonsterImg->GetHeight() / 4;

	int xStart = (curFrame / 3) * w;
	int yStart = GetDirection()==1 ? 0 : h*2;
	if (m_CurBehaviorState == Attack)
	{
		yStart += h;
		xStart = (curFrame / 4) * w;
		curFrame = curFrame >= 19 ? 0 : curFrame + 1;
		if (curFrame == 0)
		{
			m_CurBehaviorState = Forward;// ���⼭ �Ҳ� ��ȯ
			CreateFire();
		}
	}
	else
	{
		if (m_SpitFireTime > 0.f)
			m_SpitFireTime -= DELTA_TIME;
		else
			m_SpitFireTime = 0;
		if (m_CurBehaviorState == Stay)
			curFrame = 0;
		else
			curFrame = curFrame >= 14 ? 0 : curFrame + 1;
	}
		
	

	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();
	//											�������� ���ݸ�ŭ ���ִ� ������ �⺻������ �׸���� ���ʻ�ܿ������� �׷��ֱ� ������ �׸��� ������ �ٲ��ֱ� ����.
	graphics.DrawImage(m_MonsterImg, Rect((int)Pos.x - (int)Scale.x / 2, (int)Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());
}


void cMonster_SpitFire::CreateFire()
{
	Vec2 Fire_Pos = GetPos();
	if (GetDirection() == 1)
		Fire_Pos.x += GetScale().x;
	else
		Fire_Pos.x -= GetScale().x;
	// ��ź ������Ʈ
	cSpitFire* Fire = new cSpitFire(Fire_Pos, GetDirection());

	cScene* curScene = cSceneManager::GetInstance()->GetCurScene();
	curScene->AddObject(Fire, GROUP_TYPE::SPITFIRE);
}
