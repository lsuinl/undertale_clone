#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
#include "NPCHandler.h"
#include "Text.h"
class NPC:public GameObject
{
	float inputTime = 0.1f;
	BitmapScene* chat=nullptr;
protected:
	Text text;
	std::wstring file;
	const char* typesound = "../Resource/music/effect/overtexting.mp3";
public:
	bool talkable = false, isTalk=false;
	NPC();
	~NPC();
	void SetTextFile(std::wstring texts) { file = texts; }
	void SetTypeSound(const char* texts) { typesound = texts; }
	NPCHandler* notify = new NPCHandler(this);
	BoxCollider* m_pCollisionBox = nullptr;
	BoxCollider* m_pChatCollisionBox = nullptr;
	virtual void Update(float time) override;
	virtual void Render(D2DEngine* pRenderTarget) override;
};

