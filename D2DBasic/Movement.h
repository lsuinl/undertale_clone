#pragma once
#include "Component.h"
#include "MathHelper.h"

class Scene;
class Movement :
	public Component
{
public:
	Movement() = default;
	virtual ~Movement() = default;
protected:
	float			m_Speed = 0.0f;		// 1�ʴ� �̵��� �ӷ�
	MathHelper::Vector2F	m_Direction{ 0.0f,0.0f };	// ���� ���ֺ���
	MathHelper::Vector2F	m_Velocity;		// �ӵ� ����
	Scene* m_pSceneComponent; // ��ġ�� ������ ������Ʈ
	float distance;
	bool isBlock = false;
	MathHelper::Vector2F preLocation;
public:
	virtual void Update(float deltaTime);
	void SetBlock() { isBlock = true; }
	void SetSceneComponent(Scene* val) { m_pSceneComponent = val; }
	void SetSpeed(float speed) { m_Speed = speed; };
	float GetSpeed() { return m_Speed; };
	void SetDistance(const MathHelper::Vector2F& Direction);
	float GetDistance() { return distance; };
	virtual void SetDirection(const MathHelper::Vector2F& Direction);
	void SetDirectionNormalize(const MathHelper::Vector2F& Direction);
	const MathHelper::Vector2F& GetDirection() { return m_Direction; };
};

