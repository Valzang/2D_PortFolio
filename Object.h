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

	Gdiplus::ImageAttributes m_imgAttr; // �̹��� �Ӽ� ��� ����

protected:
	Vec2 m_Dir;
	bool m_Blocked[(UINT)KEY::RIGHT+1]; // ����/���� ���� ��������
	int m_curGroupType;					// ���� ���� Ÿ������
	bool RotFromDown;

	bool m_BombThruRotate;
	

public:
	cObject();
	virtual ~cObject() {};

	// ��ġ ���� ����
	Vec2 GetPos() { return m_Pos; }
	virtual void SetPos(Vec2 _Pos);
	void SetPosOtherside(); // �� �ȿ����� �ɵ��Բ� ���ִ� �Լ�

	// �׾�����
	bool isDead() { return m_IsDead; }
	void Dead() { m_IsDead = true; }

	// ���� �÷��� ������
	bool isOnPlatform() { return m_OnPlatform; }
	void SetOnPlatform(bool _val) { m_OnPlatform = _val; }

	// ȸ�� �÷����� �ѹ� ����ϴ���
	bool GetThruRotate() { return m_BombThruRotate;	}
	void SetThruRotate(bool _val) { m_BombThruRotate = _val; }

	// ũ�� ����
	Vec2 GetScale() { return m_Scale; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }


	// �����̴� �ӵ� ����
	Vec2 GetDir() { return m_Dir; }
	void SetDir(Vec2 _Dir) { m_Dir = _Dir; m_Dir.Normalize(); }

	// �ٶ󺸰� �ִ� ���� ����
	int GetDirection() { return m_Direction; }
	void SetDirection(int _dir) { m_Direction = _dir; }

	// ���� ȸ�� ������
	bool GetRotating() { return m_isRotating; }
	void SetRotating(bool _val) { m_isRotating = _val; }

	// �ڽ��� ȸ����Ų ���簡 ��������
	cObject* GetRotator() { return m_Rotator; }
	void SetRotator(cObject* _val) { m_Rotator = _val; }

	// �Ʒ��������� ȸ���ϴ���
	bool GetRotFromDown() { return RotFromDown; }
	void SetRotFromDown(bool _val) { RotFromDown = _val; }

	// �浹üũ
	void CollisionCheck(cObject* curObj, int GROUP_TYPE);

	// ���� �׷�Ÿ��
	int GetCurGroupType() { return m_curGroupType; }

	float GetFirstY() { return m_FirstPos_Y; }
	void SetFirstY(float _val) { m_FirstPos_Y = _val; }

	Gdiplus::ImageAttributes* GetImgAttr() { return &m_imgAttr; }
	void SetImgAttr() { m_imgAttr.SetColorKey(Color(255, 174, 201), Color(255, 174, 201)); } // A �÷��������� B �÷� ���� ������ �����ϰ� �������

	virtual bool Update() = 0;
	virtual void Render(HDC _hdc) = 0;
};

