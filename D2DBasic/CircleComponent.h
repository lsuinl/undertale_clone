#pragma once
#include "Collider.h"
#include "Component.h"
#include "AABB.h"
#include <cmath>

class CircleCollider : public Collider, public Component
{
public:
	AABB m_Collider;
	D2D_RECT_F m_Rect;
	CircleCollider();
	~CircleCollider();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
	virtual bool IsCollide(Collider* pOtherComponent);
};
