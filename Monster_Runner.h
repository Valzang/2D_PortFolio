#pragma once
#include "Monster.h"
#include <random>

enum Behavior_Tree { Stay, Change_Direction, Forward, Retreat, Attack };
static random_device rd;
static mt19937 gen(rd());
static uniform_int_distribution<int> state(0, 2);
static uniform_int_distribution<int> forward_time(1, 3);
static uniform_int_distribution<int> stay_time(0, 2);

class cMonster_Runner : public cMonster
{
protected:
	// �����̺�� Ʈ���� �ൿ�� �� �ʰ� ������ ��
	double m_BehaviorTime;
	int m_CurBehaviorState;

	// �����̺�� Ʈ���� �ൿ�� �ٲ�� �ϴ� ��
	bool m_ChangeBehavior;
	int m_curFrame;

public:
	cMonster_Runner();
	virtual ~cMonster_Runner();

	virtual bool Update() override;
	virtual void Render(HDC _hdc) override;

	virtual int GetCurBHState() { return m_CurBehaviorState; }
	virtual void SetCurBHState(int _val) { m_CurBehaviorState = _val; }
	virtual void SetBHTime(double _val) { m_BehaviorTime = _val; }

	void ChooseBehavior();
	void SensePlayer();
	bool SenseBomb();

};

