#pragma once
#include "World.h"
class snowMap :public World
{
public:
	snowMap();
	~snowMap();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
};

