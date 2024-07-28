#include "Story.h"
#include "ResourceManager.h"
#include "ScreenManager.h"
#include "SoundManager.h"
#include "Title.h"
Story::Story()
{
	SoundManager::GetInstance()->LoadMusic(eSoundList::typeing, true, "../Resource/music/effect/typeing.mp3");
	intro.ReadFile(L"../Resource/text/introduction.txt");
	//¹è°æ
	background = CreateGameObject<GameObject>()->CreateComponent<AnimationScene>();
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/introduction.png", &background->m_pBitmap);
	background->LoadAnimationAsset(L"../Resource/ui/introduction.png", L"../Resource/introduction.csv");
	background->m_size = { 789,325 }; background->m_RelativeScale = { 3.2f,3.2f }; background->SetAnimation(6, false);
	SoundManager::GetInstance()->PlayMusic(eSoundList::Story, eSoundChannel::BGM);
}

Story::~Story()
{
}

void Story::Update(float deltaTime)
{
	//__super::Update(deltaTime);
	background->Update(deltaTime);
	intro.Update(deltaTime);
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000)|| (*background).isEnd()) {
		SoundManager::GetInstance()->StopMusic(eSoundChannel::BGM);
		SoundManager::GetInstance()->StopMusic(eSoundChannel::typing);
		ScreenManager::pInstanc->CreateWorld<Title>();
	}
}

void Story::Render(D2DEngine* pRenderTarget)
{
	// __super::Render(pRenderTarget);
	background->Render(pRenderTarget);
	std::wstring context = intro.GetText();
	pRenderTarget->DrawTextsize(context.c_str(), 160, 800, 500, 800);
}
