#include "Object.h"
#include "Scene.h"

void cObject::SetPos(Vec2 _Pos)
{
	m_Pos = _Pos;
	if (m_curGroupType == (INT)GROUP_TYPE::PLATFORM)
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

void cObject::Collsion(cObject& curObj, UINT GROUP_TYPE, float multiplier)
{
	Vec2 curObj_Left = curObj.GetPos();
	curObj_Left.x -= (curObj.GetScale().x / 2);

	float curObj_y = curObj_Left.y + (curObj.GetScale().y / 2);

	Vec2 curObj_Right = curObj.GetPos();
	curObj_Right.x += (curObj.GetScale().x / 2);

	cScene* curScene = cSceneManager::GetInstance()->GetCurScene();

	if (GROUP_TYPE == (UINT)GROUP_TYPE::PLATFORM)
		curObj.SetOnPlatform(false);

	for (int i = 0; i < curScene->GetCurObjectVec()[GROUP_TYPE].size(); ++i)
	{
		Vec2 Platform_Pos = curScene->GetCurObjectVec()[GROUP_TYPE][i]->GetPos();
		Vec2 Platform_Scale = curScene->GetCurObjectVec()[GROUP_TYPE][i]->GetScale();

		float Left_End = Platform_Pos.x - Platform_Scale.x/2.f;
		float Right_End = Platform_Pos.x + Platform_Scale.x/2.f;
		float Top_End = Platform_Pos.y - Platform_Scale.y / 2.f;
		float Bottom_End = Platform_Pos.y + Platform_Scale.y / 2.f;

		double cur_DT = (double)multiplier * (double)(m_Dir.y) * DELTA_TIME;

		if (GROUP_TYPE == (UINT)GROUP_TYPE::PLATFORM)
		{
			if (!(curObj.isOnPlatform()) && curObj_y + cur_DT >= Top_End && curObj_Left.y <= Top_End 	// 현재 플랫폼과 1 이하의 차이로 플랫폼 위에 있고
				&& curObj_Right.x > Left_End && curObj_Left.x < Right_End)	// 현재 플랫폼의 좌측 끝과 우측 끝 사이에 있을 때,
			{
				curObj.SetOnPlatform(true);
			}
			if (curObj_Right.x + cur_DT >= Left_End && curObj.GetPos().x < Left_End
				&& curObj_Left.y >= Top_End && curObj_Left.y <= Bottom_End)
			{
				curObj.m_Blocked[(UINT)KEY::RIGHT] = true;
			}
			else if (curObj_Left.x - cur_DT <= Right_End && curObj.GetPos().x > Right_End
					 && curObj_Left.y >= Top_End && curObj_Left.y <= Bottom_End)
			{
				curObj.m_Blocked[(UINT)KEY::LEFT] = true;
			}
		}
			
	}
	
	return;
}
