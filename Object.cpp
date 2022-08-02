#include "Object.h"
#include "Scene.h"

void cObject::SetPosOtherside()
{
	Vec2 curPos = GetPos();
	float start_Xpos = GetScale().x / 2, start_Ypos = GetScale().y / 2;
	float end_Xpos = CCore::GetInstance()->GetResolution().x + GetScale().x / 2, end_Ypos = CCore::GetInstance()->GetResolution().y + GetScale().y / 2;

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

void cObject::CollsionWithPlatform(cObject& curObj, float multiplier)
{
	Vec2 og_pos = curObj.GetPos();
	Vec2 curObj_Left = curObj.GetPos();
	curObj_Left.x -= (curObj.GetScale().x / 2);

	float curObj_y = curObj_Left.y + (curObj.GetScale().y / 2);

	Vec2 curObj_Right = curObj.GetPos();
	curObj_Right.x += (curObj.GetScale().x / 2);

	cScene* curScene = cSceneManager::GetInstance()->GetCurScene();
	for (int i = 0; i < curScene->GetCurObjectVec()[(UINT)GROUP_TYPE::PLATFORM].size(); ++i)
	{
		Vec2 Platform_Pos = curScene->GetCurObjectVec()[(UINT)GROUP_TYPE::PLATFORM][i]->GetPos();
		Vec2 Platform_Scale = curScene->GetCurObjectVec()[(UINT)GROUP_TYPE::PLATFORM][i]->GetScale();

		float Left_End = Platform_Pos.x - Platform_Scale.x/2.f;
		float Right_End = Platform_Pos.x + Platform_Scale.x/2.f;
		float Top_End = Platform_Pos.y - Platform_Scale.y / 2.f;
		//float Bottom_End = Platform_Pos.y + Platform_Scale.y / 2.f;

		double cur_DT = double(multiplier * m_Dir.y * DELTA_TIME);

		if ((curObj_y >= Top_End - cur_DT) && (curObj_y <= Top_End + cur_DT) 	// 현재 플랫폼과 1 이하의 차이로 플랫폼 위에 있고
			&& curObj_Right.x > Left_End && curObj_Left.x < Right_End )	// 현재 플랫폼의 좌측 끝과 우측 끝 사이에 있을 때,
		{
			curObj.SetOnPlatform(true);
			return;
		}
	}
	curObj.SetOnPlatform(false);
	return;
}
