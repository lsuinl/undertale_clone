#pragma once
#include "BitmapScene.h"
#include "AnimationAsset.h"
#include "Component.h"

struct ANIMATION_INFO;


// �ִϸ��̼� �ν��Ͻ� ����
class AnimationScene :public BitmapScene, public Component
{
public:
	AnimationScene();
	virtual ~AnimationScene();

	// �����ϴ� �ִϸ��̼� ����	
	AnimationAsset* m_pAnimationAsset = nullptr;  // �����ϴ� �ִϸ��̼� ����
	// �ν��Ͻ����� �ٸ� �ִϸ��̼� ����
	ANIMATION_INFO* m_pAnimationInfo = nullptr;	// ���� �ִϸ��̼� ������ ����
	std::wstring m_strAnimationAssetFilePath;    // �ִϸ��̼� ���� ���� �̸�
	float m_FrameTime = 0.0f;	// ������ ����ð�
	int m_FrameIndexCurr = -1;		// ���� ������ �ε���
	int m_FrameIndexPrev = -1;		// ���� ������ �ε���
	int m_AnimationIndex = -1;	// ���� �ִϸ��̼� �ε���
	D2D1_RECT_F m_SrcRect;		// D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect;		// RenderTarget�� Destination ����	
	bool isAniEnd=false;

	bool m_bMirror;				// �¿� ���� ����
	D2D1_MATRIX_3X2_F	m_ImageTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f 
	bool isEnd() {return isAniEnd;}
	void SetMirror(bool mirror );
	void LoadAnimationAsset(const std::wstring strFilePath, const std::wstring strPath);
	virtual void Update(float fTimeElapsed) override;
	virtual void Render(D2DEngine* pRenderTarget) override;
	void SetAnimation(int index, bool mirror);
};

