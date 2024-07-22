#include "pch.h"
#include "World.h"
#include "D2DEngine.h"
#include "ResourceManager.h"


World::World()
{
	//리소스 매니저 초기화
	float width = 1024;
	float height = 768;
}

World::~World()
{

}

void World::Update(float deltaTime)
{
	std::vector<BoxCollider*> boxComponents;
	if(Player)SetCullingBound(&Player->Camera->m_ViewBoundBox);
	for (auto& obj : m_GameObjects) {
		obj->Update(deltaTime);
		
		for (auto& com : obj->m_OwnedComponents) { //충돌체 찾기
			BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(com);
			if (boxCollider) {
				boxCollider->ClearAndBackupCollideState();
				boxComponents.push_back(boxCollider);
			}
		}
	}

	//충돌검사
	for (size_t i = 0; i < boxComponents.size(); i++) {
		for (size_t j = 0; j < boxComponents.size(); j++) {
			if (boxComponents[i]->GetOwner() == boxComponents[j]->GetOwner())continue; //같은 오브젝트
			if (!boxComponents[i]->IsCollide(boxComponents[j])) continue; //충돌 안하는 경우
			if (boxComponents[i]->GetCollisionType() == CollisionType::Block && boxComponents[j]->GetCollisionType() == CollisionType::Block) {//부딫힘!
				boxComponents[i]->ProcessBlock(boxComponents[j]); //부딫힘 처리.
				boxComponents[j]->ProcessBlock(boxComponents[i]); 
				
			}
			else { //통과! (이벤트처리)
				boxComponents[i]->InsertCollideState(boxComponents[j]); //부딫힘 처리.
				boxComponents[j]->InsertCollideState(boxComponents[i]);
			}
		}
	}


	//begitn, end흠
	for (auto& components : boxComponents)
		components->ProcessOverlap();

}

void World::Render(D2DEngine* pRenderTarget)
{
	//배경은 그냥 그려요
	for (auto& back : m_Background) {
		back->Render(pRenderTarget);
	}
	for (auto& obj : m_GameObjects)
	{
		if (m_pCullingBound->CheckIntersect(obj->GetBoundBox()))
		{
			obj->Render(pRenderTarget);
		}
	}
}

void World::Clear()
{
	m_GameObjects.clear();
}


void World::CreateWalls(std::vector<Wall*> walls, AnimationScene* ani, float x, float y,float width, float height) {
	walls.push_back(World::CreateGameObject<Wall>());
	ani = dynamic_cast<AnimationScene*>(walls.back()->m_pRootScene);
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/hearts.png", &ani->m_pBitmap);
	ani->LoadAnimationAsset(L"../Resource/hearts.png", L"../Resource/csv/idle.csv");
	ani->m_RelativeScale = { 0,0};
	ani->m_size = { width, height }; ani->m_RelativeLocation = { x,y }; ani->SetAnimation(2, false);
}

void World::CreatePlayer(Character* Player, AnimationScene* ani)
{
	ani = dynamic_cast<AnimationScene*>(Player->m_pRootScene);
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/hearts.png", &ani->m_pBitmap);
	ani->LoadAnimationAsset(L"../Resource/hearts.png", L"../Resource/csv/idle.csv");
	ani->LoadAnimationAsset(L"../Resource/hearts.png", L"../Resource/csv/attack.csv");
	ani->LoadAnimationAsset(L"../Resource/hearts.png", L"../Resource/csv/death.csv");
	ani->m_RelativeScale = { 1.6,1.6 };
	ani->m_size = { 27,26 }; ani->m_RelativeLocation = { 485,430 }; ani->SetAnimation(2, false);
}


int World::random(int min, int max)
{
	std::uniform_int_distribution<int> range(min, max);
	std::random_device rd;
	std::mt19937 gen(rd());
	return range(gen);
}
