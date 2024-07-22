#pragma once
#include "World.h"
class Battle :public World
{
public:
	int Level = 0; //������
	float PlayTime = 0, ClearTime = 5.0f; //����� ��ƾ �ð� (n�� �̻� ��Ƽ�� ������ ����.)
	float monsterTime = 0, CreateTime = 0.3; //���� ���� ���� �ֱ�
	AABB m_CullingBoundDefault;//�̴� ����
	std::vector <Monster*> Monsters; //����

	Battle();
	~Battle();
	virtual void Update(float deltaTime);
	virtual void Render(D2DEngine* pRenderTarget);
	void CreateMonster(std::vector<Monster*> Player, Character* player, AnimationScene* ani);
};

