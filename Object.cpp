#include "Object.h"
#include "Scene.h"
#include "Player.h"
#include "Bomb.h"

cObject::cObject() : m_Pos(), m_Scale(), m_Direction(1), m_IsDead(false), m_OnPlatform(false), 
					m_Dir(Vec2(-2.f, 600.f)), m_Blocked {}, m_isRotating(), RotFromDown(false), m_curOnPlatform(nullptr)
					,m_BombThruRotate(false), m_Rotator(nullptr)
{ 
	m_Dir.Normalize(); 
	m_curGroupType = (INT)GROUP_TYPE::DEFAULT; 
}

void cObject::SetPos(Vec2 _Pos)
{
	m_Pos = _Pos;
}

void cObject::SetPosOtherside()
{
	Vec2 curPos = GetPos();
	float start_Xpos = GetScale().x / 2, start_Ypos = GetScale().y / 2;
	float end_Xpos = cCore::GetInstance()->GetResolution().x + GetScale().x / 2, end_Ypos = cCore::GetInstance()->GetResolution().y + GetScale().y / 2;

	if (curPos.x <= -start_Xpos)
		curPos.x = end_Xpos - 1;
	else if (curPos.x >= end_Xpos)
		curPos.x = -start_Xpos + 1;

	if (curPos.y <= -GetScale().y / 2)
		curPos.y = end_Ypos - 1;
	else if (curPos.y >= end_Ypos)
		curPos.y = -start_Ypos + 1;

	SetPos(curPos);
}

void cObject::CollisionCheck(cObject* curObj)
{
	Vec2 curObj_Pos = curObj->GetPos();
	Vec2 curObj_Scale = curObj->GetScale();

	float curObj_RightX = curObj_Pos.x + curObj_Scale.x / 2.f;
	float curObj_LeftX = curObj_Pos.x - curObj_Scale.x / 2.f;
	float curObj_UpY = curObj_Pos.y - curObj_Scale.y / 2.f;
	float curObj_DownY = curObj_Pos.y + curObj_Scale.y / 2.f;

	vector<cObject*> curPlatform = cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[(INT)GROUP_TYPE::PLATFORM];

	for (int i = 0; i < curPlatform.size(); ++i)
	{
		Vec2 curPlatform_Pos = curPlatform[i]->GetPos();
		Vec2 curPlatform_Scale = curPlatform[i]->GetScale();

		float curPlatform_RightX = curPlatform_Pos.x + curPlatform_Scale.x / 2.f;
		float curPlatform_LeftX = curPlatform_Pos.x - curPlatform_Scale.x / 2.f;
		float curPlatform_UpY = curPlatform_Pos.y - curPlatform_Scale.y / 2.f;
		float curPlatform_DownY = curPlatform_Pos.y + curPlatform_Scale.y / 2.f;

		// 충돌했을 때 (사각형 기준)
		if ((abs(curObj_Pos.x - curPlatform_Pos.x) < (curObj_Scale.x + curPlatform_Scale.x) / 2.f)
			&& (abs(curObj_Pos.y - curPlatform_Pos.y) < (curObj_Scale.y + curPlatform_Scale.y) / 2.f))
		{			
			// 아랫쪽에서 충돌했을 때
			if (curObj_UpY < curPlatform_UpY && curObj_DownY >= curPlatform_UpY)
			{				
				curObj->SetOnPlatform(curPlatform[i]);			
				// 회전문을 1번만 통과해야할 때
				if (curObj->GetThruRotate() && curPlatform[i]->m_curGroupType == (INT)GROUP_TYPE::PLATFORM_ROTATE)
				{					
					static bool Already_Pass = false;					
					if(!Already_Pass)
						curObj->SetOnPlatform(false);
					else
						curObj->SetOnPlatform(true);
					Already_Pass = true;
				}
				// 통과할 필요 없을 때 ( 일반적 케이스 )
				else
				{
					// 넘어간 만큼 위치 보정
					curObj_Pos.y -= (curObj_DownY - curPlatform_UpY);
					if (curObj->m_curGroupType == (INT)GROUP_TYPE::BOMB)
					{
						cBomb* curBomb = dynamic_cast<cBomb*>(curObj);
						int curBounceCnt = curBomb->GetBounceCount();
						//cout << "카운트 : " << curBomb->GetBounceCount() << " 폭탄 방향 : " << curBomb->GetDirection() << '\n';

						if (curBomb->GetIsShoot() && curBounceCnt < 3)
						{
							curBomb->SetBounce();
							curBomb->IncreaseBounceCount();
							if (curBomb->GetBounceCount() >= 3)
							{
								curBomb->SetIsShoot(false);
								curBomb->SetOnPlatform(true);
							}
						}
						else
						{
							curBomb->SetIsShoot(false);
							curBomb->SetOnPlatform(true);
						}
							
					}
					else
						curObj->SetOnPlatform(true);
				}
					
			}
			// 위쪽에서 충돌했을 때
			else if (curObj_UpY <= curPlatform_DownY && curObj_DownY > curPlatform_DownY)
			{
				// 넘어온 만큼 위치 보정
				curObj_Pos.y += (curPlatform_DownY - curObj_UpY);
				if (curObj->m_curGroupType == (INT)GROUP_TYPE::PLAYER)
				{
					cPlayer* curPlayer = dynamic_cast<cPlayer*>(curObj);
					curPlayer->SetRotFromDown(true);
					if (curPlayer->Rotate_Platform())
						curPlayer->SetAttach();
					else
						curPlayer->SetYspeedReverse();
				}
			}
			// 왼쪽이 닿았을 때
			else if (curObj_LeftX <= curPlatform_RightX && curObj_RightX > curPlatform_RightX)
			{
				// 넘어온 만큼 위치 보정
				curObj_Pos.x += (curPlatform_RightX - curObj_LeftX);
				if (curObj->m_curGroupType == (INT)GROUP_TYPE::BOMB)
					curObj->SetDirection(1);
			}

			// 오른쪽이 닿았을 때
			else if (curObj_RightX >= curPlatform_LeftX && curObj_LeftX < curPlatform_LeftX)
			{
				// 넘어온 만큼 위치 보정
				curObj_Pos.x -= (curObj_RightX - curPlatform_LeftX);
				if (curObj->m_curGroupType == (INT)GROUP_TYPE::BOMB)
					curObj->SetDirection(-1);
			}			
		}
	}
	curObj->SetPos(curObj_Pos);
}
