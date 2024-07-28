#pragma once
#include "Collider.h"
#include "Component.h"
#include "AABB.h"
#include "GameObject.h"
#include "Movement.h"
#include <cmath>

class BoxCollider : public Collider, public Component
{
	public:
		bool exSize; //����ڼ����ڽ�ũ��
		AABB m_Collider;
		bool isColli=false;
		D2D_RECT_F m_Rect;
		BoxCollider() {
			 m_ColliderType=ColliderType::Box;// �ö��̴� Ÿ�� (��,�ڽ�)
			 m_Color= D2D1::ColorF(D2D1::ColorF::White);// �׸���� ����
		};
		~BoxCollider() = default;
		virtual void Update(float deltaTime);
		virtual void Render(D2DEngine* pRenderTarget);
		virtual bool IsCollide(Collider* pOtherComponent);

		virtual void InsertCollideState(Collider* pColliderComponent) { m_CollideStateCurr.insert(pColliderComponent); }
		virtual void ProcessOverlap();
		virtual void ProcessBlock(Collider* pOtherComponent);
	
};
