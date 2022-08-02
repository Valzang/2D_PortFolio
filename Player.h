#pragma once
#include "Object.h"

class cPlayer :
    public cObject
{
private:
    Image* m_PlayerImg;  // 이미지 파일    

    bool m_isMoved;     // 현재 움직이고 있는지
    bool m_isSitted;    // 현재 앉아있는 지
    bool m_isDashing;   // 현재 대쉬중인지
    bool m_isJumping;   // 현재 점프 중인지

    int m_LifeCount;     // 현재 목숨
    double m_Falling;

    double m_AtkCoolTime; // 폭탄 간 쿨타임
    double m_DashTime;    // 몇 초 간 대쉬를 하는지
    double m_DashCoolTime; // 대쉬 간 쿨타임    
    double m_JumpingTime; // 몇 초 간 점프를 하는지    

public:
    cPlayer();
    virtual ~cPlayer();
    virtual bool Update() override;
    virtual void Render(HDC _hdc) override;
    void CreateBomb();
};

