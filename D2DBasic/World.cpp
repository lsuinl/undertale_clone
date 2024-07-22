#include "pch.h"
#include "World.h"
#include "D2DEngine.h"
#include "ResourceManager.h"


World::World()
{
	//���ҽ� �Ŵ��� �ʱ�ȭ
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
		
		for (auto& com : obj->m_OwnedComponents) { //�浹ü ã��
			BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(com);
			if (boxCollider) {
				boxCollider->ClearAndBackupCollideState();
				boxComponents.push_back(boxCollider);
			}
		}
	}

	//�浹�˻�
	for (size_t i = 0; i < boxComponents.size(); i++) {
		for (size_t j = 0; j < boxComponents.size(); j++) {
			if (boxComponents[i]->GetOwner() == boxComponents[j]->GetOwner())continue; //���� ������Ʈ
			if (!boxComponents[i]->IsCollide(boxComponents[j])) continue; //�浹 ���ϴ� ���
			if (boxComponents[i]->GetCollisionType() == CollisionType::Block && boxComponents[j]->GetCollisionType() == CollisionType::Block) {//�΋H��!
				boxComponents[i]->ProcessBlock(boxComponents[j]); //�΋H�� ó��.
				boxComponents[j]->ProcessBlock(boxComponents[i]); 
				
			}
			else { //���! (�̺�Ʈó��)
				boxComponents[i]->InsertCollideState(boxComponents[j]); //�΋H�� ó��.
				boxComponents[j]->InsertCollideState(boxComponents[i]);
			}
		}
	}


	//begitn, end��
	for (auto& components : boxComponents)
		components->ProcessOverlap();

}

void World::Render(D2DEngine* pRenderTarget)
{
	//����� �׳� �׷���
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
