#pragma once
#include "Monster_Runner.h"

class cMonster_SpitFire : public cMonster_Runner
{
private:
	double m_SpitFireTime;

public :
	cMonster_SpitFire();
	virtual ~cMonster_SpitFire();

	virtual bool Update() override;
	virtual void Render(HDC _hdc) override;

	void CreateFire();

	virtual int GetCurBHState() { return m_CurBehaviorState; }
	virtual void SetCurBHState(int _val) { m_CurBehaviorState = _val; }
	virtual void SetBHTime(double _val) { m_BehaviorTime = _val; }
};

