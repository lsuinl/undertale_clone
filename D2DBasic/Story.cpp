#include "Story.h"
#include "ResourceManager.h"
#include "ScreenManager.h"

Story::Story()
{
	intro.ReadFile(L"../Resource/introduction.txt");
	//¹è°æ
	background = CreateGameObject<GameObject>()->CreateComponent<AnimationScene>();
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/introduction.png", &background->m_pBitmap);
	background->LoadAnimationAsset(L"../Resource/ui/introduction.png", L"../Resource/introduction.csv");
	background->m_size = { 789,325 }; background->m_RelativeScale = { 3.2f,3.2f }; background->SetAnimation(6, false);
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
		ScreenManager::pInstanc->LoadWorld(1);
	}
}

void Story::Render(D2DEngine* pRenderTarget)
{
	// __super::Render(pRenderTarget);
	background->Render(pRenderTarget);
	std::wstring context = intro.GetText();
	pRenderTarget->DrawTextsize(context.c_str(), 160, 800, 500, 800);
}
