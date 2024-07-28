#include "GameOver.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "ScreenManager.h"
#include "Title.h"
GameOver::GameOver()
{
	m_Background.push_back(new BitmapScene());
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/gameover.png", &m_Background.back()->m_pBitmap);
	m_Background.back()->destinationRect = D2D1::RectF(200, 100, 800, 400);
	m_Background.back()->sourceRect = D2D1::RectF(0, 0.f, 1080, 960.f);
}

GameOver::~GameOver()
{
}

void GameOver::Update(float deltaTime)
{
	time += deltaTime;
	if (time < 48.0f) {
		text.Update(deltaTime);
		if (((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000))) {
			SoundManager::GetInstance()->StopMusic(eSoundChannel::BGM);
			SoundManager::GetInstance()->StopMusic(eSoundChannel::Effect);
			ScreenManager::pInstanc->CreateWorld<Title>();
		}
	}
	if (time>50.0f) {
		SoundManager::GetInstance()->LoadMusic(eSoundList::typeing, true, "../Resource/music/effect/overtexting.mp3");
		SoundManager::GetInstance()->PlayMusic(eSoundList::GameOver, eSoundChannel::BGM);
		text.ReadFile(L"../Resource/text/over.txt");
		time = 0.0f;
	}
	__super::Update(deltaTime);
}

void GameOver::Render(D2DEngine* pRenderTarget)
{
	if (time < 48.0f) 
		__super::Render(pRenderTarget);
	std::wstring context = text.GetText();
	pRenderTarget->DrawTextsize(context.c_str(), 300, 800, 500, 800);
}
