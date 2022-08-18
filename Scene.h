#pragma once
#include "CustomDefine.h"
#include "Object.h"


// 헤더 파일을 부를 때와는 다르게
// 전방선언을 사용할 시 해당 class 내용이 바뀌어도 대응하지 않음.
// 즉, 컴파일 시간에 이득.
// 대신 포인터로 밖에 못 씀
class cObject;

class cScene
{
private:
	// 오브젝트들을 담을 벡터를 그룹 개수만큼 선언
	vector<cObject*> m_arr_obj[(UINT)GROUP_TYPE::END];
	Image* m_SceneImg;  // 이미지 파일
	Image* m_IntroAlramImg;				// 인트로 전용 알람 문구
	
	int m_MonsterCount;					// 몬스터 수

	int m_curSceneType;
	Gdiplus::ImageAttributes m_imgAttr; // 이미지 속성 담당 변수

	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
	int dwID;

public:
	cScene();
	virtual ~cScene();


	// 함수 정의를 헤더파일에 할 시에 inline 처리 되서 함수 호출 비용이 줆
	void AddObject(cObject* _Obj, GROUP_TYPE _Type)
	{		
		m_arr_obj[(UINT)_Type].push_back(_Obj);
	}

	void DeleteObject(cObject* _Obj, GROUP_TYPE _Type)
	{
		for (int j = (int)m_arr_obj[UINT(_Type)].size()-1 ; j >= 0; --j)
		{
			// m_arr_obj[i] 그룹 벡터의 j가 죽어있으면 해당 객체 삭제
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

	virtual void Enter() = 0; // 해당 씬으로 진입 시 호출
	virtual void Exit() = 0;  // 해당 씬에서 탈출 시 호출

	void BGM_SetAndPlay(const LPCWSTR File_Path);

	void Update();
	void Render(HDC _hdc);


};