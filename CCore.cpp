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
	// 최초 호출 시
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



// 장점 : 굳이 지워주지 않아도 된다. 왜냐? 동적으로 할당을 안했으니까
// 단점 : 프로그램 중간에 지울 수 없다. 종료할 때까지 가져가야 한다.
// => 따라서 가벼운 매니저 역할을 하는 클래스의 경우에 유용함.
CCore2* CCore2::GetInstance()
{
	static CCore2 core;
	return &core;
}
*/