#include "HeroHandler.h"
#include "Hero.h"
void HeroHandler::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	m_pOwner->m_pMovement->SetBlock();
}

void HeroHandler::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void HeroHandler::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}
