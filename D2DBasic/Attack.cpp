#include "Attack.h"
void AttackState::Enter()
{
	ani = dynamic_cast<AnimationScene*>(GetOwner()->GetOwner()->m_pRootScene);
	ani->SetAnimation(3, false);
}

void AttackState::Update(float DeltaTime)
{
	if (ani->isEnd()) {
		FiniteStateMachine* fsm = GetOwner();
		fsm->m_pNextState = fsm->m_pStates["Idle"];
	}
}

void AttackState::Exit()
{
}
