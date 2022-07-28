#pragma once
#include "CustomDefine.h"

// 1. 프레임 동기화
// 키 매니저의 의의 : 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가져간다.

// 2. 키 입력 이벤트 처리
// 한번 눌렸는지, 꾹 눌렸는지, 눌렸다가 떼어졌는지, 안 눌렸는지

// 3. 현재 윈도우 창이 활성화 되어있을 때에만 키 입력 처리



enum class KEY_STATE
{
	NONE, // 누르지 않은 상태 ( 이전에 안 눌렸음 )
	DOWN, // 처음 누른 상태
	HOLD, // 누르고 있는 상태
	UP, // 누르지 않은 상태 ( 이전에 눌렸음 )
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	// 1P 움직임
	A, S, I, J, K, L,


	// 2P 움직임	
	Delete, End, Num8, Num4, Num5, Num6,

	Player2_START, // 2P 켜기
	P, // Pause
	ESC, // Escape
	Enter, // Enter
	LAST // enum의 끝
};

static int arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	// 1P 움직임
	'A', 'S', 'I', 'J', 'K', 'L',

	// 2P 움직임
	VK_DELETE, VK_END, VK_NUMPAD8, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6,

	'2', // 2P 시작
	'P', // Pause
	VK_ESCAPE, // Escape
	VK_RETURN, // Enter
};

struct KeyInfo
{
	KEY_STATE mKeyState; // 키의 상태값
	bool wasPushed; // 이전 프레임에 눌렸는지
};


class cKeyManager
{
	SINGLETON2(cKeyManager)

private:
	vector<KeyInfo> m_vecKey;
	//HWND m_hWnd = NULL;

public:
	void Init();
	void Update();
	KEY_STATE GetKeyState(KEY _key);
};

