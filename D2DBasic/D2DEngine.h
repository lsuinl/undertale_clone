#pragma once
#include <d2d1.h>
#include "pch.h"
#pragma comment(lib, "dwrite.lib") //..
#pragma comment(lib, "dxgi.lib")

class D2DEngine
{
public:
	D2DEngine();
	~D2DEngine();

	static D2D1_MATRIX_3X2_F m_CameraTransform;		// 카메라의 좌표계로 변환하는 카메라 월드의 역행렬

	void InitDirect2D(HWND hWnd);
	void UninitDirect2D();
	void BeginDraw();
	void EndDraw();
	void DrawSquare(int left, int right, int top, int bottom);
	HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** bitmap);
	ID2D1Factory* GetFactory() { return m_pD2DFactory; }
	ID2D1HwndRenderTarget* GetRenderTarget() { return m_pRenderTarget; }
	size_t GetUsedVRAM();
	void DrawTexts(const wchar_t* text, float left, float top);
	void DrawTextsize(const wchar_t* text, float left, float right,float top, float bottom);
	void DrawTextChat(const wchar_t* text, float left, float right,float top, float bottom);
private:
	ID2D1Factory* m_pD2DFactory;		// D2D 개체 인터페이스 포인터 변수
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IWICImagingFactory* m_pWICFactory;	// D2D비트맵 생성을 위한 이미지 처리 인터페이스
	IDWriteFactory* m_pDWriteFactory;	// TextFormat생성을 위한 팩토리
	IDWriteTextFormat* m_pDWriteTextFormat; // 기본 텍스트 출력을 위한 Format
	IDWriteTextFormat* m_pDWriteTextFormats; // 기본 텍스트 출력을 위한 Format
	ID2D1SolidColorBrush* m_pBrush;	// 렌더타겟이 생성하는 리소스 역시 장치의존
	ID2D1SolidColorBrush* m_pBlackBrush;	// 렌더타겟이 생성하는 리소스 역시 장치의존
	IDXGIFactory4* m_pDXGIFactory;		// DXGI팩토리
	IDXGIAdapter3* m_pDXGIAdapter;		// 비디오카드 정보에 접근 가능한 인터페이스
	HWND m_hWnd;						// 렌더타겟을 생성할 윈도우 핸들
	D2D_SIZE_U	m_ClientSize;			// 렌더타겟의 크기
};