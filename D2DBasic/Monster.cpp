#include "Monster.h"
#include "D2DEngine.h"

Monster::Monster()
{

	AnimationScene* m_pAnimationScene = CreateComponent<AnimationScene>();
	SetRootScene(m_pAnimationScene);
	//Movemont
	m_pMovement = CreateComponent<Movement>();
	m_pMovement->SetSceneComponent(m_pAnimationScene);
	m_pMovement->SetSpeed(0.5f);
	m_pCollisionBox = CreateComponent<BoxCollider>();
	m_pCollisionBox->SetParent(m_pAnimationScene);
	m_pCollisionBox->SetCollisionType(CollisionType::Overlap);
	
	SetRootScene(m_pAnimationScene);
}

Monster::~Monster()
{

}

void Monster::Update(float time) {
	//float targetx = target->m_pRootScene->m_RelativeLocation.x;
	//float targety= target->m_pRootScene->m_RelativeLocation.y;
	m_pMovement->SetDirectionNormalize({ 1, 0 });
	m_pMovement->SetSpeed(100.f);
	__super::Update(time);
}