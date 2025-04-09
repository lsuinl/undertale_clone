#include "BitmapScene.h"
#include "pch.h"
#include "ResourceManager.h"
BitmapScene::BitmapScene()
{
}

BitmapScene::~BitmapScene()
{
	if (m_pBitmap!=nullptr)
	{
		//m_pBitmap->Release();
		m_pBitmap = nullptr;
	}
}
bool BitmapScene::Load(const std::wstring& strFileName)
{
	return true;
}

void BitmapScene::Update(float fTimeElapsed)
{
}

void BitmapScene::Render(D2DEngine* pRenderTarget)
{
	assert(m_pBitmap != nullptr);
	pRenderTarget->GetRenderTarget()->SetTransform(m_WorldTransform);
	pRenderTarget->GetRenderTarget()->DrawBitmap(
		m_pBitmap,
		destinationRect,
		1.0f, // 불투명도
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		sourceRect
	);
}

