#include "Scene.h"
#include "KeyManager.h"

cScene::cScene() : m_SceneImg(nullptr), m_IntroAlramImg(nullptr), m_MonsterCount(0), mciOpen(), mciPlay(), dwID(0), m_curSceneType(0)
{
	m_IntroAlramImg = Image::FromFile(L"Image/Intro_Alram.png");
	m_imgAttr.SetColorKey(Color(255, 174, 201), Color(255, 200, 201));
}

cScene::~cScene()
{
	DeleteSceneImg(); 
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL); // 음악 종료
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arr_obj[i].size(); ++j)
		{
			// m_arr_obj[i] 그룹 벡터의 j 물체 삭제
			if (m_arr_obj[i][j] != NULL)
			{
				delete m_arr_obj[i][j];
				m_arr_obj[i][j] = nullptr;
			}			
		}
	}
	// 위에서 벡터의 원소가 지워졌다면
	// 소멸자 자체에서 벡터 자체가 지워짐
}

void cScene::SetSceneImg(const wchar_t* FileName)
{
	m_SceneImg = Image::FromFile((WCHAR*)FileName);
}

void cScene::DeleteSceneImg()
{
	if (m_SceneImg != NULL)
	{
		delete m_SceneImg;
		m_SceneImg = nullptr;
	}
}

void cScene::BGM_SetAndPlay(const LPCWSTR File_Path)
{
	mciOpen.lpstrDeviceType = L"mpegvideo";
	mciOpen.lpstrElementName = File_Path; // 파일 경로 입력

	mciSendCommandW(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&mciOpen);
	dwID = mciOpen.wDeviceID;

	// play & repeat
	mciSendCommandW(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)&mciPlay);

}

void cScene::Update()
{
	//m_BGM->Update();
	if (GetCurSceneType() == (INT)SCENE_TYPE::START)
	{
		if (KEY_CHECK(KEY::A, KEY_STATE::DOWN))
		{			
			SetMonsterSize(0);

			MCI_OPEN_PARMS mciOpen2;
			MCI_PLAY_PARMS mciPlay2;
			int dwID2 = 0;

			mciOpen2.lpstrDeviceType = L"WaveAudio";
			mciOpen2.lpstrElementName = L"Sound/EFFECT/Cool.wav"; // 파일 경로 입력

			mciSendCommandW(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&mciOpen2);
			dwID2 = mciOpen2.wDeviceID;

			// play
			mciSendCommandW(dwID2, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&mciPlay2);
		}
	}
	else
	{
		for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
		{
			for (INT j = (INT)(m_arr_obj[i].size()) - 1; j >= 0; --j)
			{
				if (m_arr_obj[i][j]->Update() == false)
				{
					delete m_arr_obj[i][j];
					m_arr_obj[i][j] = nullptr;
					m_arr_obj[i].erase(m_arr_obj[i].begin() + j);
				}
			}
		}
	}	
}

void cScene::Render(HDC _hdc)
{
	Gdiplus::Graphics graphics(_hdc);
	int w = m_SceneImg->GetWidth();
	int h = m_SceneImg->GetHeight();
	
	graphics.DrawImage(m_SceneImg, Rect(0,0, w, h), 0, 0, w, h, UnitPixel, &m_imgAttr);

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arr_obj[i].size(); ++j)
		{
			m_arr_obj[i][j]->Render(_hdc);
		}
	}

	if (GetCurSceneType() == (INT)SCENE_TYPE::START)
	{
		Gdiplus::Graphics graphics_Alram(_hdc);
		w = (int)m_IntroAlramImg->GetWidth();
		h = (int)(m_IntroAlramImg->GetHeight() / 2.f);
		static int yStart = 0;
		static int curFrame = 0;
		Vec2 Alram_Pos(Vec2(640.f, 584.f));
		// Rect가 위치
		graphics_Alram.DrawImage(m_IntroAlramImg, Rect((int)Alram_Pos.x - w / 2, (int)Alram_Pos.y - h / 2, w, h), 0, yStart, w, h, UnitPixel, &m_imgAttr);

		yStart = curFrame++ < 10 ? 0 : h;
		if (curFrame == 18)
			curFrame = 0;
	}

	
}
