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



// �̱��� ���� ���ο�
class CCore
{
private:
	// static ������ ������ ������ �����Ǹ�, �ʱ�ȭ�� �ѹ��� ������ ��.
	// ���� 2�� �̻� �ҷ��� �ʱ�ȭ�� ������� ����.
	static CCore* g_pInst;

private:
	// private�� �����ڿ� �Ҹ��ڸ� �������ν�, ��ü ������ �Ժη� ���� ���ϰԲ�
	CCore() {}
	~CCore() {}

public:
	// ���� ������ ���� ��ü�� ������ �ʰ� ���� �����ϰԲ�.
	static CCore* GetInstance();

	static void Release();

};
*/