#pragma once
#include "FSMState.h"
#include "FiniteStateMachine.h"
#include "pch.h"
#include "Movement.h"
#include "GameObject.h"
#include "AnimationScene.h"

// Idle 상태 클래스
class HeroMove : public FSMState
{
public:
    int curForward=1;
    HeroMove(FiniteStateMachine* pOwner, std::string name) : FSMState(pOwner, name) {}

    void Enter() override;
    void Update(float DeltaTime) override;
    void Exit() override;
};
