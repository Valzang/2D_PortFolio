#pragma once

#include "CustomDefine.h"
#include "KeyManager.h"
#include "TimeManager.h"


class cObject
{
private:
	Vec2 m_Pos;
	Vec2 m_Scale;
	int m_Direction;
	bool m_IsDead;
	bool m_OnPlatform;


	Gdiplus::ImageAttributes m_imgAttr; // 이미지 속성 담당 변수

protected:
	Vec2 m_Dir;

public:
	cObject() : m_Pos(), m_Scale(), m_Direction(1), m_IsDead(false), m_OnPlatform(false), m_Dir(Vec2(-2.f, 600.f)) { m_Dir.Normalize(); };
	virtual ~cObject() {};

	Vec2 GetPos() { return m_Pos; }
	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetPosOtherside(); // 맵 안에서만 맴돌게끔 해주는 함수

	bool isDead() { return m_IsDead; }
	void Dead() { m_IsDead = true; }

	bool isOnPlatform() { return m_OnPlatform; }
	void SetOnPlatform(bool _val) { m_OnPlatform = _val; }

	Vec2 GetScale() { return m_Scale; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	Vec2 GetDir() { return m_Dir; }
	void SetDir(Vec2 _Dir) { m_Dir = _Dir; m_Dir.Normalize(); }


	int GetDirection() { return m_Direction; }
	void SetDirection(int _dir) { m_Direction = _dir; }
	Gdiplus::ImageAttributes* GetImgAttr() { return &m_imgAttr; }
	void SetImgAttr() { m_imgAttr.SetColorKey(Color(255, 174, 201), Color(255, 174, 201)); } // A 컬러에서부터 B 컬러 사이 값들을 투명하게 만들어줌

	void Collsion(cObject& curObj,UINT GROUP_TYPE, float multiplier); // 플랫폼 위에 있으면 안떨어지게끔 하려고함, 추후 구현 필요

	virtual bool Update() = 0;
	virtual void Render(HDC _hdc) = 0;
};

