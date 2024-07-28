#include "Title.h"
#include "ResourceManager.h"
#include "ScreenManager.h"
#include "SoundManager.h"
#include "snowMap.h"
Title::Title()
{
	m_Background.push_back(new BitmapScene());		 
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/introduction.png", &m_Background.back()->m_pBitmap);
	m_Background.back()->destinationRect = D2D1::RectF(0, 0.f, 1080, 960.f);
	m_Background.back()->sourceRect = D2D1::RectF(10, 3140, 335, 3380);

	m_Background.push_back(new BitmapScene());//press anykey
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/press.png", &m_Background.back()->m_pBitmap);
	m_Background.back()->destinationRect = D2D1::RectF(350, 400, 650, 500.f);
	m_Background.back()->sourceRect = D2D1::RectF(0, 0, 0, 0);

	SoundManager::GetInstance()->PlayMusic(eSoundList::TitleEffect, eSoundChannel::BGM);
}

Title::~Title()
{
} 

void Title::Update(float deltaTime)
{
	__super::Update(deltaTime);
	PressTime += deltaTime;
	if (PressTime > limitTime && !start) { //º¯°æ
		start = true;

		SoundManager::GetInstance()->PlayMusic(eSoundList::Title, eSoundChannel::BGM);
		m_Background.back()->sourceRect = D2D1::RectF(0, 0, 287, 49);
	}

	if(start && ((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000))) {
		SoundManager::GetInstance()->StopMusic(eSoundChannel::BGM);
		ScreenManager::pInstanc->CreateWorld<snowMap>();
	}
}

void Title::Render(D2DEngine* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
