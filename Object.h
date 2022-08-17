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

	int m_HP;
	bool m_IsDead;
	bool m_OnPlatform;

	bool m_isRotating;
	Vec2 m_RotatorPos;

	cObject* m_Rotator;

	float m_FirstPos_Y;

	Gdiplus::ImageAttributes m_imgAttr; // 이미지 속성 담당 변수	

    // 플랫폼에 의해 위쪽으로 튕겨나가는지
	bool m_RotateToUp;

	// 회전 플랫폼에 의해 발사되는지
	bool m_isShoot;

protected:
	Vec2 m_Dir;
	int m_curGroupType;					// 현재 무슨 타입인지
	bool RotFromDown;

	bool m_BombThruRotate;

	// 음악 재생 관련
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
	int dwID;
	

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

	// 플랫폼에 의해 발사되는지
	bool GetShoot() { return m_isShoot; }
	void SetShoot(bool _val) { m_isShoot = _val; }

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

	// 플랫폼에 의해 위쪽으로 튕겨나가는지
	bool GetRotateDir() { return m_RotateToUp; }
	void SetRotateDir(bool _val) { m_RotateToUp = _val; }

	// 충돌체크
	virtual void CollisionCheck(cObject* curObj, int GROUP_TYPE);
	virtual void CollisionPlatform(cObject* curObj, cObject* otherObj);

	// 현재 그룹타입
	int GetCurGroupType() { return m_curGroupType; }

	float GetFirstY() { return m_FirstPos_Y; }
	void SetFirstY(float _val) { m_FirstPos_Y = _val; }

	// HP 관련
	int GetHP() { return m_HP; }
	void SetHP(int _val) { m_HP = _val; }
	virtual void Damage() { --m_HP; }

	//사운드 관련
	void BGM_SetAndPlay(const LPCWSTR File_Path);

	// 이미지 관련
	Gdiplus::ImageAttributes* GetImgAttr() { return &m_imgAttr; }
	void SetImgAttr() { m_imgAttr.SetColorKey(Color(255, 174, 201), Color(255, 174, 201)); } // A 컬러에서부터 B 컬러 사이 값들을 투명하게 만들어줌

	virtual bool Update() = 0;
	virtual void Render(HDC _hdc) = 0;
};

