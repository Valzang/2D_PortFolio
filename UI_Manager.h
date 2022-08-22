#pragma once
#include "CustomDefine.h"

class cPlayer;

class cUI_Manager
{
	SINGLETON2(cUI_Manager);

private:
	cPlayer* m_curPlayer;
	int m_PlayerHP;
	UINT m_Score;

	Gdiplus::ImageAttributes m_imgAttr;

	Image* m_PlayerLifeImg;
	Vec2 m_PlayerLife_Pos;
	Vec2 m_PlayerLife_Scale;

	Image* m_PlayerLifeCountImg;
	Vec2 m_LifeCount_Pos;
	Vec2 m_LifeCount_Scale;
	

public:
	Vec2 Get_PlayerLife_Pos() { return m_PlayerLife_Pos; }
	void Set_PlayerLife_Pos(Vec2 _val) { m_PlayerLife_Pos = _val; }
	Vec2 Get_PlayerLife_Scale() { return m_PlayerLife_Scale; }
	void Set_PlayerLife_Scale(Vec2 _val) { m_PlayerLife_Scale = _val; }

	Vec2 Get_LifeCount_Pos() { return m_LifeCount_Pos; }
	void Set_LifeCount_Pos(Vec2 _val) { m_LifeCount_Pos = _val; }
	Vec2 Get_LifeCount_Scale() { return m_LifeCount_Scale; }
	void Set_LifeCount_Scale(Vec2 _val) { m_LifeCount_Scale = _val; }

	Gdiplus::ImageAttributes* GetImgAttr() { return &m_imgAttr; }
	void SetImgAttr() { m_imgAttr.SetColorKey(Color(255, 174, 201), Color(255, 174, 201)); } // A 컬러에서부터 B 컬러 사이 값들을 투명하게 만들어줌

	void Init();
	void Update();
	void Render(HDC _hdc);
};