#pragma once
#include "CustomDefine.h"
#include "Object.h"

// ��� ������ �θ� ���ʹ� �ٸ���
// ���漱���� ����� �� �ش� class ������ �ٲ� �������� ����.
// ��, ������ �ð��� �̵�.
// ��� �����ͷ� �ۿ� �� ��
class cObject;

class cScene
{
private:
	// ������Ʈ���� ���� ���͸� �׷� ������ŭ ����
	vector<cObject*> m_arr_obj[(UINT)GROUP_TYPE::END];
	wstring m_sceneName;
	Image* m_SceneImg;  // �̹��� ����
	Gdiplus::ImageAttributes m_imgAttr; // �̹��� �Ӽ� ��� ����
	int m_MonsterCount;

public:
	cScene() : m_SceneImg(nullptr) {}
	virtual ~cScene();


	// �Լ� ���Ǹ� ������Ͽ� �� �ÿ� inline ó�� �Ǽ� �Լ� ȣ�� ����� ��
	void AddObject(cObject* _Obj, GROUP_TYPE _Type)
	{
		m_arr_obj[(UINT)_Type].push_back(_Obj);
	}

	void DeleteObject(cObject* _Obj, GROUP_TYPE _Type)
	{
		for (UINT j = 0; j < m_arr_obj[UINT(_Type)].size(); ++j)
		{
			// m_arr_obj[i] �׷� ������ j ��ü ����
			delete m_arr_obj[UINT(_Type)][j];
		}
		m_arr_obj[UINT(_Type)].clear();
	}

	int GetMonsterSize() { return m_MonsterCount; }
	void SetMonsterSize(int _s) { m_MonsterCount = _s; }

	void SetSceneImg(const wchar_t* FileName);
	void DeleteSceneImg();
	void SetName(const wstring& _strName);
	const wstring& GetName() { return m_sceneName; }

	virtual void Enter() = 0; // �ش� ������ ���� �� ȣ��
	virtual void Exit() = 0;  // �ش� ������ Ż�� �� ȣ��

	void Update();
	void Render(HDC _hdc);


};

