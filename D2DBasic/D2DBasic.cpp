//기능: 기본 윈도우 클라이언트 영역을 특정 색상으로 채운다.
//기본적인윈도우 애플리케이션 생성 + Direct2D를 사용
#include "D2DBasic.h"
#include "D2DEngine.h"
#include "ResourceManager.h"
#include "ScreenManager.h"
#include "Battle.h"
 
D2DBasic::D2DBasic() {
	m_pRenderer = new D2DEngine;
	m_pResourceManager = new ResourceManager;
	m_pScreenManager = new ScreenManager;
}

D2DBasic::~D2DBasic() {

}
void D2DBasic::Initialize(HINSTANCE hInstance)
{
	// 윈도우 클래스 구조체 초기화(윈도우 정의하고 등록하기)
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	// 윈도우 프로시저 함수
	wc.hInstance = hInstance;   // 인스턴스 핸들
	// NULL을 사용하면 현재 실행 중인 프로그램의 인스턴스 핸들을 사용하게 됩니다.두 번째 인자는 로드할 커서의 ID입니다.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = L"BasicWindowClass";
	wc.hIcon = (HICON)LoadImageW(
		hInstance,       
		L"../Resource/pixil-frame-0.ico",       
		IMAGE_ICON,    
		0,             
		0,             
		LR_LOADFROMFILE
	);
	// 윈도우 클래스 등록
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"윈도우 클래스 등록 실패", L"에러", MB_OK | MB_ICONERROR);
	}

	// 원하는 크기가 조정되어 리턴
	SIZE clientSize = { 1024, 768 };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);
	// 윈도우 생성
	g_hWnd = CreateWindowEx(
		0,
		L"BasicWindowClass",
		L"undertale",
		WS_OVERLAPPEDWINDOW,	// OR연산으로 조합된 윈도우창 스타일
		0, 0,	// 시작위치
		clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, // 너비, 높이
		NULL, NULL, hInstance, NULL
	);

	if (!g_hWnd)
	{
		MessageBox(NULL, L"윈도우 생성 실패", L"에러", MB_OK | MB_ICONERROR);
	}

	// 윈도우 표시
	ShowWindow(g_hWnd,SW_SHOWNORMAL);
	UpdateWindow(g_hWnd);

	//Direct2D함수를 호출하여 초기화해준다.
	m_pRenderer->InitDirect2D(g_hWnd);
	ResourceManager::pInstance->D2D=m_pRenderer;
	GameTime::InitTime();
}

void D2DBasic::Run()
{
	MSG msg;
	// 기본 메시지 루프. 여기서 메세지를 처리해준다.
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			//윈도우 메시지 처리 
			TranslateMessage(&msg); // 키입력관련 메시지 변환  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&msg);
		}
		else
		{
			GameTime::UpdateTime();
			float times = GameTime::GetDeltaTime();
			Update(times);
			Render();
		}
	}
}

void D2DBasic::Finalize() 
{
	m_pRenderer->UninitDirect2D(); //메세지가 종료되면 Direct2d 해제를 진행
}

void D2DBasic::Render()
{

}

void D2DBasic::Update(float times)
{
}
// 윈도우 프로시저 함수 정의
LRESULT CALLBACK D2DBasic::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY://WM_DESTROY메세지를 전달받으면 종료.
		PostQuitMessage(0);
		break;
	default: //그 외에는 기본 프로시저로 처리합니다.
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
