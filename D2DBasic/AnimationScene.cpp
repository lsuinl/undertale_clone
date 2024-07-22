#include "pch.h"
#include "AnimationScene.h"
#include "AnimationAsset.h"
#include "D2DEngine.h"
#include "ResourceManager.h"


AnimationScene::AnimationScene()
{
	m_pAnimationAsset = new AnimationAsset();
}

AnimationScene::~AnimationScene()
{
	// 리소스매니저를 통하여 에셋이름으로 해제한다.
	if (m_pAnimationAsset)
	{
		ResourceManager::pInstance->ReleaseAnimationAsset(m_strAnimationAssetFilePath);
		m_pAnimationAsset = nullptr;
	}
}

void AnimationScene::SetMirror(bool mirror)
{
	m_bMirror = mirror;
}

void AnimationScene::LoadAnimationAsset(const std::wstring strFilePath, const std::wstring strCsvPath)
{
	// 리소스 매니저를 통해 AnimationAsset을 로드한다.
	ResourceManager::pInstance->CreateAnimationAsset(strFilePath, &m_pAnimationAsset);
	m_pAnimationAsset->LoadAnimation(strCsvPath);
	m_strAnimationAssetFilePath = strFilePath;
}

void AnimationScene::Update(float fTimeElapsed)
{
	BitmapScene::Update(fTimeElapsed);
	assert(m_pAnimationAsset != nullptr);  // asset이 없으면 debug모드에서 멈춤
	if (m_pAnimationInfo == nullptr)
		return;
	isAniEnd = false;
	const FRAME_INFO& Frame = m_pAnimationInfo->Frames[m_FrameIndexCurr];
	size_t MaxFrameCount = m_pAnimationInfo->Frames.size();

	m_FrameTime += fTimeElapsed;
	if (m_FrameTime > Frame.Duration) {
		m_FrameTime = 0;
		m_FrameIndexCurr++;
		if (m_pAnimationInfo->Frames.size() - 1 == m_FrameIndexCurr) {
			m_FrameIndexCurr = 0;
			isAniEnd = true;
		}
	}

	m_SrcRect = Frame.Source;
	m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };

	if (m_bMirror) //x 축 스케일은 좌우 반전 , Translation 은 출력할 이미지의 원점 정보
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation((m_DstRect.right - m_DstRect.left), 0);
			//D2D1::Matrix3x2F::Translation((m_DstRect.right - m_DstRect.left) * Frame.Center.x, Frame.Center.y);
	}
	else
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(Frame.Center.x * -1, Frame.Center.y);
	}
}

void AnimationScene::Render(D2DEngine* pRenderTarget)
{
	if (m_pAnimationInfo == nullptr)
		return;
	D2D1_MATRIX_3X2_F Transform = m_ImageTransform 
		* m_WorldTransform 
		* D2DEngine::m_CameraTransform;
	float x = m_pAnimationInfo->Frames[m_FrameIndexCurr].Center.x;
	float y = m_pAnimationInfo->Frames[m_FrameIndexCurr].Center.y;
	UpdateTrasnform();
	pRenderTarget->GetRenderTarget()->SetTransform(Transform);
	pRenderTarget->GetRenderTarget()->DrawBitmap(m_pBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_pAnimationInfo->Frames[m_FrameIndexCurr].Source);
}

void AnimationScene::SetAnimation(int index, bool mirror)
{
	assert(m_pAnimationAsset != nullptr);

	ANIMATION_INFO* pFound = m_pAnimationAsset->GetAnimationInfo(index);
	if (pFound == nullptr)
		return;
	m_pAnimationInfo = pFound;
	m_bMirror = mirror;
	m_FrameIndexCurr = 0;
	m_FrameIndexPrev = 0;
	m_FrameTime = 0.0f;
}
