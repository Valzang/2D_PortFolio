#pragma once
#include "Monster.h"
#include <random>

//enum Behavior_Tree { Stay, Change_Direction, Forward, Retreat, Attack };
//static random_device rd;
//static mt19937 gen(rd());
//static uniform_int_distribution<int> state(0, 2);
//static uniform_int_distribution<int> forward_time(1, 3);
//static uniform_int_distribution<int> stay_time(0, 2);

class cMonster_Boss : public cMonster
{
private:
	bool m_isAttacking;
	int m_prevHP;
	int m_curFrame;
	bool m_NonDamage;

	double m_AttackTime;

	Vec2 DiffPos[4];
	int	m_PosCount;

public:
	cMonster_Boss();
	virtual ~cMonster_Boss();

	void SensePlayer();
	void CreateWave();

	void SetAttackTime() { m_AttackTime = 3.f; }

	virtual bool Update() override;
	virtual void Render(HDC _hdc) override;
	friend class cWave;
};

