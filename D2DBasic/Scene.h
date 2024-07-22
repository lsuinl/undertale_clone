#pragma once
#include <d2d1.h>
#include <d2d1_1.h>
#include "Component.h"
//�̹����� �׸��� ���� ��� scene

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	Scene* m_pParentScene = nullptr;		// �θ� Scene ������Ʈ	
	D2D_VECTOR_2F		m_RelativeScale = { 1,1 };	// ��� ũ��
	float				m_RelativeRotation = 0; // ��� ȸ��
	D2D_VECTOR_2F 		m_RelativeLocation = { 0,0 }; // ��� ��ġ
	D2D_MATRIX_3X2_F	m_RelativeTransform; // ��� ���� ��ȯ
	D2D_MATRIX_3X2_F	m_WorldTransform;    // �θ���� �ݿ��� ���� ��ȯ
	D2D_VECTOR_2F m_preLocation;
	D2D1_POINT_2F m_center = { 0,0 };
	D2D1_POINT_2F m_size;
	// RelativeTransform�� 	m_WorldTransform�� ����Ѵ�.
	void UpdateTrasnform();
	void SetParent(Scene* pParentScene) { m_pParentScene = pParentScene; }
	D2D1_VECTOR_2F GetWorldLocation();

	//�߰�
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

