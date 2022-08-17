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

	Gdiplus::ImageAttributes m_imgAttr; // �̹��� �Ӽ� ��� ����	

    // �÷����� ���� �������� ƨ�ܳ�������
	bool m_RotateToUp;

	// ȸ�� �÷����� ���� �߻�Ǵ���
	bool m_isShoot;

protected:
	Vec2 m_Dir;
	int m_curGroupType;					// ���� ���� Ÿ������
	bool RotFromDown;

	bool m_BombThruRotate;

	// ���� ��� ����
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
	int dwID;
	

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

	// �÷����� ���� �߻�Ǵ���
	bool GetShoot() { return m_isShoot; }
	void SetShoot(bool _val) { m_isShoot = _val; }

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

	// �÷����� ���� �������� ƨ�ܳ�������
	bool GetRotateDir() { return m_RotateToUp; }
	void SetRotateDir(bool _val) { m_RotateToUp = _val; }

	// �浹üũ
	virtual void CollisionCheck(cObject* curObj, int GROUP_TYPE);
	virtual void CollisionPlatform(cObject* curObj, cObject* otherObj);

	// ���� �׷�Ÿ��
	int GetCurGroupType() { return m_curGroupType; }

	float GetFirstY() { return m_FirstPos_Y; }
	void SetFirstY(float _val) { m_FirstPos_Y = _val; }

	// HP ����
	int GetHP() { return m_HP; }
	void SetHP(int _val) { m_HP = _val; }
	virtual void Damage() { --m_HP; }

	//���� ����
	void BGM_SetAndPlay(const LPCWSTR File_Path);

	// �̹��� ����
	Gdiplus::ImageAttributes* GetImgAttr() { return &m_imgAttr; }
	void SetImgAttr() { m_imgAttr.SetColorKey(Color(255, 174, 201), Color(255, 174, 201)); } // A �÷��������� B �÷� ���� ������ �����ϰ� �������

	virtual bool Update() = 0;
	virtual void Render(HDC _hdc) = 0;
};

