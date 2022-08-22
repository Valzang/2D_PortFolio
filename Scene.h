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
	Image* m_SceneImg;  // �̹��� ����
	Image* m_IntroAlramImg;				// ��Ʈ�� ���� �˶� ����
	
	int m_MonsterCount;					// ���� ��

	int m_curSceneType;
	Gdiplus::ImageAttributes m_imgAttr; // �̹��� �Ӽ� ��� ����

	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
	int dwID;

public:
	cScene();
	virtual ~cScene();


	// �Լ� ���Ǹ� ������Ͽ� �� �ÿ� inline ó�� �Ǽ� �Լ� ȣ�� ����� ��
	void AddObject(cObject* _Obj, GROUP_TYPE _Type)
	{		
		m_arr_obj[(UINT)_Type].push_back(_Obj);
	}

	void DeleteObject(cObject* _Obj, GROUP_TYPE _Type)
	{
		for (int j = (int)m_arr_obj[UINT(_Type)].size()-1 ; j >= 0; --j)
		{
			// m_arr_obj[i] �׷� ������ j�� �׾������� �ش� ��ü ����
			if (m_arr_obj[UINT(_Type)][j]->isDead())
			{
				delete m_arr_obj[UINT(_Type)][j];
				m_arr_obj[UINT(_Type)].erase(m_arr_obj[UINT(_Type)].begin() + j);
			}
		}
	}

	int GetMonsterSize() { return m_MonsterCount; }
	void SetMonsterSize(int _s) { m_MonsterCount = _s; }

	int GetCurSceneType() { return m_curSceneType; }
	void SetCurSceneType(int _val) { m_curSceneType = _val; }

	vector<cObject*>* GetCurObjectVec() { return m_arr_obj; }

	virtual void SetSceneImg(const wchar_t* FileName);
	virtual void DeleteSceneImg();

	virtual void Enter() = 0; // �ش� ������ ���� �� ȣ��
	virtual void Exit() = 0;  // �ش� ������ Ż�� �� ȣ��

	void BGM_SetAndPlay(const LPCWSTR File_Path);

	void Update();
	void Render(HDC _hdc);


};