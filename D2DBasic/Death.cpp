#include "Death.h"
#include "GameObject.h"
#include "ScreenManager.h"
void DeathState::Enter()
{
	ani = dynamic_cast<AnimationScene*>(GetOwner()->GetOwner()->m_pRootScene);
	ani->SetAnimation(4, false);
}

void DeathState::Update(float DeltaTime)
{
	if (ani->isEnd())
		ScreenManager::pInstanc->LoadWorld(1);
}

void DeathState::Exit()
{
}
