#pragma once

#include "CustomDefine.h"
#include "KeyManager.h"
#include "TimeManager.h"

extern short** g_PossibleArea;

class cObject
{
private:
	Vec2 m_Pos;
	Vec2 m_Scale;
	int m_Direction;
	bool m_IsDead;
	bool m_OnPlatform;

	bool m_isRotating;
	Vec2 m_RotatorPos;

	Gdiplus::ImageAttributes m_imgAttr; // 이미지 속성 담당 변수

protected:
	Vec2 m_Dir;
	bool m_Blocked[(UINT)KEY::RIGHT+1]; // 좌측/우측 벽이 막혔는지
	int m_curGroupType;					// 현재 무슨 타입인지
	bool RotFromDown;
	

public:
	cObject();
	virtual ~cObject() {};

	Vec2 GetPos() { return m_Pos; }
	virtual void SetPos(Vec2 _Pos);
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

	bool GetRotating() { return m_isRotating; }
	void SetRotating(bool _val) { m_isRotating = _val; }

	Vec2 GetRotator() { return m_RotatorPos; }
	void SetRotator(Vec2 _val) { m_RotatorPos = _val; }

	bool GetRotFromDown() { return RotFromDown; }
	void SetRotFromDown(bool _val) { RotFromDown = _val; }



	Gdiplus::ImageAttributes* GetImgAttr() { return &m_imgAttr; }
	void SetImgAttr() { m_imgAttr.SetColorKey(Color(255, 174, 201), Color(255, 174, 201)); } // A 컬러에서부터 B 컬러 사이 값들을 투명하게 만들어줌

	virtual bool Update() = 0;
	virtual void Render(HDC _hdc) = 0;
};

