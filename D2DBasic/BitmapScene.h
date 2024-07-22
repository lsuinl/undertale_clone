#pragma once
#include "Scene.h"
#include <string>

class D2DEngine;
class BitmapScene :
	public Scene
{
public:
	D2D1_RECT_F sourceRect;
	D2D1_RECT_F destinationRect;
	BitmapScene();
	virtual ~BitmapScene();

	bool Load(const std::wstring& strFileName);
	
	std::wstring m_strFileName;
	ID2D1Bitmap* m_pBitmap = nullptr;

	void Update(float fTimeElapsed);
	void Render(D2DEngine* pRenderTarget);
};




