#pragma once
#include "World.h"
#include "Text.h"
class GameOver :public World
{
	float time = 48.5f;
	Text text;
public:
	GameOver();
	~GameOver();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
};

