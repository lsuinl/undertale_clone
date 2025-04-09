#include "BattleUI.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ScreenManager.h"
#include "Battle.h"

BattleUI::BattleUI()
{
	Level+=1;
	addBack(L"../Resource/charcacter/kids.png",D2D1::RectF(370, 30.f, 650, 310),D2D1::RectF(0.0f, 0.0f, 100.f, 100.f));
	addBack(L"../Resource/background/battle.png", D2D1::RectF(0.0f, 0.0f, 1024, 380), D2D1::RectF(10.0f, 330.0f, 645.f, 540.f));
	//버튼들
	addBack(L"../Resource/ui/battle.png", D2D1::RectF(70, 640, 270, 740), D2D1::RectF(8, 9, 118, 51));
	addBack(L"../Resource/ui/battle.png", D2D1::RectF(290, 640, 490, 740), D2D1::RectF(8, 111, 118, 153));
	addBack(L"../Resource/ui/battle.png", D2D1::RectF(510, 640, 710, 740), D2D1::RectF(8, 212, 118, 254));
	addBack(L"../Resource/ui/battle.png", D2D1::RectF(730, 640, 930, 740), D2D1::RectF(8, 313, 118, 355));

	//캐릭터
	focus = new AnimationScene();
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/hearts.png", &focus->m_pBitmap);
	focus->LoadAnimationAsset(L"../Resource/hearts.png", L"../Resource/csv/idle.csv");
	focus->m_RelativeScale = { 3,3 };
	focus->m_size = { 27,26 }; focus->m_RelativeLocation = { 200,600 };
	focus->SetAnimation(2, false);
	D2DEngine::m_CameraTransform = D2D1::Matrix3x2F::Identity();
	//텍스트 
	text.ReadFile(L"../Resource/text/battleui.txt");
	text.index = Level > 5 ? 5 : Level;
	text.SetTimeout(false);
}

BattleUI::~BattleUI()
{
}

void BattleUI::Update(float deltaTime)
{
	__super::Update(deltaTime);
	focus->Update(deltaTime);
	text.Update(deltaTime);
	inputTime += deltaTime;
	if (!battleStart) {
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 && state > 1 && inputTime > 0.3f) {//왼쪽
			inputTime = 0.0f;
			state--;
			SoundManager::GetInstance()->PlayMusic(eSoundList::click, eSoundChannel::Effect);
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && state < 4 && inputTime > 0.3f) {//오른쪽
			inputTime = 0.0f;
			state++;
			SoundManager::GetInstance()->PlayMusic(eSoundList::click, eSoundChannel::Effect);
		}
		else if (GetAsyncKeyState(VK_RETURN) & 0x8000 && inputTime > 0.3f && text.GetIsSentenceEnd()) {
			SoundManager::GetInstance()->PlayMusic(eSoundList::click, eSoundChannel::Effect);
			inputTime = 0;
			battleStart = true;
		}
	}
	else {
		if (inputTime > 1.0f) {
			ScreenManager::pInstanc->CreateWorld<Battle>();
		}
	}
	focus->m_RelativeLocation = { -140.0f + (state * 220),665.0f  };
}

void BattleUI::Render(D2DEngine* pRenderTarget)
{
	__super::Render(pRenderTarget);
	focus->Render(pRenderTarget);
	//pRenderTarget->DrawSquare(350, 650, 300, 600);
	if(battleStart)
	pRenderTarget->DrawSquare(
		100+(inputTime*250), 
		900- (inputTime * 250),
		400 - (inputTime * 100),
		600 
	);
	else {
		pRenderTarget->DrawSquare(100, 900, 400, 600);
		std::wstring context = text.GetText();
		pRenderTarget->DrawTextsize(context.c_str(), 130, 900, 430, 600);
	}

}


void BattleUI::addBack(std::wstring filename, D2D1_RECT_F des, D2D1_RECT_F sou) {
	m_Background.push_back(new BitmapScene());		 
	ResourceManager::pInstance->CreateD2DBitmapFromFile(filename, &m_Background.back()->m_pBitmap);
	m_Background.back()->destinationRect = des;
	m_Background.back()->sourceRect = sou;
}
