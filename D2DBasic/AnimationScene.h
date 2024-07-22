#pragma once
#include "BitmapScene.h"
#include "AnimationAsset.h"
#include "Component.h"

struct ANIMATION_INFO;


// 애니메이션 인스턴스 정보
class AnimationScene :public BitmapScene, public Component
{
public:
	AnimationScene();
	virtual ~AnimationScene();

	// 공유하는 애니메이션 정보	
	AnimationAsset* m_pAnimationAsset = nullptr;  // 공유하는 애니메이션 정보
	// 인스턴스마다 다른 애니메이션 정보
	ANIMATION_INFO* m_pAnimationInfo = nullptr;	// 현재 애니메이션 프레임 정보
	std::wstring m_strAnimationAssetFilePath;    // 애니메이션 정보 파일 이름
	float m_FrameTime = 0.0f;	// 프레임 진행시간
	int m_FrameIndexCurr = -1;		// 현재 프레임 인덱스
	int m_FrameIndexPrev = -1;		// 이전 프레임 인덱스
	int m_AnimationIndex = -1;	// 현재 애니메이션 인덱스
	D2D1_RECT_F m_SrcRect;		// D2D1Bitmap의 Source 영역
	D2D1_RECT_F m_DstRect;		// RenderTarget의 Destination 영역	
	bool isAniEnd=false;

	bool m_bMirror;				// 좌우 반전 여부
	D2D1_MATRIX_3X2_F	m_ImageTransform;	// 반대 방향으로 뒤집기 위한 행렬 Scale.x = -1.0f 
	bool isEnd() {return isAniEnd;}
	void SetMirror(bool mirror );
	void LoadAnimationAsset(const std::wstring strFilePath, const std::wstring strPath);
	virtual void Update(float fTimeElapsed) override;
	virtual void Render(D2DEngine* pRenderTarget) override;
	void SetAnimation(int index, bool mirror);
};

