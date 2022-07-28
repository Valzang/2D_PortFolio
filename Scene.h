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
	wstring m_sceneName;

public:
	// 함수 정의를 헤더파일에 할 시에 inline 처리 되서 함수 호출 비용이 줆
	void AddObject(cObject* _Obj, GROUP_TYPE _Type)
	{
		m_arr_obj[(UINT)_Type].push_back(_Obj);
	}

	cScene() {}
	virtual ~cScene();

	void SetName(const wstring& _strName) { m_sceneName = _strName; }
	const wstring& GetName() { return m_sceneName; }

	virtual void Enter() = 0; // 해당 씬으로 진입 시 호출
	virtual void Exit() = 0;  // 해당 씬에서 탈출 시 호출

	void Update();
	void Render(HDC _hdc);


};

