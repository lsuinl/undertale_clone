#include "HeroIdle.h"

void HeroIdle::Enter()
{
	AnimationScene* ani = dynamic_cast<AnimationScene*>(GetOwner()->GetOwner()->m_pRootScene);
	curForward = getForward();
	if (curForward == 1)
		ani->SetAnimation(13, false); //뒤
	else if (curForward == 2)
		ani->SetAnimation(11, false);//앞
	else if (curForward == 3)
		ani->SetAnimation(12, false);//왼쪽
	else  if (curForward == 4)
		ani->SetAnimation(12, true);//오른쪽
}

void HeroIdle::Update(float DeltaTime)
{
	int forward = getForward();
	if (forward != curForward) {
		AnimationScene* ani = dynamic_cast<AnimationScene*>(GetOwner()->GetOwner()->m_pRootScene);
		if (forward == 1)
			ani->SetAnimation(13, false); //뒤
		else if (forward == 2)
			ani->SetAnimation(11, false);//앞
		else if (forward == 3)
			ani->SetAnimation(12, false);//왼쪽
		else  if (forward == 4)
			ani->SetAnimation(12, true);//오른쪽
	}
	curForward = forward;
}

void HeroIdle::Exit()
{
}
