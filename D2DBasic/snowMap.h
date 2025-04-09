#pragma once
#include "World.h"
#include "Hero.h"
#include "NPC.h"
#include "Kid.h"
class snowMap :public World
{
public:
	Hero* Player;
	snowMap();
	~snowMap();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
	void CreateNPC(std::wstring text, std::wstring csv, std::wstring png, D2D_VECTOR_2F scale, D2D_VECTOR_2F center, D2D1_POINT_2F size, D2D_VECTOR_2F xy, int index, const char* file = nullptr);
};
