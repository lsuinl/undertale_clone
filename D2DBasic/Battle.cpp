#include "Battle.h"
#include "ResourceManager.h"
#include "ScreenManager.h"
#include "SoundManager.h"
#include "BattleUI.h"
#include "Ending.h"
#include "Story.h"

int BattleUI::Level;

Battle::Battle()
{
	//m_CullingBoundDefault.SetExtent(width / 2, height / 2);
	//m_CullingBoundDefault.SetCenter(width / 2, width / 2);
	m_CullingBoundDefault.SetExtent(130, 130);
	m_CullingBoundDefault.SetCenter(495, 495);	
	m_Background.push_back(new BitmapScene());		 //적..
	//ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/charcacter/kid.png", &m_Background.back()->m_pBitmap);
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/charcacter/kids.png", &m_Background.back()->m_pBitmap);
	//m_Background.back()->destinationRect = D2D1::RectF(420, 30.f, 600, 280);
	m_Background.back()->destinationRect = D2D1::RectF(370, 30.f, 650, 310);
	//m_Background.back()->sourceRect = D2D1::RectF(10.0f, 22.0f, 50.f, 88.f);
	m_Background.back()->sourceRect = D2D1::RectF(0.0f, 0.0f, 100.f, 100.f);

	m_Background.push_back(new BitmapScene());	//레이저
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/background/battle.png", &m_Background.back()->m_pBitmap);
	m_Background.back()->destinationRect = D2D1::RectF(0.0f, 0.0f, 1024, 380);
	m_Background.back()->sourceRect = D2D1::RectF(10.0f, 330.0f, 645.f, 540.f);
	CreateWalls(walls, ani, 330, 600, 350, 30);
	CreateWalls(walls, ani, 330, 270, 350, 30);
	CreateWalls(walls, ani, 320, 270, 30, 350);
	CreateWalls(walls, ani, 650, 270, 30, 350);
	//캐릭터
	Player = CreateGameObject<Character>();
	CreatePlayer(Player, ani);
	D2DEngine::m_CameraTransform = D2D1::Matrix3x2F::Identity();
	text.ReadFile(L"../Resource/text/battle.txt");
	text.SetTimeout(false);
	text.index = BattleUI::Level;
	//텍스트박스
	chat = new BitmapScene();
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/textbox.png", &chat->m_pBitmap);
	chat->destinationRect = D2D1::RectF(600, 50, 900, 250);
	chat->sourceRect = D2D1::RectF(20, 450, 257, 554);
	if(BattleUI::Level>5){
		goending = true;
		BattleUI::Level = 0;
	}
}

Battle::~Battle()
{

}

void Battle::Update(float deltaTime)
{
	if (goending) {
		SoundManager::GetInstance()->StopMusic(eSoundChannel::BGM);
		SoundManager::GetInstance()->StopMusic(eSoundChannel::Effect);
		ScreenManager::pInstanc->CreateWorld<Ending>();
	}
	text.Update(deltaTime);
	if (text.GetIsSentenceEnd()) {
		__super::Update(deltaTime);
		monsterTime += deltaTime;
		PlayTime += deltaTime;
		if (!Player->death) {
			if (PlayTime > ClearTime) { //페이즈 클리어!
				while (m_GameObjects.size() != 5)
					m_GameObjects.erase(m_GameObjects.begin() + 5);
				SoundManager::GetInstance()->StopMusic(eSoundChannel::Effect);
				ScreenManager::pInstanc->CreateWorld<BattleUI>();
				monsterTime = 0.0f;
				PlayTime = 0;
			}
			if (monsterTime > CreateTime) { //몬스터 생성
				monsterTime = 0;
				CreateMonster(Monsters, Player, ani);
			}
			if (m_GameObjects.size() > 20)  m_GameObjects.erase(m_GameObjects.begin() + 5); //지나간 몬스터 없애기
		}
	}
}

void Battle::Render(D2DEngine* pRenderTarget)
{
	//__super::Render(pRenderTarget);
	pRenderTarget->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	if (Player)SetCullingBound(&Player->Camera->m_ViewBoundBox);
	pRenderTarget->DrawSquare(350, 650, 300, 600);
	for (auto& back : m_Background) {
		back->Render(pRenderTarget);
	}

	for (auto& obj : m_GameObjects)
	{
		Monster* objs = dynamic_cast<Monster*>(obj);
		if (objs) {
			objs->GetBoundBox();
			if (m_CullingBoundDefault.CheckIntersect(obj->GetBoundBox())) {
				objs->Render(pRenderTarget);//적의 공격은 미니 월드에서 체크!
			}
		}
		else {
			if (m_pCullingBound->CheckIntersect(obj->GetBoundBox()))
			{
				obj->Render(pRenderTarget);
			}
		}
	}
	if (!text.GetIsSentenceEnd()) {
		chat->Render(pRenderTarget);
		std::wstring context = text.GetText();
		pRenderTarget->DrawTextChat(context.c_str(), 650, 900, 70, 250);
	}

}

void Battle::CreatePlayer(Character* Player, AnimationScene* ani)
{
	ani = dynamic_cast<AnimationScene*>(Player->m_pRootScene);
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/hearts.png", &ani->m_pBitmap);
	ani->LoadAnimationAsset(L"../Resource/hearts.png", L"../Resource/csv/idle.csv");
	ani->LoadAnimationAsset(L"../Resource/hearts.png", L"../Resource/csv/attack.csv");
	ani->LoadAnimationAsset(L"../Resource/hearts.png", L"../Resource/csv/death.csv");
	ani->m_RelativeScale = { 1.6,1.6 };
	ani->m_size = { 27,26 }; ani->m_RelativeLocation = { 485,430 }; ani->SetAnimation(2, false);
}

void Battle::CreateMonster(std::vector<Monster*> monster, Character* Players, AnimationScene* ani)
{
	//레벨별로 수치를 변환.
	monster.push_back(CreateGameObject<Monster>());	//몬스터
	ani = dynamic_cast<AnimationScene*>(monster.back()->m_pRootScene);
	float x,y;
	int direction;
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/attack.png", &ani->m_pBitmap);
	switch (BattleUI::Level)
	{
	case 1:
		//오른쪽으로 오는 음표
		CreateTime = 0.2;
		ani->LoadAnimationAsset(L"../Resource/attack.png", L"../Resource/csv/patten1.csv");
		ani->m_RelativeScale = { 1.5,1.5 };
		 y = random(320, 570);
		ani->m_size = { 25,25 }; ani->m_RelativeLocation = { 200,y }; ani->SetAnimation(5, false);
		monster.back()->target = Players;
		break;
	case 2:
		//떨어지는 말캉이
		CreateTime = 0.7;
		ani->LoadAnimationAsset(L"../Resource/attack.png", L"../Resource/csv/patten2.csv");
		ani->m_RelativeScale = { 2,2 };	ani->m_center = {22,20};
		ani->m_size = { 50,50 }; ani->m_RelativeLocation = { static_cast<float>(random(380, 630)),300}; ani->SetAnimation(28, false);
		monster.back()->target = Players;
		break;
	case 3:
		//위아래로 줄줄이 오리
		y = random(450, 550);
		CreateTime = 0.7;
		ani->LoadAnimationAsset(L"../Resource/attack.png", L"../Resource/csv/patten3.csv");//아래
		ani->m_RelativeScale = { 3,3 }; ani->m_center = { 5,5 };//13,35
		 ani->m_size = { 20,90 };  ani->m_RelativeLocation = { 750,y }; ani->SetAnimation(29, false);
		monster.back()->target = Players;

		monster.push_back(CreateGameObject<Monster>());	 //위
		ani = dynamic_cast<AnimationScene*>(monster.back()->m_pRootScene);
		ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/attack.png", &ani->m_pBitmap);
		ani->LoadAnimationAsset(L"../Resource/attack.png", L"../Resource/csv/patten3.csv");
		ani->m_RelativeScale = { 3,3 }; ani->m_center = { 5,5 };//13,35
		ani->m_size = { 20,90 }; ani->m_RelativeLocation = { 750,y-150 }; ani->SetAnimation(29, false);
		monster.back()->target = Players;
		break;
	case 4:
		direction = random(0, 3);
		//랜덤 푸슝 오리
		CreateTime = 0.3;
		ani->LoadAnimationAsset(L"../Resource/attack.png", L"../Resource/csv/patten4.csv");
		ani->m_RelativeScale = { 4,4 };
		switch (direction) {
		case 0: // 위로 
			x = random(340, 570);
			y = 600;
			ani->m_RelativeLocation = { x, y };
			ani->SetRelativeRotation(0);
			ani->m_size = { 30,130 }; ani->m_center = { 5,5 };
			break;
		case 1: // 오른쪽으로
			x = 200;
			y = random(320, 570);
			ani->m_RelativeLocation = { x, y };
			ani->SetRelativeRotation(90);
			ani->m_size = { 130,30 }; ani->m_center = { 9,32 };
			break;
		case 2: // 아래로
			x = random(340, 570);
			y = 200;
			ani->m_RelativeLocation = { x, y };
			ani->SetRelativeRotation(180);
			ani->m_size = { 30,130 }; ani->m_center = { 9,28 };
			break;
		case 3: // 왼쪽으로
			x = 750;
			y = random(320, 570);
			ani->m_RelativeLocation = { x, y };
			ani->SetRelativeRotation(270);
			ani->m_size = { 130,30 }; ani->m_center = { 10,5 };
			break;
		}
		ani->SetAnimation(30, false);
		monster.back()->target = Players;
		break;
	case 5:
		//둥실둥실 위로
		CreateTime = 0.4;
		ani->LoadAnimationAsset(L"../Resource/attack.png", L"../Resource/csv/patten5.csv");
		ani->m_RelativeScale = { 1.5,1.5 };
		x = random(340, 570);
		y = 600;
		ani->m_size = { 25,25 }; ani->m_RelativeLocation = { x,y }; ani->SetAnimation(31, false);
		monster.back()->target = Players;
		break;
	default:
		break;
	}
}
