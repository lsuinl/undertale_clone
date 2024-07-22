#pragma once
#include "../D2DBasic/GameObject.h";
#include "../D2DBasic/AnimationScene.h"
class AnimationScene;
class Character :
	public GameObject
{
public:
	Character();
	virtual ~Character();

	AnimationScene* m_pAnimationScene = nullptr;
	//CollisionBox* m_pCollisionBox = nullptr;
};

