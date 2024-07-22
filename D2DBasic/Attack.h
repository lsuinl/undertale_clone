#pragma once
#include "FSMState.h"
#include "FiniteStateMachine.h"
#include "Movement.h"
#include "GameObject.h"
#include "pch.h"
#include "ResourceManager.h"
// Attck 상태 클래스
class AttackState : public FSMState
{
public:
    Movement* movement;
    AnimationScene* ani;
    AttackState(FiniteStateMachine* pOwner, std::string name) : FSMState(pOwner, name) {}

    void Enter() override;

    void Update(float DeltaTime) override;

    void Exit() override;
};