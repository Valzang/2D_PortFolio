#include "CCore.h"

#define SINGLETONE2(type) public:\
							static type* GetInstance()\
							{\
								static type mgr;\
								return &mgr;\
							}

/*
CCore* CCore::g_pInst = nullptr;

CCore* CCore::GetInstance()
{
	// ���� ȣ�� ��
	if (g_pInst == nullptr)
	{
		g_pInst = new CCore;
	}

	return g_pInst;
}

void CCore::Release()
{
	if (nullptr != g_pInst)
	{
		delete g_pInst;
		g_pInst = nullptr;
	}
}



// ���� : ���� �������� �ʾƵ� �ȴ�. �ֳ�? �������� �Ҵ��� �������ϱ�
// ���� : ���α׷� �߰��� ���� �� ����. ������ ������ �������� �Ѵ�.
// => ���� ������ �Ŵ��� ������ �ϴ� Ŭ������ ��쿡 ������.
CCore2* CCore2::GetInstance()
{
	static CCore2 core;
	return &core;
}
*/