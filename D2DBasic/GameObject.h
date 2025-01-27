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

	std::vector<Component*> m_OwnedComponents;	// 소유한 컴포넌트들
	Scene* m_pRootScene = nullptr;				// 컴포넌트 중에 어느게 루트인지 설정
	World* m_pOwner = nullptr;					// 이 게임 오브젝트가 속한 월드
	AABB m_BoundBox;								// 바운딩 박스

	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
	void SetRootScene(Scene* pRootComponent) { m_pRootScene = pRootComponent; }
	const AABB& GetBoundBox() const { return m_BoundBox; }
	void AddComponent(Component* pComponent);
	void SetOwner(World* pOwner) { m_pOwner = pOwner; }

	D2D1_VECTOR_2F GetWorldLocation();

	// 컴포넌트 를 템틀릿 함수로 생성합니다.
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

