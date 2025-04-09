#include "Monster.h"
#include "D2DEngine.h"
#include "BattleUI.h"

Monster::Monster()
{
	AnimationScene* m_pAnimationScene = CreateComponent<AnimationScene>();
	//Movemont
	m_pMovement = CreateComponent<Movement>();
	m_pMovement->SetSceneComponent(m_pAnimationScene);
	m_pMovement->SetSpeed(0.5f);
	m_pCollisionBox = CreateComponent<BoxCollider>();
	m_pCollisionBox->SetParent(m_pAnimationScene);
	m_pCollisionBox->SetCollisionType(CollisionType::Overlap);
	m_pCollisionBox->notify = notify;
	SetRootScene(m_pAnimationScene);
}

Monster::~Monster()
{

}

void Monster::Update(float time) 
{
	__super::Update(time);
	float yMovement,xMovement;
	MathHelper::Vector2F Location;
	switch (BattleUI::Level)
	{
	case 1:
		m_pMovement->SetDirectionNormalize({ 1, 0 });
		m_pMovement->SetSpeed(170.f);
		times += time;
		Location = m_pRootScene->GetRelativeLocation();
		yMovement = 0.5f * std::sin(5.0f * times);
		Location.y += yMovement;
		m_pMovement->GetSceneComponent()->SetRelativeLocation(Location);
		break;
	case 2:
		m_pRootScene->AddRelativeRotation(0.2f);
		m_pMovement->SetDirectionNormalize({ 0, 1 });
		m_pMovement->SetSpeed(140.f);
		m_pCollisionBox->exSize = true;
		break;
	case 3:
		m_pMovement->SetDirectionNormalize({ -1, 0 });
		m_pMovement->SetSpeed(100.f);
		break;
	case 4:
		m_pMovement->SetSpeed(190.f);
		if (m_pRootScene->GetRelativeRotation() == 0) //위로 올라가기
		{ 
			m_pMovement->SetDirectionNormalize({ 0, -1 });
		}
		else if (m_pRootScene->GetRelativeRotation() == 90) //오른쪽으로
		{
			m_pMovement->SetDirectionNormalize({ 1, 0 });
		}
		else if (m_pRootScene->GetRelativeRotation() == 180)//아래로
		{
			m_pMovement->SetDirectionNormalize({ 0, 1 });
		}
		else if (m_pRootScene->GetRelativeRotation() == 270) //왼쪽으로
		{
			m_pMovement->SetDirectionNormalize({ -1, 0 });
		}
		times = 0; //5스테이지 가기 전에 셋팅.
		break; 
	case 5:
		m_pMovement->SetDirectionNormalize({ 0, -1 });
		m_pMovement->SetSpeed(130.f);
		times += time;
		Location = m_pRootScene->GetRelativeLocation();
		xMovement = 1.0f * std::sin(2.0f * times);
		Location.x += xMovement;
		m_pMovement->GetSceneComponent()->SetRelativeLocation(Location);
		break;
	default:
		break;
	}
}

void Monster::Render(D2DEngine* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
