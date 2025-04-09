#include "NPCHandler.h"
#include "BoxCollider.h"
#include "Hero.h"
#include "NPC.h"
void NPCHandler::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void NPCHandler::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	BoxCollider* other = dynamic_cast<BoxCollider*>(pOtherComponent);
	Hero* hero = dynamic_cast<Hero*>(other->GetOwner());
	if(hero)
		m_pOwner->talkable = true;

}

void NPCHandler::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	BoxCollider* other = dynamic_cast<BoxCollider*>(pOtherComponent);
	Hero* hero = dynamic_cast<Hero*>(other->GetOwner());
	if (hero)
		m_pOwner->talkable = false;
}
