#pragma once
#include <Windows.h>
#include "D2DEngine.h"

class World;
class D2DEngine;
class ResourceManager;
class ScreenManager;

class D2DBasic
{
private:
	HINSTANCE       g_hInst;   //현재 인스턴스               
	HWND            g_hWnd;   //윈도우 핸들
	HINSTANCE m_hInstance = { 0 };  
	HWND m_hWnd = { 0 };			

	int width = 1920;
	int height =1080;
	int timer = 0;
public:
	D2DBasic();
	~D2DBasic();
	void Run();
	virtual void Initialize(HINSTANCE hInstance);
	virtual void Finalize();
	virtual void Render();
	virtual void Update(float times);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	D2DEngine* m_pRenderer = nullptr;
	ResourceManager* m_pResourceManager = nullptr;
	ScreenManager* m_pScreenManager = nullptr;

};
