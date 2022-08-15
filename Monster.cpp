#include "Monster.h"

#include "TimeManager.h"


cMonster::cMonster() :
	m_Speed(100.f)
	, m_MonsterImg(nullptr)
{
	m_curGroupType = (INT)GROUP_TYPE::MONSTER;
}

cMonster::~cMonster()
{
	PlaySound(TEXT("Sound/EFFECT/Monster_Death.wav"), NULL, SND_ASYNC);//여기에 효과음 넣으면 될듯
	if(m_MonsterImg != NULL)
	{
		delete m_MonsterImg;
		m_MonsterImg = nullptr;
	}
}