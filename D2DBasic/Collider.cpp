#include "pch.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "GameObject.h"
void Collider::ClearAndBackupCollideState()
{
	m_CollideStatePrev = m_CollideStateCurr;
	m_CollideStateCurr.clear();
}

