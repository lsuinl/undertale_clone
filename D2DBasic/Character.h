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

	Character();
	virtual ~Character();
	int HP=40;
	CameraScene* Camera;
	FiniteStateMachine* FSMS;
	BoxCollider* m_pCollisionBox = nullptr;
	Movement* m_pMovement = nullptr;
	CharacterHandler* notify= new CharacterHandler(this);
	int GetHP() { return HP; }
	void Damage(int n);
	virtual void Update(float time) override;
	virtual void Render(D2DEngine* pRenderTarget) override;
};
