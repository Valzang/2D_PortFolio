#include "Scene.h"

cScene::~cScene()
{
	DeleteSceneImg();
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arr_obj[i].size(); ++j)
		{
			// m_arr_obj[i] �׷� ������ j ��ü ����
			if (m_arr_obj[i][j] != NULL)
			{
				delete m_arr_obj[i][j];
				m_arr_obj[i][j] = nullptr;
			}			
		}
	}
	// ������ ������ ���Ұ� �������ٸ�
	// �Ҹ��� ��ü���� ���� ��ü�� ������
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

void cScene::Update()
{
	//m_BGM->Update();
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
}
