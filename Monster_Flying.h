#pragma once
#include "Monster.h"
class cMonster_Flying : public cMonster
{
private:
	double m_FlyingTime;
	int		m_curFrame;

public:
	cMonster_Flying();
	cMonster_Flying(int _Direction);
	virtual ~cMonster_Flying();

	virtual bool Update() override;
	virtual void Render(HDC _hdc) override;

};

