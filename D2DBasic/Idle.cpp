#include "Idle.h"

void IdleState::Enter()
{
	AnimationScene* ani = dynamic_cast<AnimationScene*>(GetOwner()->GetOwner()->m_pRootScene);
	ani->SetAnimation(2, false);
}

void IdleState::Update(float DeltaTime)
{
	if (death) {
		FiniteStateMachine* fsm = GetOwner();
		fsm->m_pNextState = fsm->m_pStates["Death"];
		death = false;
	}
	else if (attack) {
		FiniteStateMachine* fsm = GetOwner();
		fsm->m_pNextState = fsm->m_pStates["Attack"];
		attack = false;
	}
	
}

void IdleState::Exit()
{
}
