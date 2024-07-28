#include "Attack.h"
#include "SoundManager.h"
void AttackState::Enter()
{
	ani = dynamic_cast<AnimationScene*>(GetOwner()->GetOwner()->m_pRootScene);
	ani->SetAnimation(3, false);
	SoundManager::GetInstance()->PlayMusic(eSoundList::Attack, eSoundChannel::Effect);
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
