#pragma once
#include "World.h"
#include "Text.h"
class Battle :public World
{
public:
	Text text;
	int Level = 0; //������
	float PlayTime = 0, ClearTime = 5.0f; //����� ��ƾ �ð� (n�� �̻� ��Ƽ�� ������ ����.)
	float monsterTime = 0, CreateTime = 0.3; //���� ���� ���� �ֱ�
	AABB m_CullingBoundDefault;//�̴� ����
	Character* Player; //�÷��̾�
	std::vector <Monster*> Monsters; //����
	BitmapScene* chat = nullptr;
	Battle();
	~Battle();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
	void CreateMonster(std::vector<Monster*> Player, Character* player, AnimationScene* ani);
	void CreatePlayer(Character* Player, AnimationScene* ani);
};

