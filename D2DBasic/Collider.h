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
//		// �浹�� �� ��ü�� �߽� ��ġ�� ������ �Ǵ� ũ�� ������ �����ɴϴ�.
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
//		// �浹�� �� ��ü�� �ݴ� �������� �о���ϴ�.
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
	CollisionType m_CollisionType;		// �ø��� Ÿ�� (���ø���,��, ������)
	ColliderType m_ColliderType;		// �ö��̴� Ÿ�� (��,�ڽ�)
	D2D1_COLOR_F m_Color;				// �׸���� ����
	std::set<Collider*> m_CollideStateCurr;    // ���� �浹 ����
	std::set<Collider*> m_CollideStatePrev;	// ���� �浹 ����
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

	// Circle,Box ���� ���� �����ؾ��Ѵ�.
	virtual bool IsCollide(Collider* pOtherComponent) = 0;
};


