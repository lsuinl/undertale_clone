#pragma once
#include "GameObject.h"
#include "Movement.h"
#include "CameraScene.h"
#include "BoxCollider.h"
#include "FiniteStateMachine.h"
class AnimationScene;
class Movement;
class Character :public GameObject
{
public:
	Character();
	virtual ~Character();
	int HP=100;
	CameraScene* Camera;
	FiniteStateMachine* FSMS;
	BoxCollider* m_pCollisionBox = nullptr;
	Movement* m_pMovement = nullptr;
	
	int GetHP() { return HP; }
	void Damage(int n);
	virtual void Update(float time) override;
};

