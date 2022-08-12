#pragma once
#include "Object.h"

enum { Moving, Sitting, Dashing, Jumping, Attaching };

class cPlayer :
    public cObject
{
private:
    Image* m_PlayerImg;  // 이미지 파일    

    bool m_isMoved;     // 현재 움직이고 있는지
    bool m_isSitted;    // 현재 앉아있는 지
    bool m_isDashing;   // 현재 대쉬중인지
    bool m_isJumping;   // 현재 점프 중인지
    bool m_isAttached;  // 회전 후 천장에 붙어있는지

    int m_LifeCount;     // 현재 목숨
    int m_Rotation_Degree; // 돌아가는 각도

    double m_AtkCoolTime; // 폭탄 간 쿨타임
    double m_DashTime;    // 몇 초 간 대쉬를 하는지
    double m_DashCoolTime; // 대쉬 간 쿨타임    
    double m_AfterAttackTime; //폭탄 후 몇초간 뒤로 밀려날건지
    double m_AttachingTime;


public:
    cPlayer();
    virtual ~cPlayer();
    virtual bool Update() override;
    virtual void Render(HDC _hdc) override;
    void CreateBomb();


    bool GetDashing() { return m_isDashing; }

    void SetUnsitted() { m_isSitted = false; }
    void SetYspeedReverse() { m_Dir.y = 300.f; }
    bool Rotate_Platform();

    bool isAttaching() { return m_isAttached; }
    void SetAttach() { m_isAttached = true; }
};

