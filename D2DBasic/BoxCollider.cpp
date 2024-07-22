#include "BoxCollider.h"
#include "Character.h"

void BoxCollider::Render(D2DEngine* d2d)
{
	if (false) {
		ID2D1SolidColorBrush* m_pBrush;
		d2d->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
		d2d->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::AliceBlue), &m_pBrush);
		d2d->GetRenderTarget()->DrawRectangle(
			D2D1::RectF(m_Collider.GetMinX(), m_Collider.GetMinY(), m_Collider.GetMaxX(), m_Collider.GetMaxY()), m_pBrush);
	}
}

void BoxCollider::Update(float deltaTime)
{
	m_size = m_pParentScene->m_size;
	m_center = { m_pParentScene->m_RelativeLocation.x , m_pParentScene->m_RelativeLocation.y };
	m_Collider.SetCenter(m_center.x+ m_size.x/2, m_center.y+ m_size.y /2);
	m_Collider.SetExtent(m_size.x / 2, m_size.y / 2);
}

bool BoxCollider::IsCollide(Collider* pOtherComponent)
{
	if (pOtherComponent->GetColliderType() == ColliderType::Circle) {
	}
	else if (pOtherComponent->GetColliderType() == ColliderType::Box) {
		BoxCollider* otherBox = dynamic_cast<BoxCollider*>(pOtherComponent);
		return m_Collider.CheckIntersect(otherBox->m_Collider);
	}
		
	return false;
}

void BoxCollider::ProcessOverlap()
{
	for (auto& collider : m_CollideStateCurr)
	{
		if (m_CollideStatePrev.find(collider) == m_CollideStatePrev.end())
		{
			isColli = true;
			Character* characters = dynamic_cast<Character*>(m_pOwner);
			if (characters)
				characters->Damage(10);
		}
	}

	for (auto& collider : m_CollideStatePrev)
	{
		if (m_CollideStateCurr.find(collider) == m_CollideStateCurr.end())
		{
			isColli = false;
		}
	}
}

void BoxCollider::ProcessBlock(Collider* pOtherComponent)
{
	for (auto e : m_pOwner->m_OwnedComponents) {
		Movement* m = dynamic_cast<Movement*>(e);
		if (m) {
			m->SetBlock();
		}
	}
}


