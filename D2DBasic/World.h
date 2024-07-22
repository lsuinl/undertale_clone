#pragma once
#include "pch.h"
#include "D2DEngine.h"
#include "GameObject.h"
#include "AABB.h"
#include "Character.h"
#include "Monster.h"
#include "wall.h"

// ������ ���踦 ��Ÿ���� Ŭ����
// GameObectŸ������ ������ ��ü���� �����Ͽ� Update, Render�� ȣ���Ѵ�.
class World
{
public:
	World();
	virtual ~World();
	AABB* m_pCullingBound = nullptr; //����

	std::vector <BitmapScene*> m_Background; //�⺻ ���
	
	AnimationScene* ani = nullptr;//�ִϸ��̼� ����
 	std::vector<GameObject*> m_GameObjects; //��� ������Ʈ ����
	std::vector<Wall*> walls; //��
public:
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
	void Clear();
	void SetCullingBound(AABB* pBound) { m_pCullingBound = pBound; }

	template<typename T>
	T* CreateGameObject()	// ���ø� �Լ��� GameObject�� ����
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);	// GameObject�� ��ӹ��� Ŭ������ ������ �� �ִ�.
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

