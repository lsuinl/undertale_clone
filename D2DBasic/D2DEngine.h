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

	static D2D1_MATRIX_3X2_F m_CameraTransform;		// ī�޶��� ��ǥ��� ��ȯ�ϴ� ī�޶� ������ �����

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
	ID2D1Factory* m_pD2DFactory;		// D2D ��ü �������̽� ������ ����
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IWICImagingFactory* m_pWICFactory;	// D2D��Ʈ�� ������ ���� �̹��� ó�� �������̽�
	IDWriteFactory* m_pDWriteFactory;	// TextFormat������ ���� ���丮
	IDWriteTextFormat* m_pDWriteTextFormat; // �⺻ �ؽ�Ʈ ����� ���� Format
	IDWriteTextFormat* m_pDWriteTextFormats; // �⺻ �ؽ�Ʈ ����� ���� Format
	ID2D1SolidColorBrush* m_pBrush;	// ����Ÿ���� �����ϴ� ���ҽ� ���� ��ġ����
	ID2D1SolidColorBrush* m_pBlackBrush;	// ����Ÿ���� �����ϴ� ���ҽ� ���� ��ġ����
	IDXGIFactory4* m_pDXGIFactory;		// DXGI���丮
	IDXGIAdapter3* m_pDXGIAdapter;		// ����ī�� ������ ���� ������ �������̽�
	HWND m_hWnd;						// ����Ÿ���� ������ ������ �ڵ�
	D2D_SIZE_U	m_ClientSize;			// ����Ÿ���� ũ��
};