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
	//std::vector<World*> worlds; //모든 오브젝트 관리
	
	template<typename T>
	T* CreateWorld()	// 템플릿 함수로 World를 생성
	{
		bool bIsBase = std::is_base_of<World, T>::value;
		T* newWorld = new T();
		//worlds.push_back(newWorld);
		curWorld = newWorld;
		return newWorld;
	}
};

