#pragma once
#include "GameObject.h"
#include "Movement.h"
#include "CameraScene.h"
#include "FSMState.h"
#include "FiniteStateMachine.h"
#include "BoxCollider.h"
#include "Collider.h"
#include "MonsterHandler.h"

class Monster : public GameObject
{
public:
    Monster();
    virtual ~Monster();
    MonsterHandler* notify= new MonsterHandler(this);
    GameObject* target;
    Movement* m_pMovement = nullptr;
    BoxCollider* m_pCollisionBox = nullptr;
    float times=0;

    virtual void Update(float time) override;
    virtual void Render(D2DEngine* pRenderTarget) override;
};

