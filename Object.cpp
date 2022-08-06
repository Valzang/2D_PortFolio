#include "Object.h"
#include "Scene.h"

cObject::cObject() : m_Pos(), m_Scale(), m_Direction(1), m_IsDead(false), m_OnPlatform(false), 
					m_Dir(Vec2(-2.f, 600.f)), m_Blocked {}, m_isRotating(), RotFromDown(false)
{ 
	m_Dir.Normalize(); 
	m_curGroupType = (INT)GROUP_TYPE::DEFAULT; 
}

void cObject::SetPos(Vec2 _Pos)
{
	m_Pos = _Pos;
	if (m_curGroupType == (INT)GROUP_TYPE::PLATFORM || m_curGroupType == (INT)GROUP_TYPE::PLATFORM_ROTATE)
	{
		for (int i = (int)(_Pos.x - m_Scale.x / 2); i < (int)(_Pos.x + m_Scale.x / 2); ++i)
		{
			for (int j = (int)(_Pos.y - m_Scale.y / 2); j < (int)(_Pos.y + m_Scale.y / 2); ++j)
			{
				g_PossibleArea[i][j] = false;
			}
		}
	}
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
