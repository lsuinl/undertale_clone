#pragma once
#include "World.h"

class Ending :public World
{
public:
	Ending();
	~Ending();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
};

