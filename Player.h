#pragma once
#include "Object.h"

class cPlayer : public cObject
{
private:
    Image* m_PlayerImg;  // 이미지 파일    
    Image* m_PlayerLifeImg;    
    Image* m_PlayerLifeCountImg; 

    Vec2 m_PlayerLife_Pos;
    Vec2 m_PlayerLife_Scale;

    Vec2 m_LifeCount_Pos;
    Vec2 m_LifeCount_Scale;

    bool m_isMoved;     // 현재 움직이고 있는지
    bool m_isSitted;    // 현재 앉아있는 지
    bool m_isDashing;   // 현재 대쉬중인지
    bool m_isJumping;   // 현재 점프 중인지
    bool m_isAttached;  // 회전 후 천장에 붙어있는지
    bool m_Spawning;    // 나타나는 중인지
    bool m_GameOver;    // 게임 오버 확인용
    bool m_Clear;       // 클리어 이미지 띄우기용
    bool m_isDamaging;  // 데미지 받고 있을 때

    int m_OverCount;
    int m_Rotation_Degree; // 돌아가는 각도

    double m_AtkCoolTime; // 폭탄 간 쿨타임
    double m_DashTime;    // 몇 초 간 대쉬를 하는지
    double m_DashCoolTime; // 대쉬 간 쿨타임    
    double m_AfterAttackTime; //폭탄 후 몇초간 뒤로 밀려날건지
    double m_AttachingTime; // 몇 초 간 천장에 붙어있을지
    double m_InvincibleTime; // 몇 초간 무적일지

    Vec2 m_SpawnPlace; //스폰되는 장소

    bool m_Xreverse = false;


public:
    cPlayer();
    cPlayer(Vec2 _SpawnPlace, int _Life);
    virtual ~cPlayer();
    virtual bool Update() override;
    virtual void Render(HDC _hdc) override;
    void CreateBomb();

    bool GetDashing() { return m_isDashing; }

    void SetUnsitted() { m_isSitted = false; }
    void SetYspeedReverse() { m_Dir.y = 300.f; }
    bool Rotate_Platform();

    bool GetAttach() { return m_isAttached; }
    void SetAttach() { m_isAttached = true; }    

    void ResetAttackTime() { m_AtkCoolTime = 3.f; }
    void SetAttackTime(double _val) { m_AfterAttackTime = _val; }

    virtual void Damage();

    void UI_Render(HDC _hdc);

    void SetSpawnPlace(Vec2 _Val) { m_SpawnPlace = _Val; }
    void Respawn();
};

