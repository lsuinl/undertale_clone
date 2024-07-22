#include "pch.h"
#include "Movement.h"
#include "Scene.h"
#include "Helper.h"
#include "MathHelper.h"

// ���ӵ� ������� ������ �ӵ��� �̵��Ѵ�.
void Movement::Update(float DeltaTime)
{
	assert(m_pSceneComponent != nullptr);
		// ���� ��ġ�� �����´�.
		MathHelper::Vector2F Location = m_pSceneComponent->GetRelativeLocation();
		m_Velocity = m_Direction * m_Speed;
	if (!isBlock) {
		preLocation = Location;
		Location += m_Velocity * DeltaTime;
	}
	else {
		Location = preLocation;
		isBlock = false;
	}
	m_pSceneComponent->SetRelativeLocation(Location);
}

void Movement::SetDistance(const MathHelper::Vector2F& Direction)
{
	MathHelper::Vector2F Location = m_pSceneComponent->GetRelativeLocation();
	m_Direction = Direction - Location;
	distance = sqrt((m_Direction.x * m_Direction.x) + (m_Direction.y * m_Direction.y));
}

void Movement::SetDirection(const MathHelper::Vector2F& Direction)
{
	MathHelper::Vector2F Location = m_pSceneComponent->GetRelativeLocation();
	m_Direction =  Direction- Location;
	m_Direction.Normalize();
}

void Movement::SetDirectionNormalize(const MathHelper::Vector2F& Direction)
{
	m_Direction = Direction;
	m_Direction.Normalize();
}


