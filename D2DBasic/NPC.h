#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
#include "NPCHandler.h"
#include "Text.h"
class NPC:public GameObject
{
	Text text;
public:
	float inputTime = 0.1f;
	bool talkable = false, isTalk=false;
	BitmapScene* chat=nullptr;
	NPC();
	~NPC();
	NPCHandler* notify = new NPCHandler(this);
	BoxCollider* m_pCollisionBox = nullptr;
	BoxCollider* m_pChatCollisionBox = nullptr;
	virtual void Update(float time) override;
	virtual void Render(D2DEngine* pRenderTarget) override;
};

