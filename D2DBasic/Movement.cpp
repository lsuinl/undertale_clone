#include "pch.h"
#include "Movement.h"
#include "Scene.h"
#include "Helper.h"
#include "MathHelper.h"

// 가속도 개념없이 일정한 속도로 이동한다.
void Movement::Update(float DeltaTime)
{
	assert(m_pSceneComponent != nullptr);
		// 현재 위치를 가져온다.
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


