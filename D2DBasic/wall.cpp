#include "wall.h"

Wall::Wall()
{
	AnimationScene* m_pAnimationScene = CreateComponent<AnimationScene>();
	m_pCollisionBox = CreateComponent<BoxCollider>();
	m_pCollisionBox->SetCollisionType(CollisionType::Block);
	m_pCollisionBox->SetParent(m_pAnimationScene);
	SetRootScene(m_pAnimationScene);
}

Wall::~Wall()
{
}

void Wall::Update(float time)
{
	__super::Update(time);
}
