#include "Character.h"
#include "D2DEngine.h"
#include "Attack.h"
#include "Idle.h"
#include "Death.h"
int Character::HP;
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
    //체력바 셋팅
    ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/hp.png", &hp->m_pBitmap);
    hp->destinationRect = D2D1::RectF(400, 600, 550, 660);
    hp->sourceRect = D2D1::RectF(0, 0.f, 1080, 960.f);
    ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/fullhp.png", &hpback->m_pBitmap);
    hpback->destinationRect = D2D1::RectF(400, 600, 550 + (HP * 5), 660);
    hpback->sourceRect = D2D1::RectF(0, 0.f, 1080, 960.f);
}

Character::~Character()
{

}

void Character::Damage(int n)
{
   IdleState* idle = dynamic_cast<IdleState*>(FSMS->m_pCurrState);
   if (idle) {
       Character::HP -= n;
       Character::HP > -30 ? idle->attack = true : idle->death = true;
       if (Character::HP <= -30) {
           death = true;
           Character::HP = -30;
       }
       hpback->destinationRect = D2D1::RectF(400, 600, 550 + (HP * 5), 660);
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
    hp->Render(pRenderTarget);
    hpback->Render(pRenderTarget);
    pRenderTarget->DrawTextsize(L"HP", 350, 650, 600, 700); //150 -30 ,5
    pRenderTarget->DrawTextsize((std::to_wstring(30 + Character::HP)+L"/30").c_str(), 550, 750, 600, 700);

}
