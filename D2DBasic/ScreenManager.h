#pragma once
#include "pch.h"
#include "World.h"
class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();
	static ScreenManager* pInstanc;
	World* curWorld;
	//std::vector<World*> worlds; //��� ������Ʈ ����
	
	template<typename T>
	T* CreateWorld()	// ���ø� �Լ��� World�� ����
	{
		bool bIsBase = std::is_base_of<World, T>::value;
		T* newWorld = new T();
		//worlds.push_back(newWorld);
		curWorld = newWorld;
		return newWorld;
	}
};

