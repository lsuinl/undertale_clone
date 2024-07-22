#pragma once
#include "World.h"
class Battle :public World
{
public:
	int Level = 0; //페이즈
	float PlayTime = 0, ClearTime = 5.0f; //페이즈별 버틴 시간 (n초 이상 버티면 페이즈 종료.)
	float monsterTime = 0, CreateTime = 0.3; //공격 패턴 생성 주기
	AABB m_CullingBoundDefault;//미니 월드
	std::vector <Monster*> Monsters; //공격

	Battle();
	~Battle();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
	void CreateMonster(std::vector<Monster*> Player, Character* player, AnimationScene* ani);
};

