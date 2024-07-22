#pragma once
#include "pch.h"
/*
	FSMState �߻�Ŭ����
	���̴� Transition Class�� ����ص��ǰ�
	CheckTransition �Լ��� ������(override) �ؼ� ����ص���
*/
class FSMTransition;
class FiniteStateMachine;
class FSMState
{
	int forward=1;
	std::string m_Name;
	FiniteStateMachine* m_pOwner = nullptr;
public:

	FSMState(FiniteStateMachine* pOwner, std::string Name)
		:m_pOwner(pOwner)
		, m_Name(Name)
	{

	}
	virtual ~FSMState()
	{

	}
	void setForward(int n) { forward = n; }
	int getForward() { return forward; }
	FiniteStateMachine* GetOwner() { return m_pOwner; }
	void SetOwner(FiniteStateMachine* pOwner) { m_pOwner = pOwner; }
	const std::string& GetName() { return m_Name; }

	virtual void Enter() = 0;	// ���� ������ ������ ����
	virtual void Update(float DeltaTime) = 0; // ���� �϶� ��� ������ ����, ���� ���� �˻� (Check Transition Condition) �� ���� �Ѵ�.
	virtual void Exit() = 0;	// ���� Ż�⶧ ������ ����
};