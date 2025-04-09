#pragma once
#include "World.h"
#include "Text.h"

class Battle :public World
{
	Text text;
	bool goending=false;
	float PlayTime = 0, ClearTime = 10.0f; //����� ��ƾ �ð� (n�� �̻� ��Ƽ�� ������ ����.)
	float monsterTime = 0, CreateTime = 0.3; //���� ���� ���� �ֱ�
	AABB m_CullingBoundDefault;//�̴� ����
	Character* Player; //�÷��̾�
	BitmapScene* chat = nullptr;
	std::vector <Monster*> Monsters; //����
public:
	Battle();
	~Battle();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
	void CreateMonster(std::vector<Monster*> Player, Character* player, AnimationScene* ani);
	void CreatePlayer(Character* Player, AnimationScene* ani);
};

