#include "Scene.h"
#include "pch.h"

Scene::Scene()
{
	m_RelativeTransform = m_WorldTransform = D2D1::Matrix3x2F::Identity();
}

Scene::~Scene()
{

}

void Scene::Update(float deltaTime)
{
	m_preLocation = m_RelativeLocation;
	UpdateTrasnform();

}
void Scene::UpdateTrasnform()
{
	//��,,��ü
	//#if _DEBUG	
		//pRenderTarget->SetTransform(m_WorldTransform);
		//pRenderTarget->DrawRectangle(D2D1::RectF(-2, -2, 2, 2), D2DRenderer::Instance->m_pBrushRed);
	//#endif // _DEBUG
	m_RelativeTransform =
		D2D1::Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y), m_center) *
		D2D1::Matrix3x2F::Rotation(m_RelativeRotation, m_center) *
		D2D1::Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);
  
	if (m_pParentScene != nullptr)
		m_WorldTransform = m_RelativeTransform * m_pParentScene->m_WorldTransform;
	else
		m_WorldTransform = m_RelativeTransform;
}
D2D1_VECTOR_2F Scene::GetWorldLocation() {
    D2D1_VECTOR_2F worldLocation = m_RelativeLocation; // �ʱ�ȭ�� ��� ��ġ���� �����մϴ�

    // �θ� Scene�� �����ϴ� ���, �θ��� ���� ��ġ�� �����ͼ� ���մϴ�
    if (m_pParentScene != nullptr)
    {
        D2D1_VECTOR_2F parentWorldLocation = m_pParentScene->GetWorldLocation();
        worldLocation.x += parentWorldLocation.x;
        worldLocation.y += parentWorldLocation.y;
    }

    return worldLocation;
}
//�߰�
void Scene::SetRelativeRotation(float Rotation)
{
	m_RelativeRotation = Rotation;
	m_RelativeRotation = fmodf(m_RelativeRotation, 360.0f);
}

void Scene::AddRelativeRotation(float Rotation)
{
	m_RelativeRotation += Rotation;
	m_RelativeRotation = fmodf(m_RelativeRotation, 360.0f);
}


void Scene::SetRelativeLocation(const D2D1_VECTOR_2F& Location)
{
	m_RelativeLocation = Location;
}

void Scene::AddRelativeLocation(float x, float y)
{
	m_RelativeLocation = { m_RelativeLocation.x + x,m_RelativeLocation.y + y };
}

