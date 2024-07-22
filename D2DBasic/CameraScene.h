#pragma once
#include "Scene.h"
#include "AABB.h"
#include "Component.h"

class CameraScene :
	public Scene, public Component
{
	float deltaTime;
public:
	CameraScene();
	CameraScene(float _width, float _height);
	virtual ~CameraScene();

	AABB m_ViewBoundBox;

	virtual void Update(float deltaTime);
};

