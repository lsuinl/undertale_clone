#pragma once
#include "World.h"
#include "Text.h"

class Story:public World
{
public:
	Text intro;
	AnimationScene* background;
	Story();
	~Story();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
};

