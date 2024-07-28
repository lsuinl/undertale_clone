#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
#include "WallHandler.h"

class Wall :public GameObject
{
public:
	Wall();
	virtual ~Wall();
	WallHandler* notify = new WallHandler(this);
	BoxCollider* m_pCollisionBox = nullptr;

	virtual void Update(float time) override;
};
