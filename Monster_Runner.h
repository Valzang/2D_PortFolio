#pragma once
#include "Monster.h"
#include <random>


class cMonster_Runner : public cMonster
{
private:
	// 비헤이비어 트리의 행동을 몇 초간 실행할 지
	double m_BehaviorTime;
	int m_CurBehaviorState;

	// 비헤이비어 트리의 행동을 바꿔야 하는 지
	bool m_ChangeBehavior;

public:
	cMonster_Runner();
	virtual ~cMonster_Runner();

	virtual bool Update() override;
	virtual void Render(HDC _hdc) override;

	void ChooseBehavior();
	void SensePlayer();
	bool SenseBomb();

};

