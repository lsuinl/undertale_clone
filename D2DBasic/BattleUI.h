#pragma once
#include "World.h"
#include "Text.h"
class BattleUI :public World
{
	bool battleStart = false;
	Text text;
public:
	static int Level;
	int state = 1; //버튼 위치.
	float inputTime = 1.0f;
	AnimationScene* focus;
	BattleUI();
	~BattleUI();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
	void CreatePlayer(AnimationScene* ani);
	void addBack(std::wstring filename, D2D1_RECT_F des, D2D1_RECT_F sou);
};

