#pragma once
#include "Monster.h"
#include <random>


class cMonster_Runner : public cMonster
{
private:
	// �����̺�� Ʈ���� �ൿ�� �� �ʰ� ������ ��
	double m_BehaviorTime;
	int m_CurBehaviorState;

	// �����̺�� Ʈ���� �ൿ�� �ٲ�� �ϴ� ��
	bool m_ChangeBehavior;

public:
	cMonster_Runner();
	virtual ~cMonster_Runner();

	virtual bool Update() override;
	virtual void Render(HDC _hdc) override;

	int GetCurBHState() { return m_CurBehaviorState; }
	void SetCurBHState(int _val) { m_CurBehaviorState = _val; }
	void SetBHTime(double _val) { m_BehaviorTime = _val; }

	void ChooseBehavior();
	void SensePlayer();
	bool SenseBomb();

};

