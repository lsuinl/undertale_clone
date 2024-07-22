#include "Battle.h"
#include "ResourceManager.h"
Battle::Battle()
{
	//m_CullingBoundDefault.SetExtent(width / 2, height / 2);
	//m_CullingBoundDefault.SetCenter(width / 2, width / 2);
	m_CullingBoundDefault.SetExtent(130, 130);
	m_CullingBoundDefault.SetCenter(495, 495);

	//배경
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

	//캐릭터
	Player = CreateGameObject<Character>();
	CreatePlayer(Player, ani);
	CreateWalls(walls, ani, 330, 600, 350, 30);
	CreateWalls(walls, ani, 330, 270, 350, 30);
	CreateWalls(walls, ani, 320, 270, 30, 350);
	CreateWalls(walls, ani, 650, 270, 30, 350);
}

Battle::~Battle()
{

}

void Battle::Update(float deltaTime)
{
	__super::Update(deltaTime);
	monsterTime += deltaTime;
	PlayTime += deltaTime;
	if (PlayTime > ClearTime) { //페이즈 클리어!
		while (m_GameObjects.size() != 5)
			m_GameObjects.erase(m_GameObjects.begin() + 5);
		Level++;
		monsterTime = 0.0f;
		PlayTime = 0;
	}
	if (monsterTime > CreateTime) { //몬스터 생성
		monsterTime = 0;
		CreateMonster(Monsters, Player, ani);
	}
	if (m_GameObjects.size() > 20)  m_GameObjects.erase(m_GameObjects.begin() + 5); //지나간 몬스터 없애기

}

void Battle::Render(D2DEngine* pRenderTarget)
{
	//__super::Render(pRenderTarget);
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
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/hearts.png", &ani->m_pBitmap);
	ani->LoadAnimationAsset(L"../Resource/hearts.png", L"../Resource/kenmove.csv");
	ani->m_RelativeScale = { 1.5,1.5 };
	float y = random(320, 570);
	ani->m_size = { 25,25 }; ani->m_RelativeLocation = { 200,y }; ani->SetAnimation(5, false);
	monster.back()->target = Players;
}
