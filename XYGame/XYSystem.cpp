#include "XYSystem.h"
#include "util.h"
#include "SoundManager.h"

XYSystem::XYSystem() {}
XYSystem::~XYSystem() {}

void XYSystem::Initialize(HINSTANCE hInstance)
{
	__super::Initialize(hInstance);
	ScreenManager::pInstanc->CreateWorld<Story>();

	//ScreenManager::pInstanc->CreateWorld<Battle>();
	//ScreenManager::pInstanc->CreateWorld<GameOver>();
	//ScreenManager::pInstanc->CreateWorld<Ending>();
	ScreenManager::pInstanc->LoadWorld(0);
}
void XYSystem::Update(float times)
{
	ScreenManager::pInstanc->curWorld->Update(times);
}

void XYSystem::Finalize()
{
	__super::Finalize();
}

void XYSystem::Render()
{
	m_pRenderer->BeginDraw();
	ScreenManager::pInstanc->curWorld->Render(m_pRenderer);
	m_pRenderer->EndDraw();
}

