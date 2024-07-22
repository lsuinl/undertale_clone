#pragma once
#include "FSMState.h"
#include "FiniteStateMachine.h"
#include "pch.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Movement.h"
// Run ���� Ŭ����
class DeathState : public FSMState
{
public:
    Movement* movement;
    AnimationScene* ani;
    DeathState(FiniteStateMachine* pOwner, std::string name) : FSMState(pOwner, name) {}
    void Enter() override;
    void Update(float DeltaTime) override;
    void Exit() override;
};

