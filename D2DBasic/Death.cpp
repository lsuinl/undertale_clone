#include "Death.h"
#include "GameObject.h"
#include "ScreenManager.h"
#include "SoundManager.h"
#include "GameOver.h"

void DeathState::Enter()
{
	ani = dynamic_cast<AnimationScene*>(GetOwner()->GetOwner()->m_pRootScene);
	ani->SetAnimation(4, false);
	SoundManager::GetInstance()->StopMusic(eSoundChannel::BGM);
	SoundManager::GetInstance()->PlayMusic(eSoundList::Death, eSoundChannel::Effect);
}

void DeathState::Update(float DeltaTime)
{
	if (ani->isEnd()) {
		ScreenManager::pInstanc->CreateWorld<GameOver>();
	}
}

void DeathState::Exit()
{
}
