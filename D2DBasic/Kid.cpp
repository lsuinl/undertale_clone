#include "Kid.h"
#include "ScreenManager.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "BattleUI.h"

Kid::Kid()
{
	battleStart = new AnimationScene(); //전투시작
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/charcacter/kids.png", &battleStart->m_pBitmap);
	battleStart->LoadAnimationAsset(L"../Resource/charcacter/kids.png", L"../Resource/csv/battlestart.csv");
	battleStart->m_RelativeScale = { 1.6,1.6 };
	battleStart->m_size = { 27,26 }; battleStart->m_RelativeLocation = { 4300,2970 };
}

void Kid::Update(float time)
{
	battleStart->Update(time);
	if(!battle) __super::Update(time);
	if (text.GetIsEnd()&& !battle) { //채팅종료
		battle = true;
		battleStart->SetAnimation(14, false);
		SoundManager::GetInstance()->PlayMusic(eSoundList::BattleStart, eSoundChannel::Effect);
	}
}

void Kid::Render(D2DEngine* pRenderTarget)
{
	if (!battle)__super::Render(pRenderTarget);
	else if (battle) {
		battleStart->Render(pRenderTarget);
		if (battleStart->isEnd()) {
			SoundManager::GetInstance()->PlayMusic(eSoundList::Battle, eSoundChannel::BGM);
			SoundManager::GetInstance()->LoadMusic(eSoundList::typeing,true,"../Resource/music/effect/flower.mp3");
			ScreenManager::pInstanc->CreateWorld<BattleUI>();
		}
	}
}
