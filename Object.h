#pragma once

#include "KeyManager.h"
#include "TimeManager.h"
//#include "CustomDefine.h"


class Object
{
protected:

private:
	Vec2 m_Pos;
	Vec2 m_Scale;

public:
	Object() : m_Pos(), m_Scale(){};
	virtual ~Object() {};

	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	Vec2 GetPos() { return m_Pos; }
	Vec2 GetScale() { return m_Scale; }

	void Update();
	void Render(HDC _hdc);
};

