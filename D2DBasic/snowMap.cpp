#include "snowMap.h"
#include "ResourceManager.h"
#include "SoundManager.h"
snowMap::snowMap()
{
	AnimationScene* Background = CreateGameObject<GameObject>()->CreateComponent<AnimationScene>();	//배경
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/background/back.png", &Background->m_pBitmap);
 	Background->LoadAnimationAsset(L"../Resource/background/back.png", L"../Resource/csv/mapback.csv"); 
	Background->m_RelativeLocation = { 0,600 };
	Background->m_size = { 10000,10000 }; Background->m_RelativeScale = { 3.25f,3.25f }; Background->SetAnimation(7, false);

	Player = CreateGameObject<Hero>();	//캐릭터
	AnimationScene* ani = dynamic_cast<AnimationScene*>(Player->m_pRootScene);
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/charcacter/player.png", &ani->m_pBitmap);
 	ani->LoadAnimationAsset(L"../Resource/charcacter/player.png", L"../Resource/csv/herorun.csv");
 	ani->LoadAnimationAsset(L"../Resource/charcacter/player.png", L"../Resource/csv/herorunside.csv");
 	ani->LoadAnimationAsset(L"../Resource/charcacter/player.png", L"../Resource/csv/herorunback.csv");
 	ani->LoadAnimationAsset(L"../Resource/charcacter/player.png", L"../Resource/csv/heroidle.csv");
 	ani->LoadAnimationAsset(L"../Resource/charcacter/player.png", L"../Resource/csv/heroidleside.csv");
 	ani->LoadAnimationAsset(L"../Resource/charcacter/player.png", L"../Resource/csv/heroidleback.csv");
	ani->m_RelativeScale = { 3,3 };
	//시작 좌표만 바꾸기
	ani->m_size = { 127,110 }; ani->m_RelativeLocation = { 510,2970 }; ani->SetAnimation(10, false);

	SoundManager::GetInstance()->LoadMusic(eSoundList::snowMap, true, "../Resource/music/bgm/map.mp3");
	SoundManager::GetInstance()->PlayMusic(eSoundList::snowMap, eSoundChannel::BGM);
}

snowMap::~snowMap()
{
}

void snowMap::Update(float deltaTime)
{
	__super::Update(deltaTime);
	SetCullingBound(&Player->Camera->m_ViewBoundBox);
}

void snowMap::Render(D2DEngine* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
