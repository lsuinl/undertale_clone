#pragma once
#include "D2DEngine.h"
/*
	게임 오브젝트의 기능을 컴포넌트 단위로 분리하기 위한 추상 클래스
	게임오브젝트는 컴포넌트의 조합으로 이루어진다.
	컴포넌트의 생성은 GameObject의 CreateComponent<T> 를 통해 이루어진다.
*/
class GameObject;
class Component
{
public:
	Component();
	virtual ~Component();

	GameObject* m_pOwner;

	void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }
	GameObject* GetOwner() { return m_pOwner; }

	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
};

