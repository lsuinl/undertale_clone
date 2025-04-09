#pragma once
#include "Collider.h"

class NPC;
class NPCHandler : public IColliderNotify
{
	NPC* m_pOwner;
public:
	NPCHandler(NPC* Owner) { m_pOwner = Owner; };
	~NPCHandler();

	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};
