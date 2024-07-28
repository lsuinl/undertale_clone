#include "NPC.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "ScreenManager.h"
#include "Battle.h"
NPC::NPC()
{
	AnimationScene* m_pAnimationScene = CreateComponent<AnimationScene>();
	m_pCollisionBox = CreateComponent<BoxCollider>();
	m_pCollisionBox->SetCollisionType(CollisionType::Block);
	m_pCollisionBox->SetParent(m_pAnimationScene);
	m_pCollisionBox->notify = notify;

	m_pChatCollisionBox = CreateComponent<BoxCollider>();
	m_pChatCollisionBox->SetCollisionType(CollisionType::Overlap);
	m_pChatCollisionBox->SetParent(m_pAnimationScene);
	SetRootScene(m_pAnimationScene);
	m_pChatCollisionBox->notify = notify;
	m_pChatCollisionBox->exSize = true;
}


NPC::~NPC()
{
}

void NPC::Update(float time)
{
	inputTime += time;
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000)&&inputTime>0.2f) {
		inputTime = 0.0f;
		if (talkable && !isTalk) {
			isTalk = true;
			SoundManager::GetInstance()->LoadMusic(eSoundList::typeing, false, "../Resource/music/effect/overtexting.mp3");
			text.ReadFile(L"../Resource/text/kid.txt");
			text.SetTimeout(false);
			//텍스트박스 생성
			chat = new BitmapScene();
			ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/textbox.png", &chat->m_pBitmap);
			chat->destinationRect = D2D1::RectF(50, 500, 990, 750);
			chat->sourceRect = D2D1::RectF(227, 228, 518, 306);
		}
		else if (isTalk) text.NextText();
	}
	if (isTalk) text.Update(time);
	__super::Update(time);
}

void NPC::Render(D2DEngine* pRenderTarget)
{
	__super::Render(pRenderTarget);
	if (chat != nullptr) {
		std::wstring context = text.GetText();
		pRenderTarget->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
		chat->Render(pRenderTarget);
		pRenderTarget->DrawTextsize(context.c_str(), 90, 800, 550, 800);
	}
	if (text.GetIsEnd()) {//채팅종료
		ScreenManager::pInstanc->CreateWorld<Battle>();
		isTalk = false;
		chat = nullptr;
	}
}
