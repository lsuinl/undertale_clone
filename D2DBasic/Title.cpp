#include "Title.h"
#include "ResourceManager.h"
#include "ScreenManager.h"

Title::Title()
{
	m_Background.push_back(new BitmapScene());		 
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/introduction.png", &m_Background.back()->m_pBitmap);
	m_Background.back()->destinationRect = D2D1::RectF(0, 0.f, 1080, 960.f);
	m_Background.back()->sourceRect = D2D1::RectF(10, 3140, 335, 3380);

	m_Background.push_back(new BitmapScene());//press anykey
	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"../Resource/ui/introduction.png", &m_Background.back()->m_pBitmap);
	m_Background.back()->destinationRect = D2D1::RectF(0, 0.f, 1080, 960.f);
	m_Background.back()->sourceRect = D2D1::RectF(10, 3140, 335, 3380);
}

Title::~Title()
{
}

void Title::Update(float deltaTime)
{
	__super::Update(deltaTime);
	if (!isKey) {
		//press any key
		twinkTime += deltaTime;
		if (twinkLimit < twinkTime) {
			twinkTime = 0;
			m_Background.back()->SetVis(); //반짝이기.
		}
	}
	else {
		//시작, 계속하기 버튼,+설정,,
		
	}
}

void Title::Render(D2DEngine* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
