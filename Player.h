#pragma once
#include "Object.h"

enum { Moving, Sitting, Dashing, Jumping, Attaching };

class cPlayer :
    public cObject
{
private:
    Image* m_PlayerImg;  // �̹��� ����    

    bool m_isMoved;     // ���� �����̰� �ִ���
    bool m_isSitted;    // ���� �ɾ��ִ� ��
    bool m_isDashing;   // ���� �뽬������
    bool m_isJumping;   // ���� ���� ������
    bool m_isAttached;  // ȸ�� �� õ�忡 �پ��ִ���

    int m_LifeCount;     // ���� ���
    int m_Rotation_Degree; // ���ư��� ����

    double m_AtkCoolTime; // ��ź �� ��Ÿ��
    double m_DashTime;    // �� �� �� �뽬�� �ϴ���
    double m_DashCoolTime; // �뽬 �� ��Ÿ��    
    double m_AfterAttackTime; //��ź �� ���ʰ� �ڷ� �з�������
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

