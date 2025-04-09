#include "Ending.h"
#include "SoundManager.h"
#include "ResourceManager.h"
Ending::Ending()
{
	m_Background.push_back(new BitmapScene());
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/introduction.png", &m_Background.back()->m_pBitmap);
	m_Background.back()->destinationRect = D2D1::RectF(0, 0.f, 1080, 960.f);
	m_Background.back()->sourceRect = D2D1::RectF(10, 3140, 335, 3380);
	SoundManager::GetInstance()->StopMusic(eSoundChannel::typing);
	SoundManager::GetInstance()->PlayMusic(eSoundList::Ending, eSoundChannel::BGM);
}

Ending::~Ending()
{

}

void Ending::Update(float deltaTime)
{
	__super::Update(deltaTime);
	engingTime += deltaTime;
	if (GetAsyncKeyState(VK_RETURN) & 0x8000 && engingTime>4.0f)
		PostQuitMessage(0);
}

void Ending::Render(D2DEngine* pRenderTarget)
{
	__super::Render(pRenderTarget);
	float y = engingTime < 0 ? 0 : engingTime;

	pRenderTarget->DrawTextsize(L"해피엔딩입니다..\n\n그런걸로해주세용..", 350, 1300, 1200-(y * 30), 20000);
	pRenderTarget->DrawTextsize(L"만든이: 김수인", 370, 1300, 900-(y * 30), 20000);
}
