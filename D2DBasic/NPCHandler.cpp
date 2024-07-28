#include "NPCHandler.h"
#include "NPC.h"
void NPCHandler::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void NPCHandler::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	m_pOwner->talkable = true;

}

void NPCHandler::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	m_pOwner->talkable = false;
}
