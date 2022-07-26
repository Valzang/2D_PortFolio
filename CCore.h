#pragma once


class SceneManager
{
private:
	SceneManager() {}
	~SceneManager() {}

public:
	static SceneManager* GetInstance()
	{
		static SceneManager SceneInstance;

		return &SceneInstance;
	}
};

/*
class CCore2
{
private:
	CCore2() {}
	~CCore2() {};

public:
	static CCore2* GetInstance();

};



// 싱글톤 패턴 공부용
class CCore
{
private:
	// static 변수는 데이터 영역에 생성되며, 초기화는 한번만 진행이 됨.
	// 따라서 2번 이상 불러도 초기화는 진행되지 않음.
	static CCore* g_pInst;

private:
	// private에 생성자와 소멸자를 담음으로써, 객체 생성을 함부로 하지 못하게끔
	CCore() {}
	~CCore() {}

public:
	// 정적 선언을 통해 객체를 만들지 않고도 접근 가능하게끔.
	static CCore* GetInstance();

	static void Release();

};
*/