#pragma once
#include "GameObject.h"
#include "Movement.h"
#include "CameraScene.h"
#include "FSMState.h"
#include "FiniteStateMachine.h"
#include "BoxCollider.h"

class AnimationScene;
class Movement;
class Monster :public GameObject
{
public:
	Monster();
	virtual ~Monster();
	GameObject* target;
	Movement* m_pMovement =nullptr;
	BoxCollider* m_pCollisionBox = nullptr;

	virtual void Update(float time) override;
};

