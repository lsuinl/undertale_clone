#pragma once
#include "Collider.h"

class Wall;
class WallHandler : public IColliderNotify
{
	Wall* m_pOwner;
public:
	WallHandler(Wall* Owner) { m_pOwner = Owner; };

	~WallHandler();
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};
