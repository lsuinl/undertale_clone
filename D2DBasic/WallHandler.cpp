#include "WallHandler.h"
#include "wall.h"
void WallHandler::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void WallHandler::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	m_pOwner->m_pCollisionBox->isColli = true;
}

void WallHandler::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	m_pOwner->m_pCollisionBox->isColli = false;
}
