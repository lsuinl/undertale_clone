#include "MonsterHandler.h"
#include "Monster.h"
#include "CharacterHandler.h"

void MonsterHandler::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	m_pOwner->m_pMovement->SetBlock();
}

void MonsterHandler::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	m_pOwner->m_pCollisionBox->isColli = true;
	CharacterHandler* character = dynamic_cast<CharacterHandler*>(pOtherComponent->notify);
	if (character) {
		m_pOwner->m_pRootScene->m_RelativeScale = { 0,0 };
		m_pOwner->m_pRootScene->m_size = { 0,0 };
	}
}

void MonsterHandler::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	m_pOwner->m_pCollisionBox->isColli = false;
}
