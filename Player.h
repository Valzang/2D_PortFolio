#pragma once
#include "Object.h"

class cPlayer :
    public cObject
{
private:
    Image* m_PlayerImg;  // �̹��� ����    

    bool m_isMoved;     // ���� �����̰� �ִ���
    bool m_isSitted;    // ���� �ɾ��ִ� ��
    bool m_isDashing;   // ���� �뽬������
    bool m_isJumping;   // ���� ���� ������

    int m_LifeCount;     // ���� ���
    double m_Falling;

    double m_AtkCoolTime; // ��ź �� ��Ÿ��
    double m_DashTime;    // �� �� �� �뽬�� �ϴ���
    double m_DashCoolTime; // �뽬 �� ��Ÿ��    
    double m_JumpingTime; // �� �� �� ������ �ϴ���    

public:
    cPlayer();
    virtual ~cPlayer();
    virtual bool Update() override;
    virtual void Render(HDC _hdc) override;
    void CreateBomb();
};

