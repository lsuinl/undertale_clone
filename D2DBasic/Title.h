#pragma once
#include "World.h"
class Title:public World
{
public:
	bool isKey = false;
	float twinkTime = 0.f, twinkLimit = 1.0f;
	Title();
	~Title();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
};

