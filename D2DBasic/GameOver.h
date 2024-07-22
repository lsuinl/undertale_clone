#pragma once
#include "World.h"
class GameOver :public World
{
public:
	GameOver();
	~GameOver();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
};

