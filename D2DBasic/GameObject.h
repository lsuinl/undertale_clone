#pragma once
#include "AABB.h"
#include "Component.h"
#include "AnimationScene.h"

class Component;
class Scene;
class World;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	std::vector<Component*> m_OwnedComponents;	// ������ ������Ʈ��
	Scene* m_pRootScene = nullptr;				// ������Ʈ �߿� ����� ��Ʈ���� ����
	World* m_pOwner = nullptr;					// �� ���� ������Ʈ�� ���� ����
	AABB m_BoundBox;								// �ٿ�� �ڽ�

	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
	void SetRootScene(Scene* pRootComponent) { m_pRootScene = pRootComponent; }
	const AABB& GetBoundBox() const { return m_BoundBox; }
	void AddComponent(Component* pComponent);
	void SetOwner(World* pOwner) { m_pOwner = pOwner; }

	D2D1_VECTOR_2F GetWorldLocation();

	// ������Ʈ �� ��Ʋ�� �Լ��� �����մϴ�.
	template<typename T>
	T* CreateComponent()
	{
		bool bIsBase = std::is_base_of<Component, T>::value;
		assert(bIsBase == true);
		T* pComponent = new T();
		AddComponent(pComponent);
		return pComponent;
	}
};

