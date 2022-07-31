#include "Scene.h"

cScene::~cScene()
{
	DeleteSceneImg();
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arr_obj[i].size(); ++j)
		{
			// m_arr_obj[i] 그룹 벡터의 j 물체 삭제
			delete m_arr_obj[i][j];
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
		delete m_SceneImg;
}

void cScene::SetName(const wstring& _strName)
{
	m_sceneName = _strName;
}

void cScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (INT j = (INT)(m_arr_obj[i].size())-1; j >= 0; --j)
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

void cScene::Render(HDC _hdc)
{
	Graphics graphics(_hdc);
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
}
