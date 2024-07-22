#include "pch.h"
#include "CameraScene.h"

CameraScene::CameraScene()
{
	float width = 1024;
	float height = 768;
	m_ViewBoundBox.SetCenter(width / 2, height / 2);
	m_ViewBoundBox.SetExtent(width / 2, height / 2);
}
CameraScene::CameraScene(float _width, float _height)
{
	float width = _width;
	float height = _height;
	m_ViewBoundBox.SetCenter(width / 2, height / 2);
	m_ViewBoundBox.SetExtent(width / 2, height / 2);
}

CameraScene::~CameraScene()
{

}



void CameraScene::Update(float deltaTime)
{
	Scene::UpdateTrasnform();
	m_ViewBoundBox.m_Center = { m_ViewBoundBox.m_Extent.x + GetWorldLocation().x,
		m_ViewBoundBox.m_Extent.y + GetWorldLocation().y
	};
	this->deltaTime += deltaTime;

	deltaTime = 0;
	m_WorldTransform = D2D1::Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);
	D2D1InvertMatrix(&m_WorldTransform);
}
