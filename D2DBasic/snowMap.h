#pragma once
#include "World.h"
#include "Hero.h"
class snowMap :public World
{
public:
	Hero* Player;
	snowMap();
	~snowMap();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
};

