#include "CharacterHandler.h"
#include "Character.h"
void CharacterHandler::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	m_pOwner->m_pMovement->SetBlock();
}

void CharacterHandler::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	m_pOwner->m_pCollisionBox->isColli = true;
	m_pOwner->Damage(10);
}

void CharacterHandler::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	m_pOwner->m_pCollisionBox->isColli = false;
}
