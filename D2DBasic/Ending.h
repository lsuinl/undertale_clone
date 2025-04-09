#pragma once
#include "World.h"

class Ending :public World
{
public:
	float engingTime = -3.0f;
	Ending();
	~Ending();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
};

