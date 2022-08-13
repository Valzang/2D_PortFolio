#pragma once
#include "Monster.h"
class cMonster_Flying : public cMonster
{
private:

public:
	cMonster_Flying();
	virtual ~cMonster_Flying();


	virtual bool Update() override;
	virtual void Render(HDC _hdc) override;

};

