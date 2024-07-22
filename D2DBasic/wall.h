#pragma once
#include "GameObject.h"
#include "BoxCollider.h"

class Wall :public GameObject
{
public:
	Wall();
	virtual ~Wall();

	BoxCollider* m_pCollisionBox = nullptr;

	virtual void Update(float time) override;
};
