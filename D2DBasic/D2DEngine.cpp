#include "pch.h"
#include "D2DEngine.h"
#include "BitmapScene.h"
#include "Helper.h"
#pragma comment(lib, "d2d1.lib")


	D2DEngine::D2DEngine()
	{

	}

	D2DEngine::~D2DEngine()
	{

	}

	D2D1_MATRIX_3X2_F D2DEngine::m_CameraTransform = D2D1::Matrix3x2F::Identity();

	void D2DEngine::InitDirect2D(HWND hWnd)
	{
		HRESULT hr = S_OK;
		// COM ��� ����
		hr = CoInitialize(NULL);
		if (SUCCEEDED(hr))
		{
			/*	��ġ�� ���ε����� ���� ���ҽ��� ����ϴ�.������ ���� ���ӵǴ� ���� ȿ�������� ����˴ϴ�.
				�̷��� ���ҽ����� Direct2D �� DirectWrite ���͸���
				DirectWrite �ؽ�Ʈ ���� ��ü(Ư�� �۲� Ư���� �ĺ��ϴ� �� ����)�� ���Ե˴ϴ�.
			*/
			hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
		}
		RECT rc;
		GetClientRect(hWnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
		if (SUCCEEDED(hr))
		{
			/*
			Direct3D ��ġ�� ���ε��� ���ҽ��� ����ϴ�.
			Direct3D ��ġ�� �սǵ� ���(��: ���÷��� ����, ����, ���� ī�� ���� ��)
			���ҽ��� �ٽ� �����ؾ� �ϴ� ��츦 ����Ͽ� ��� ���⿡ �߾� ����ȭ�Ǿ� �ֽ��ϴ�.
			*/
			// Create a Direct2D render target.
			hr = m_pD2DFactory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(hWnd, size),
				&m_pRenderTarget);

		}

		if (SUCCEEDED(hr))
		{
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::AliceBlue), &m_pBrush);
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
		}

		if (SUCCEEDED(hr))
		{
			// DirectWrite ���͸��� ����ϴ�.
			hr = DWriteCreateFactory(
				DWRITE_FACTORY_TYPE_SHARED,
				__uuidof(m_pDWriteFactory),
				reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
		}
		if (SUCCEEDED(hr))
		{
			// Create WIC factory
			hr = CoCreateInstance(
				CLSID_WICImagingFactory,
				NULL,
				CLSCTX_INPROC_SERVER,
				IID_PPV_ARGS(&m_pWICFactory)
			);
		}
		if (SUCCEEDED(hr))
		{
			// DirectWrite �ؽ�Ʈ ���� ��ü�� ����ϴ�.
			hr = m_pDWriteFactory->CreateTextFormat(
				L"", // FontName    ������-���������-�׸�-�۲�-Ŭ�� ���� �۲��̸� Ȯ�ΰ���
				NULL,
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				40.0f,   // Font Size
				L"", //locale
				&m_pDWriteTextFormat
			);

			hr = m_pDWriteFactory->CreateTextFormat(
				L"", // FontName    ������-���������-�׸�-�۲�-Ŭ�� ���� �۲��̸� Ȯ�ΰ���
				NULL,
				DWRITE_FONT_WEIGHT_BOLD,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				20.0f,   // Font Size
				L"", //locale
				&m_pDWriteTextFormats
			);
		}
		// VRAM ������� ���� ��ü ����
		if (SUCCEEDED(hr))
		{
			// Create DXGI factory
			hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&m_pDXGIFactory);
		}
		if (SUCCEEDED(hr))
		{
			m_pDXGIFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&m_pDXGIAdapter));
		}

	}

	void D2DEngine::UninitDirect2D()
	{
		SAFE_RELEASE(m_pBrush);
		SAFE_RELEASE(m_pBlackBrush);
		SAFE_RELEASE(m_pRenderTarget);
		SAFE_RELEASE(m_pD2DFactory);
		SAFE_RELEASE(m_pWICFactory);
		SAFE_RELEASE(m_pDWriteFactory);
		SAFE_RELEASE(m_pDWriteTextFormat);
		SAFE_RELEASE(m_pDWriteTextFormats);
		SAFE_RELEASE(m_pDXGIFactory);
		SAFE_RELEASE(m_pDXGIAdapter);
		CoUninitialize();
	}

	size_t D2DEngine::GetUsedVRAM()
	{
		DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
		m_pDXGIAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);
		return videoMemoryInfo.CurrentUsage / 1024 / 1024;
	}

	void D2DEngine::BeginDraw() {
		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	}
	void D2DEngine::EndDraw() { m_pRenderTarget->EndDraw(); }

	void D2DEngine::DrawSquare(int left, int right, int top, int bottom)
	{
		ID2D1StrokeStyle* pStrokeStyle = nullptr;
		D2D1_STROKE_STYLE_PROPERTIES strokeStyleProperties = D2D1::StrokeStyleProperties();
		m_pD2DFactory->CreateStrokeStyle(strokeStyleProperties, nullptr, 0, &pStrokeStyle);
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->DrawRectangle(
			D2D1::RectF(left, top, right, bottom),
			m_pBrush,
			5, // �簢���� �β��� �����մϴ�.
			pStrokeStyle // ������ StrokeStyle�� ����մϴ�.
		);
	}


	void D2DEngine::DrawTexts(const wchar_t* text, float left, float top)
	{
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->DrawTextW(
			text,
			wcslen(text),
			m_pDWriteTextFormat,
			D2D1::RectF(left, top, left + 1000, top + 1000),
			m_pBrush
		);

	}

	void D2DEngine::DrawTextsize(const wchar_t* text, float left, float right, float top, float bottom)
	{
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->DrawTextW(
			text,
			wcslen(text),
			m_pDWriteTextFormat,
			D2D1::RectF(left, top, right, bottom),
			m_pBrush
		);

	}

	void D2DEngine::DrawTextChat(const wchar_t* text, float left, float right, float top, float bottom)
	{
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->DrawTextW(
			text,
			wcslen(text),
			m_pDWriteTextFormats,
			D2D1::RectF(left, top, right, bottom),
			m_pBlackBrush
		);
	}

	HRESULT  D2DEngine::CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap)
	{
		HRESULT hr;
		// Create a decoder
		IWICBitmapDecoder* pDecoder = NULL;
		IWICFormatConverter* pConverter = NULL;

		hr = m_pWICFactory->CreateDecoderFromFilename(
			szFilePath,                      // Image to be decoded
			NULL,                            // Do not prefer a particular vendor
			GENERIC_READ,                    // Desired read access to the file
			WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
			&pDecoder                        // Pointer to the decoder
		);

		// Retrieve the first frame of the image from the decoder
		IWICBitmapFrameDecode* pFrame = NULL;

		if (SUCCEEDED(hr))
		{
			hr = pDecoder->GetFrame(0, &pFrame);
			hr = m_pWICFactory->CreateFormatConverter(&pConverter);
			hr = pConverter->Initialize(
				pFrame,                          // Input bitmap to convert
				GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
				WICBitmapDitherTypeNone,         // Specified dither pattern
				NULL,                            // Specify a particular palette 
				0.f,                             // Alpha threshold
				WICBitmapPaletteTypeCustom       // Palette translation type
			);
			//�׸��� ���� ��������
			hr = m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppID2D1Bitmap);
		}

		// ������ ����Ҷ����� �ٽ� �����.
		if (pConverter)pConverter->Release();
		if (pDecoder)pDecoder->Release();
		if (pFrame)pFrame->Release();

		return hr;
	}