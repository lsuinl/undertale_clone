#pragma once
#include "Collider.h"

class Monster;
class MonsterHandler : public IColliderNotify
{
    Monster* m_pOwner;
public:
    MonsterHandler(Monster* Owner) : m_pOwner(Owner) {};
    ~MonsterHandler() = default;

    void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
    void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
    void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};