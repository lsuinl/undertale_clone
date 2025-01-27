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


class Collider;
class IColliderNotify
{
public:
	virtual void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) =0;
	virtual void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) =0;
	virtual void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) =0;
};


class Collider :
	public RenderScene
{
public:
	Collider() = default;
	virtual ~Collider() = default;

protected:
	CollisionType m_CollisionType;		// 컬리전 타입 (노컬리전,블럭, 오버랩)
	ColliderType m_ColliderType;		// 컬라이더 타입 (원,박스)
	D2D1_COLOR_F m_Color;				// 그리기용 색상
	std::set<Collider*> m_CollideStateCurr;    // 현재 충돌 상태
	std::set<Collider*> m_CollideStatePrev;	// 이전 충돌 상태
public:
	IColliderNotify* notify;
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


