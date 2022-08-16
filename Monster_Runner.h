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

	void ChooseBehavior();
	void SensePlayer();
	bool SenseBomb();

};

