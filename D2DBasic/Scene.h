#pragma once
#include <d2d1.h>
#include <d2d1_1.h>
#include "Component.h"
//이미지를 그리기 위한 장면 scene

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	Scene* m_pParentScene = nullptr;		// 부모 Scene 컴포넌트	
	D2D_VECTOR_2F		m_RelativeScale = { 1,1 };	// 상대 크기
	float				m_RelativeRotation = 0; // 상대 회전
	D2D_VECTOR_2F 		m_RelativeLocation = { 0,0 }; // 상대 위치
	D2D_MATRIX_3X2_F	m_RelativeTransform; // 상대 복합 변환
	D2D_MATRIX_3X2_F	m_WorldTransform;    // 부모까지 반영된 최종 변환
	D2D_VECTOR_2F m_preLocation;
	D2D1_POINT_2F m_center = { 0,0 };
	D2D1_POINT_2F m_size;
	// RelativeTransform과 	m_WorldTransform을 계산한다.
	void UpdateTrasnform();
	void SetParent(Scene* pParentScene) { m_pParentScene = pParentScene; }
	D2D1_VECTOR_2F GetWorldLocation();

	//추가
	virtual void Update(float deltaTime);
	void DrawDebugScene(ID2D1RenderTarget* pRenderTarget);

	void SetRelativeRotation(float Rotation);
	void AddRelativeRotation(float Rotation);
	float GetRelativeRotation() { return m_RelativeRotation; }
	void SetVis() { if (m_RelativeScale.x = 0) m_RelativeScale = { 1,1 }; else m_RelativeScale = { 0,0 }; }

	void SetRelativeLocation(const D2D1_VECTOR_2F& Location);
	void AddRelativeLocation(float x, float y);
	const D2D1_VECTOR_2F& GetRelativeLocation() { return m_RelativeLocation; }

};

