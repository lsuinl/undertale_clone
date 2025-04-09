#pragma once
#include "NPC.h"
#include "Text.h"
class Kid :public NPC
{
	bool battle=false;
	AnimationScene* battleStart;
public:
	Kid();
	~Kid() {};
	virtual void Update(float time) override;
	virtual void Render(D2DEngine* pRenderTarget) override;
};

