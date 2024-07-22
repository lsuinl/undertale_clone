#pragma once
#include "pch.h"
#include "D2DEngine.h"
#include "GameObject.h"
#include "AABB.h"
#include "Character.h"
#include "Monster.h"
#include "wall.h"

// 게임의 세계를 나타내는 클래스
// GameObect타입으로 생성된 객체들을 관리하여 Update, Render를 호출한다.
class World
{
public:
	World();
	virtual ~World();
	AABB* m_pCullingBound = nullptr; //월드

	std::vector <BitmapScene*> m_Background; //기본 배경
	
	AnimationScene* ani = nullptr;//애니메이션 관리
 	std::vector<GameObject*> m_GameObjects; //모든 오브젝트 관리
	std::vector<Wall*> walls; //벽
public:
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
	void Clear();
	void SetCullingBound(AABB* pBound) { m_pCullingBound = pBound; }

	template<typename T>
	T* CreateGameObject()	// 템플릿 함수로 GameObject를 생성
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);	// GameObject를 상속받은 클래스만 생성할 수 있다.
		T* newObject = new T();
		newObject->SetOwner(this);
		m_GameObjects.push_back(newObject);
		return newObject;
	}
	int random(int min, int max);
	void CreateWalls(std::vector<Wall*> walls, AnimationScene* ani, float x, float y, float width, float height);
	void CreatePlayer(Character* Player, AnimationScene* ani);
	//void CreateMonster(std::vector<Monster*> Player, Character* player, AnimationScene* ani);
};

