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
	bool m_isDamaging;
	bool m_isAttacking;
	int m_prevHP;

public:
	cMonster_Boss();
	virtual ~cMonster_Boss();

	void SensePlayer();
	void CreateWave();

	virtual bool Update() override;
	virtual void Render(HDC _hdc) override;
	friend class cWave;
};

