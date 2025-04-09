#pragma once
#include "Collider.h"

class Hero;
class HeroHandler : public IColliderNotify
{
	Hero* m_pOwner;
public:
	HeroHandler(Hero* Owner) { m_pOwner = Owner; };
	~HeroHandler();

	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};
