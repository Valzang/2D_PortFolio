#pragma once
#include "Monster.h"
class cMonster_Thorn : public cMonster
{
private:
	double m_FlyingTime;
	int		m_curFrame;

public:
	cMonster_Thorn();
	virtual ~cMonster_Thorn();


	virtual bool Update() override;
	virtual void Render(HDC _hdc) override;

};



