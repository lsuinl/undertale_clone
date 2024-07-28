#include "Hero.h"
#include "D2DEngine.h"
#include "HeroMove.h"
#include "HeroIdle.h"
Hero::Hero()
{
    AnimationScene* m_pAnimationScene = CreateComponent<AnimationScene>();
    Camera = CreateComponent<CameraScene>();
    m_pMovement = CreateComponent<Movement>();
    m_pMovement->SetSceneComponent(m_pAnimationScene);
    m_pMovement->SetSpeed(10);
    m_pCollisionBox = CreateComponent<BoxCollider>();
    m_pCollisionBox->SetCollisionType(CollisionType::Block);
    m_pCollisionBox->SetParent(m_pAnimationScene);
    FSMS = CreateComponent<FiniteStateMachine>();
    HeroIdle* Idle = FSMS->CreateState<HeroIdle>("HeroIdle");
    HeroMove* Move = FSMS->CreateState<HeroMove>("HeroMove");
    FSMS->SetOwner(this);
    m_pCollisionBox->notify = notify;
    SetRootScene(m_pAnimationScene);
}

Hero::~Hero()
{

}

void Hero::Update(float time) {
    __super::Update(time);
    m_pMovement->SetSpeed(0);
    if (GetAsyncKeyState(VK_UP) & 0x8000) {//위
        m_pMovement->SetSpeed(500.f);
        m_pMovement->SetDirectionNormalize({ 0, -1 });
        FSMS->m_pCurrState->setForward(1);
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {//아래
        m_pMovement->SetSpeed(500.f);
        m_pMovement->SetDirectionNormalize({ 0, 1 });
        FSMS->m_pCurrState->setForward(2);
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {//왼쪽
        m_pMovement->SetSpeed(500.f);
        m_pMovement->SetDirectionNormalize({ -1, 0 });
        FSMS->m_pCurrState->setForward(3);
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {//오른쪽
        m_pMovement->SetSpeed(500.f);
        m_pMovement->SetDirectionNormalize({ 1, 0 });
        FSMS->m_pCurrState->setForward(4);
    }

    if (m_pMovement->GetSpeed() == 0) 
        FSMS->m_pNextState = FSMS->m_pStates["HeroIdle"];
    else 
        FSMS->m_pNextState = FSMS->m_pStates["HeroMove"];

    int dx = Camera->m_ViewBoundBox.m_Extent.x, dy = Camera->m_ViewBoundBox.m_Extent.y;
    float fixX;
    if (m_pRootScene->m_RelativeLocation.x < 500) fixX = 510;
    else if (m_pRootScene->m_RelativeLocation.x > 9100) fixX = 9100;
    else fixX = m_pRootScene->m_RelativeLocation.x;
    Camera->m_RelativeLocation = { fixX - dx,fixY - dy };
    D2DEngine::m_CameraTransform = Camera->m_WorldTransform;
}