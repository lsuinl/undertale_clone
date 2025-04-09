#pragma once
#include "GameObject.h"
#include "Movement.h"
#include "CameraScene.h"
#include "BoxCollider.h"
#include "FiniteStateMachine.h"
#include "HeroHandler.h"
class AnimationScene;
class Movement;
class Hero :public GameObject
{
	float fixY = 2970.0f;
public:
	static bool isTalk;
	Hero();
	virtual ~Hero();
	CameraScene* Camera;
	Movement* m_pMovement = nullptr;
	HeroHandler* notify = new HeroHandler(this);
	
	FiniteStateMachine* FSMS;
	BoxCollider* m_pCollisionBox = nullptr;
	
	virtual void Update(float time) override;
};

