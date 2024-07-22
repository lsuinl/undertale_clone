#pragma once
#include "RenderScene.h"
#include <set>

enum class ColliderType
{
	None,
	Circle,
	Box
};

enum class CollisionType
{
	NoCollision,
	Block,
	Overlap
};


//class Collider;
//class IColliderNotify
//{
//public:
//	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) {
//		// 충돌한 두 객체의 중심 위치와 반지름 또는 크기 정보를 가져옵니다.
//		float ownedRadius = 0.0f, otherRadius = 0.0f;
//
//		float dx = pOwnedComponent->m_RelativeLocation.x - pOtherComponent->m_RelativeLocation.x;
//		float dy = pOwnedComponent->m_RelativeLocation.y - pOtherComponent->m_RelativeLocation.y;
//
//		float distance = sqrt(dx * dx + dy * dy);
//
//		ownedRadius = pOwnedComponent->m_size.x;
//
//
//		otherRadius = pOtherComponent->m_size.x;
//
//		float overlap = ownedRadius + otherRadius - distance;
//
//		// 충돌한 두 객체를 반대 방향으로 밀어냅니다.
//		if (overlap > 0.0f)
//		{
//			float adjustmentX = (dx / distance) * overlap / 2.0f;
//			float adjustmentY = (dy / distance) * overlap / 2.0f;
//			pOwnedComponent->SetRelativeLocation({ pOwnedComponent->m_RelativeLocation.x + adjustmentX,
//				pOwnedComponent->m_RelativeLocation.y + adjustmentY });
//			pOtherComponent->SetRelativeLocation({ pOtherComponent->m_RelativeLocation.x - adjustmentX,
//				pOtherComponent->m_RelativeLocation.y - adjustmentY });
//		}
//	};
//	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) {
//
//	};
//	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) {
//
//	};
//};


class Collider :
	public RenderScene
{
public:
	Collider() = default;
	virtual ~Collider() = default;

protected:
	//IColliderNotify notify;
	CollisionType m_CollisionType;		// 컬리전 타입 (노컬리전,블럭, 오버랩)
	ColliderType m_ColliderType;		// 컬라이더 타입 (원,박스)
	D2D1_COLOR_F m_Color;				// 그리기용 색상
	std::set<Collider*> m_CollideStateCurr;    // 현재 충돌 상태
	std::set<Collider*> m_CollideStatePrev;	// 이전 충돌 상태
public:

	CollisionType GetCollisionType() { return m_CollisionType; }
	void SetCollisionType(CollisionType Type) { m_CollisionType = Type; }
	ColliderType GetColliderType() { return m_ColliderType; }

	D2D1_COLOR_F GetColor() const { return m_Color; }
	void SetColor(D2D1_COLOR_F val) { m_Color = val; }
	void ClearAndBackupCollideState();

	bool IsEmptyCollideStateCurr() { return m_CollideStateCurr.empty(); }

	virtual void InsertCollideState(Collider* pColliderComponent) { m_CollideStateCurr.insert(pColliderComponent); }
	virtual void ProcessOverlap() {};
	virtual void ProcessBlock(Collider* pOtherComponent) {};

	// Circle,Box 에서 각자 구현해야한다.
	virtual bool IsCollide(Collider* pOtherComponent) = 0;
};


