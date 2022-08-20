#include "Object.h"
#include "Scene.h"
#include "Player.h"
#include "Bomb.h"
#include "Monster_Runner.h"

cObject::cObject() : m_Pos(), m_Scale(), m_Direction(1), m_IsDead(false), m_OnPlatform(false), 
					m_Dir(Vec2(-2.f, 600.f)), m_isRotating(), RotFromDown(false),
					m_BombThruRotate(false), m_Rotator(nullptr), m_RotateToUp(false), m_FirstPos_Y(0.f), m_HP(1),
					dwID(0), mciOpen(), mciPlay(), m_isShoot(false)
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

void cObject::CollisionCheck(cObject* curObj, int GROUP_TYPE)
{
	Vec2 curObj_Pos = curObj->GetPos();
	Vec2 curObj_Scale = curObj->GetScale();

	// �� ������Ʈ�� ������
	float curObj_RightX = curObj_Pos.x + curObj_Scale.x / 2.f;
	float curObj_LeftX = curObj_Pos.x - curObj_Scale.x / 2.f;
	float curObj_UpY = curObj_Pos.y - curObj_Scale.y / 2.f;
	float curObj_DownY = curObj_Pos.y + curObj_Scale.y / 2.f;	

	// �ε��� ������Ʈ ��������
	vector<cObject*> otherObj = cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[GROUP_TYPE];
	int curObj_GroupType = curObj->GetCurGroupType();


	for (int i = 0; i < otherObj.size(); ++i)
	{
		// �ε��� ������Ʈ�� ������
		Vec2 otherObj_Pos = otherObj[i]->GetPos();
		Vec2 otherObj_Scale = otherObj[i]->GetScale();

		float otherObj_RightX = otherObj_Pos.x + otherObj_Scale.x / 2.f;
		float otherObj_LeftX = otherObj_Pos.x - otherObj_Scale.x / 2.f;
		float otherObj_UpY = otherObj_Pos.y - otherObj_Scale.y / 2.f;
		float otherObj_DownY = otherObj_Pos.y + otherObj_Scale.y / 2.f;

		// �浹���� �� (�簢�� ����)
		if ((abs(curObj_Pos.x - otherObj_Pos.x) < (curObj_Scale.x + otherObj_Scale.x) / 2.f)
			&& (abs(curObj_Pos.y - otherObj_Pos.y) < (curObj_Scale.y + otherObj_Scale.y) / 2.f))
		{	
			// �Ʒ��ʿ��� �浹���� ��
			if (curObj_UpY < otherObj_UpY && curObj_DownY > otherObj_UpY)
			{
				switch (GROUP_TYPE)
				{
					case (INT)GROUP_TYPE::PLATFORM_ROTATE:
					case (INT)GROUP_TYPE::PLATFORM:					
					{
						// ȸ������ 1���� ����ؾ��� ��
						if (curObj->GetThruRotate() && otherObj[i]->m_curGroupType == (INT)GROUP_TYPE::PLATFORM_ROTATE)
						{
							if (curObj->GetCurGroupType() == (INT)GROUP_TYPE::BOMB)
							{
								static bool Already_Pass = false;
								if (!Already_Pass)
								{
									curObj->SetOnPlatform(false);
									curObj->SetShoot(false);
									Already_Pass = true;
								}
								else
								{
									curObj->SetOnPlatform(true);
									curObj->SetShoot(false);
									curObj->SetThruRotate(false);
									Already_Pass = false;
								}
							}
							else
							{
								static cObject* curRotPlatform = otherObj[i];
								if (curRotPlatform == nullptr)
									curRotPlatform = otherObj[i];

								if (curRotPlatform == otherObj[i])
								{
									curObj->SetOnPlatform(false);
									curObj->SetShoot(false);
								}
								else
								{
									curObj->SetOnPlatform(true);
									curObj->SetShoot(false);
									curObj->SetThruRotate(false);
									curRotPlatform = nullptr;
								}
							}
						}
						// ����� �ʿ� ���� �� ( �Ϲ��� ���̽� )
						else
						{
							// �Ѿ ��ŭ ��ġ ����
							curObj_Pos.y -= (curObj_DownY - otherObj_UpY);
							if (curObj_GroupType == (INT)GROUP_TYPE::BOMB)
							{
								cBomb* curBomb = dynamic_cast<cBomb*>(curObj);
								int curBounceCnt = curBomb->GetBounceCount();
								// 3�� ƨ��� ���̸鼭 �߻�� ���¿��� ��
								if (curBomb->GetShoot() && curBounceCnt < 3)
								{
									curBomb->SetBounce();
									curBomb->IncreaseBounceCount();
									int temp = curBomb->GetBounceCount();
									if (curBomb->GetBounceCount() >= 3)
									{
										curBomb->SetShoot(false);
										curBomb->SetOnPlatform(true);
									}
								}
								else
								{
									curBomb->SetShoot(false);
									curBomb->SetOnPlatform(true);
								}
							}
							else
							{
								curObj->SetOnPlatform(true);
								curObj->SetShoot(false);	
								curObj->SetThruRotate(false);
							}
						}
					}					
						break;
					case (INT)GROUP_TYPE::PLAYER:
					{
						cPlayer* otherObj_Player = dynamic_cast<cPlayer*>(otherObj[i]);
						if(!otherObj_Player->GetRotating())
							otherObj_Player->Damage();
					}						
						break;
					case (INT)GROUP_TYPE::MONSTER:
					{
						if (curObj_GroupType == (INT)GROUP_TYPE::BOMB)
						{
							cBomb* curBomb = dynamic_cast<cBomb*>(curObj);
							if (curBomb->GetExplode())
								otherObj[i]->Damage();
						}						
					}
						break;
				}				
			}
			// ���ʿ��� �浹���� ��
			else if (curObj_UpY < otherObj_DownY && curObj_DownY > otherObj_DownY)
			{
				switch (GROUP_TYPE)
				{
					case (INT)GROUP_TYPE::PLATFORM_ROTATE:
					case (INT)GROUP_TYPE::PLATFORM:
					{
						// �Ѿ�� ��ŭ ��ġ ����
						curObj_Pos.y += (otherObj_DownY - curObj_UpY);
						if (curObj_GroupType == (INT)GROUP_TYPE::PLAYER)
						{
							cPlayer* curPlayer = dynamic_cast<cPlayer*>(curObj);
							curPlayer->SetRotFromDown(true);
							//if (curPlayer->Rotate_Platform() && curPlayer->GetRotating())
							if (curPlayer->Rotate_Platform())
								curPlayer->SetAttach();
							else
								curPlayer->SetYspeedReverse();
						}
					}
						break;
					case (INT)GROUP_TYPE::PLAYER:
					{
						cPlayer* otherObj_Player = dynamic_cast<cPlayer*>(otherObj[i]);
						if (!otherObj_Player->GetRotating())
							otherObj_Player->Damage();
					}
						break;
					case (INT)GROUP_TYPE::MONSTER:
					{
						if (curObj_GroupType == (INT)GROUP_TYPE::BOMB)
						{
							cBomb* curBomb = dynamic_cast<cBomb*>(curObj);
							if (curBomb->GetExplode())
								otherObj[i]->Damage();
						}
					}
						break;
				}				
			}
			// ������ ����� ��
			else if (curObj_LeftX <= otherObj_RightX && curObj_RightX > otherObj_RightX)
			{
				switch (GROUP_TYPE)
				{
					case (INT)GROUP_TYPE::PLATFORM_ROTATE:
					case (INT)GROUP_TYPE::PLATFORM:
					{						
						// �Ѿ�� ��ŭ ��ġ ����
						curObj_Pos.x += (otherObj_RightX - curObj_LeftX);
						switch (curObj_GroupType)
						{
							case (INT)GROUP_TYPE::BOMB:
								if (otherObj[i]->GetCurGroupType() == (INT)GROUP_TYPE::PLATFORM_BROKEN)
								{
									cBomb* curBomb = dynamic_cast<cBomb*>(curObj);
									if(curBomb->GetExplode())
										otherObj[i]->Dead();
									else
									{
										curBomb->SetExplode();
										otherObj[i]->Dead();
									}
									break;
								}
							case (INT)GROUP_TYPE::MONSTER_THORN:
								curObj->SetDirection(1);
								break;
							case (INT)GROUP_TYPE::MONSTER_RUNNER:
								curObj->SetShoot(false);
								break;
							case (INT)GROUP_TYPE::SPITFIRE:
								curObj->Dead();
								break;
						}
					}
						break;
					case (INT)GROUP_TYPE::PLAYER:
					{
						cPlayer* otherObj_Player = dynamic_cast<cPlayer*>(otherObj[i]);
						if (curObj_GroupType == (INT)GROUP_TYPE::BOMB
							|| curObj_GroupType == (INT)GROUP_TYPE::SPITFIRE)
						{
							if (!otherObj_Player->GetRotating())
								otherObj_Player->Damage();
							if(!otherObj_Player->GetRotating() && curObj_GroupType == (INT)GROUP_TYPE::SPITFIRE)
								curObj->Dead();
						}
						else if (curObj_GroupType == (INT)GROUP_TYPE::MONSTER_RUNNER)
						{
							cMonster_Runner* curMonster = dynamic_cast<cMonster_Runner*>(curObj);
							if (curMonster->GetCurBHState() != 4)
							{
								otherObj_Player->SetAttackTime(0.2f);
								curMonster->SetBHTime(1.f);
								curMonster->SetCurBHState(0);
								curMonster->SetPos(Vec2(curMonster->GetPos().x - (otherObj_RightX - curObj_LeftX) * 2, curMonster->GetPos().y));
							}
							else if (!otherObj_Player->GetRotating())
								otherObj_Player->Damage();
						}
						
					}
						break;
					case (INT)GROUP_TYPE::MONSTER:
					{
						if (curObj_GroupType == (INT)GROUP_TYPE::BOMB)
						{
							cBomb* curBomb = dynamic_cast<cBomb*>(curObj);
							if (curBomb->GetExplode())
								otherObj[i]->Damage();
							else if (curBomb->GetShoot())
								curBomb->SetExplode();
						}
					}
						break;
				}
				
			}

			// �������� ����� ��
			else if (curObj_RightX >= otherObj_LeftX && curObj_LeftX < otherObj_LeftX)
			{
				switch (GROUP_TYPE)
				{
					case (INT)GROUP_TYPE::PLATFORM_ROTATE:
					case (INT)GROUP_TYPE::PLATFORM:
					{						
						// �Ѿ�� ��ŭ ��ġ ����
						curObj_Pos.x -= (curObj_RightX - otherObj_LeftX);
						switch (curObj_GroupType)
						{
							case (INT)GROUP_TYPE::BOMB:
								if (otherObj[i]->GetCurGroupType() == (INT)GROUP_TYPE::PLATFORM_BROKEN)
								{
									cBomb* curBomb = dynamic_cast<cBomb*>(curObj);
									if (curBomb->GetExplode())
										otherObj[i]->Dead();
									else
									{
										curBomb->SetExplode();
										otherObj[i]->Dead();
									}
									break;
								}
							case (INT)GROUP_TYPE::MONSTER_THORN:
								curObj->SetDirection(-1);
								break;
							case (INT)GROUP_TYPE::MONSTER_RUNNER:
								curObj->SetShoot(false);
								break;
							case (INT)GROUP_TYPE::SPITFIRE:
								curObj->Dead();
								break;
						}						
					}
						break;
					case (INT)GROUP_TYPE::PLAYER:
					{
						cPlayer* otherObj_Player = dynamic_cast<cPlayer*>(otherObj[i]);
						if (curObj_GroupType == (INT)GROUP_TYPE::BOMB
							|| curObj_GroupType == (INT)GROUP_TYPE::SPITFIRE)
						{
							if (!otherObj_Player->GetRotating())
								otherObj_Player->Damage();
							if (!otherObj_Player->GetRotating() && curObj_GroupType == (INT)GROUP_TYPE::SPITFIRE)
								curObj->Dead();
						}
						else if (curObj_GroupType == (INT)GROUP_TYPE::MONSTER_RUNNER)
						{
							cMonster_Runner* curMonster = dynamic_cast<cMonster_Runner*>(curObj);
							if (curMonster->GetCurBHState() != 4)
							{
								otherObj_Player->SetAttackTime(0.2f);
								curMonster->SetBHTime(1.f);
								curMonster->SetCurBHState(0);
								curMonster->SetPos(Vec2(curMonster->GetPos().x - (otherObj_RightX - curObj_LeftX) * 2, curMonster->GetPos().y));
							}
							else if (!otherObj_Player->GetRotating())
								otherObj_Player->Damage();
						}
					}
						break;
					case (INT)GROUP_TYPE::MONSTER:
					{
						if (curObj_GroupType == (INT)GROUP_TYPE::BOMB)
						{
							cBomb* curBomb = dynamic_cast<cBomb*>(curObj);
							if (curBomb->GetExplode())
								otherObj[i]->Damage();
							else if (curBomb->GetShoot())
								curBomb->SetExplode();
						}
						else if (curObj_GroupType == (INT)GROUP_TYPE::PLAYER
								 && otherObj[i]->GetCurGroupType() == (INT)GROUP_TYPE::MONSTER_RUNNER)
						{
							cPlayer* curPlayer = dynamic_cast<cPlayer*>(curObj);
							cMonster_Runner* curMonster = dynamic_cast<cMonster_Runner*>(otherObj[i]);
							if (curMonster->GetCurBHState() != 4)
							{
								curPlayer->SetAttackTime(0.2f);
								curMonster->SetBHTime(1.f);
								curMonster->SetCurBHState(0);
								curMonster->SetPos(Vec2(curMonster->GetPos().x + (curObj_RightX - otherObj_LeftX)*2, curMonster->GetPos().y));
							}
						}
					}
						break;
				}
				
			}			
			
		}
	}

	curObj->SetPos(curObj_Pos);
}

void cObject::BGM_SetAndPlay(const LPCWSTR File_Path)
{
	mciOpen.lpstrDeviceType = L"WaveAudio";

	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL); // ���� ����
	mciOpen.lpstrElementName = File_Path; // ���� ��� �Է�

	mciSendCommandW(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&mciOpen);
	dwID = mciOpen.wDeviceID;

	// play & repeat
	mciSendCommandW(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&mciPlay);
}
