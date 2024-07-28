#pragma once
#include "Collider.h"

class Character;
class CharacterHandler : public IColliderNotify
{
	Character* m_pOwner;
public:
	CharacterHandler(Character* Owner) { m_pOwner = Owner; };
	~CharacterHandler();
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};
