#pragma once
#include "Object.h"

class cPlayer :
    public cObject
{
private:
    Image* m_PlayerImg;  // 이미지 파일    
    bool m_isMoved;
    bool m_isSitted;
    bool m_isDashing;

    int m_LifeCount;

    double m_AtkCoolTime;
    double m_DashCoolTime;

public:
    cPlayer();
    virtual ~cPlayer();
    virtual bool Update() override;
    virtual void Render(HDC _hdc) override;
    void CreateBomb();
};

