#pragma once
#include "Object.h"

class cPlayer : public cObject
{
private:
    Image* m_PlayerImg;  // �̹��� ����    

    bool m_isMoved;     // ���� �����̰� �ִ���
    bool m_isSitted;    // ���� �ɾ��ִ� ��
    bool m_isDashing;   // ���� �뽬������
    bool m_isJumping;   // ���� ���� ������
    bool m_isAttached;  // ȸ�� �� õ�忡 �پ��ִ���
    bool m_Spawning;    // ��Ÿ���� ������
    bool m_isDamaging;  // ������ �ް� ���� ��

    int m_Rotation_Degree; // ���ư��� ����

    double m_AtkCoolTime; // ��ź �� ��Ÿ��
    double m_DashTime;    // �� �� �� �뽬�� �ϴ���
    double m_DashCoolTime; // �뽬 �� ��Ÿ��    
    double m_AfterAttackTime; //��ź �� ���ʰ� �ڷ� �з�������
    double m_AttachingTime; // �� �� �� õ�忡 �پ�������
    double m_InvincibleTime; // �� �ʰ� ��������

    Vec2 m_SpawnPlace; //�����Ǵ� ���

    bool m_Xreverse = false;


public:
    cPlayer();
    cPlayer(Vec2 _SpawnPlace);
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

    void SetAttackTime(double _val) { m_AfterAttackTime = _val; }

    virtual void Damage();

    void SetSpawnPlace(Vec2 _Val) { m_SpawnPlace = _Val; }
    void Respawn();
};

