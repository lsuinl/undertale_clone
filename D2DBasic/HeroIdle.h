#pragma once
#include "FSMState.h"
#include "FiniteStateMachine.h"
#include "pch.h"
#include "Movement.h"
#include "GameObject.h"
#include "AnimationScene.h"

// Idle ���� Ŭ����
class HeroIdle : public FSMState
{
public:
    int curForward;
    HeroIdle(FiniteStateMachine* pOwner, std::string name) : FSMState(pOwner, name) {}

    void Enter() override;
    void Update(float DeltaTime) override;
    void Exit() override;
};
