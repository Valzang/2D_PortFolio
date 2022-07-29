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
	Gdiplus::ImageAttributes m_imgAttr; // �̹��� �Ӽ� ��� ����

public:
	cObject() : m_Pos(), m_Scale(), m_Direction(){};
	virtual ~cObject() {};

	Vec2 GetPos() { return m_Pos; }
	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }

	Vec2 GetScale() { return m_Scale; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }


	int GetDirection() { return m_Direction; }
	void SetDirection(int _dir) { m_Direction = _dir; }
	Gdiplus::ImageAttributes* GetImgAttr() {return &m_imgAttr;}
	void SetImgAttr() { m_imgAttr.SetColorKey(Color(255, 174, 201), Color(255, 174, 201)); } // A �÷��������� B �÷� ���� ������ �����ϰ� �������

	virtual void Update() = 0;
	virtual void Render(HDC _hdc) = 0;
};

