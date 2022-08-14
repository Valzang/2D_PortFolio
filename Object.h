#pragma once

#include "CustomDefine.h"
#include "KeyManager.h"
#include "TimeManager.h"

//extern short** g_PossibleArea;

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

	cObject* m_Rotator;

	float m_FirstPos_Y;

	Gdiplus::ImageAttributes m_imgAttr; // 이미지 속성 담당 변수

protected:
	Vec2 m_Dir;
	bool m_Blocked[(UINT)KEY::RIGHT+1]; // 좌측/우측 벽이 막혔는지
	int m_curGroupType;					// 현재 무슨 타입인지
	bool RotFromDown;

	bool m_BombThruRotate;
	

public:
	cObject();
	virtual ~cObject() {};

	// 위치 조정 관련
	Vec2 GetPos() { return m_Pos; }
	virtual void SetPos(Vec2 _Pos);
	void SetPosOtherside(); // 맵 안에서만 맴돌게끔 해주는 함수

	// 죽었는지
	bool isDead() { return m_IsDead; }
	void Dead() { m_IsDead = true; }

	// 현재 플랫폼 위인지
	bool isOnPlatform() { return m_OnPlatform; }
	void SetOnPlatform(bool _val) { m_OnPlatform = _val; }

	// 회전 플랫폼을 한번 통과하는지
	bool GetThruRotate() { return m_BombThruRotate;	}
	void SetThruRotate(bool _val) { m_BombThruRotate = _val; }

	// 크기 관련
	Vec2 GetScale() { return m_Scale; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }


	// 움직이는 속도 관련
	Vec2 GetDir() { return m_Dir; }
	void SetDir(Vec2 _Dir) { m_Dir = _Dir; m_Dir.Normalize(); }

	// 바라보고 있는 방향 관련
	int GetDirection() { return m_Direction; }
	void SetDirection(int _dir) { m_Direction = _dir; }

	// 현재 회전 중인지
	bool GetRotating() { return m_isRotating; }
	void SetRotating(bool _val) { m_isRotating = _val; }

	// 자신을 회전시킨 존재가 누구인지
	cObject* GetRotator() { return m_Rotator; }
	void SetRotator(cObject* _val) { m_Rotator = _val; }

	// 아래에서부터 회전하는지
	bool GetRotFromDown() { return RotFromDown; }
	void SetRotFromDown(bool _val) { RotFromDown = _val; }

	// 충돌체크
	void CollisionCheck(cObject* curObj, int GROUP_TYPE);

	// 현재 그룹타입
	int GetCurGroupType() { return m_curGroupType; }

	float GetFirstY() { return m_FirstPos_Y; }
	void SetFirstY(float _val) { m_FirstPos_Y = _val; }

	Gdiplus::ImageAttributes* GetImgAttr() { return &m_imgAttr; }
	void SetImgAttr() { m_imgAttr.SetColorKey(Color(255, 174, 201), Color(255, 174, 201)); } // A 컬러에서부터 B 컬러 사이 값들을 투명하게 만들어줌

	virtual bool Update() = 0;
	virtual void Render(HDC _hdc) = 0;
};

