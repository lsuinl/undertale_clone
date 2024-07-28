#include "XYSystem.h"
#include "util.h"
#include "SoundManager.h"

XYSystem::XYSystem() {}
XYSystem::~XYSystem() {}

void XYSystem::Initialize(HINSTANCE hInstance)
{
	__super::Initialize(hInstance);
	//ScreenManager::pInstanc->CreateWorld<Story>(); //이게진짜
	SoundManager::GetInstance()->LoadMusic(eSoundList::typeing, true, "../Resource/music/effect/typeing.mp3");
	SoundManager::GetInstance()->LoadMusic(eSoundList::GameOver, false, "../Resource/music/bgm/gameover.mp3");
	SoundManager::GetInstance()->LoadMusic(eSoundList::TitleEffect, true, "../Resource/music/effect/title.mp3");
	SoundManager::GetInstance()->LoadMusic(eSoundList::Title, true, "../Resource/music/bgm/title.mp3");
	SoundManager::GetInstance()->LoadMusic(eSoundList::Story, true, "../Resource/music/bgm/story.mp3");
	SoundManager::GetInstance()->LoadMusic(eSoundList::Death, false, "../Resource/music/effect/death.mp3");
	SoundManager::GetInstance()->LoadMusic(eSoundList::snowMap, true, "../Resource/music/bgm/map.mp3");
	SoundManager::GetInstance()->LoadMusic(eSoundList::Attack, false, "../Resource/music/effect/damege.mp3");
	SoundManager::GetInstance()->LoadMusic(eSoundList::Battle, true, "../Resource/music/bgm/fight.mp3");
	SoundManager::GetInstance()->SetVolume(2.0f, 1);
	ScreenManager::pInstanc->CreateWorld<Story>();
}
void XYSystem::Update(float times)
{
	ScreenManager::pInstanc->curWorld->Update(times);
}

void XYSystem::Finalize()
{
	__super::Finalize();
}

void XYSystem::Render()
{
	m_pRenderer->BeginDraw();
	ScreenManager::pInstanc->curWorld->Render(m_pRenderer);
	m_pRenderer->EndDraw();
}

