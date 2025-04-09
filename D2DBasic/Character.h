#pragma once
#include "GameObject.h"
#include "Movement.h"
#include "CameraScene.h"
#include "BoxCollider.h"
#include "FiniteStateMachine.h"
#include "CharacterHandler.h"
class AnimationScene;
class Character :public GameObject
{
public:
	bool death = false;
	static int HP;
	Character();
	virtual ~Character();

	BitmapScene* hp = new BitmapScene();
	BitmapScene* hpback = new BitmapScene();

	CameraScene* Camera;
	FiniteStateMachine* FSMS;
	BoxCollider* m_pCollisionBox = nullptr;
	Movement* m_pMovement = nullptr;
	CharacterHandler* notify= new CharacterHandler(this);
	void Damage(int n);
	virtual void Update(float time) override;
	virtual void Render(D2DEngine* pRenderTarget) override;
};
