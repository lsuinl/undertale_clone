#include "Character.h"
#include "D2DEngine.h"
#include "Attack.h"
#include "Idle.h"
#include "Death.h"
Character::Character()
{
	AnimationScene* m_pAnimationScene = CreateComponent<AnimationScene>();
	Camera = new CameraScene();
	m_pMovement = CreateComponent<Movement>();
	m_pMovement->SetSceneComponent(m_pAnimationScene);
	m_pMovement->SetSpeed(10);
	m_pCollisionBox = CreateComponent<BoxCollider>();
    m_pCollisionBox->SetCollisionType(CollisionType::Block);
    m_pCollisionBox->SetParent(m_pAnimationScene);
    FSMS = CreateComponent<FiniteStateMachine>();
    IdleState* Idle = FSMS->CreateState<IdleState>("Idle"); Idle->movement = m_pMovement;
    DeathState* Death = FSMS->CreateState<DeathState>("Death"); Death->movement = m_pMovement;
    AttackState* Attack = FSMS->CreateState<AttackState>("Attack"); Attack->movement = m_pMovement;
    FSMS->SetOwner(this);
    m_pCollisionBox->notify = notify;
    SetRootScene(m_pAnimationScene);
}

Character::~Character()
{

}

void Character::Damage(int n)
{
   IdleState* idle = dynamic_cast<IdleState*>(FSMS->m_pCurrState);
   if (idle) {
       HP -= n;
       HP > 0 ? idle->attack = true : idle->death = true;
      if(HP <=0) death = true;
   }
}

void Character::Update(float time) {
	__super::Update(time);
    m_pMovement->SetSpeed(0);
   if (GetAsyncKeyState(VK_UP) & 0x8000) {//위
       m_pMovement->SetSpeed(200.f);
       m_pMovement->SetDirectionNormalize({ 0, -1 });
   }
   if (GetAsyncKeyState(VK_DOWN) & 0x8000) {//아래
       m_pMovement->SetSpeed(200.f);
       m_pMovement->SetDirectionNormalize({ 0, 1 });
   }
   if (GetAsyncKeyState(VK_LEFT) & 0x8000) {//왼쪽
       m_pMovement->SetSpeed(200.f);
       m_pMovement->SetDirectionNormalize({ -1, 0 });
   }
   if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {//오른쪽
       m_pMovement->SetSpeed(200.f);
       m_pMovement->SetDirectionNormalize({ 1, 0 });
   }
   if (death) m_pMovement->SetSpeed(0);
}

void Character::Render(D2DEngine* pRenderTarget)
{
    __super::Render(pRenderTarget);
}
