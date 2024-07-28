#pragma once
#include "World.h"
class Title:public World
{
public:
	bool start = false;
	float PressTime = 0.f, limitTime = 3.0f;
	Title();
	~Title();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
};

