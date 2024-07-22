#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
	for (auto& pComponent : m_OwnedComponents)
	{
		delete pComponent;
	}
	m_OwnedComponents.clear();
}

void GameObject::Update(float deltaTime)
{
	for (auto& pComponent : m_OwnedComponents)
	{
		pComponent->Update(deltaTime);
	}

	if (m_pRootScene) {
		m_BoundBox.m_Center = { m_pRootScene->m_RelativeLocation.x+ m_pRootScene->m_size.x * m_pRootScene->m_RelativeScale.x/2
			, m_pRootScene->m_RelativeLocation.y + m_pRootScene->m_size.y * m_pRootScene->m_RelativeScale.y /2
		};
		m_BoundBox.m_Extent = { m_pRootScene->m_size.x * m_pRootScene->m_RelativeScale.x / 2,
		 m_pRootScene->m_size.y * m_pRootScene->m_RelativeScale.y / 2 };
	}
}

void GameObject::Render(D2DEngine* pRenderTarget)
{
	for (auto& pComponent : m_OwnedComponents)
	{
		pComponent->Render(pRenderTarget);
	}
}

void GameObject::AddComponent(Component* pComponent)
{
	pComponent->SetOwner(this);
	if (dynamic_cast<Scene*>(pComponent) != nullptr) {
		SetRootScene(dynamic_cast<Scene*>(pComponent));
	}
	m_OwnedComponents.push_back(pComponent);
}

D2D1_VECTOR_2F GameObject::GetWorldLocation()
{
	D2D1_VECTOR_2F temp{ 0,0 };
	if (m_pRootScene)
		temp = m_pRootScene->GetWorldLocation();

	return temp;
}
