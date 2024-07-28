//���: �⺻ ������ Ŭ���̾�Ʈ ������ Ư�� �������� ä���.
//�⺻���������� ���ø����̼� ���� + Direct2D�� ���
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
	// ������ Ŭ���� ����ü �ʱ�ȭ(������ �����ϰ� ����ϱ�)
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	// ������ ���ν��� �Լ�
	wc.hInstance = hInstance;   // �ν��Ͻ� �ڵ�
	// NULL�� ����ϸ� ���� ���� ���� ���α׷��� �ν��Ͻ� �ڵ��� ����ϰ� �˴ϴ�.�� ��° ���ڴ� �ε��� Ŀ���� ID�Դϴ�.
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
	// ������ Ŭ���� ���
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"������ Ŭ���� ��� ����", L"����", MB_OK | MB_ICONERROR);
	}

	// ���ϴ� ũ�Ⱑ �����Ǿ� ����
	SIZE clientSize = { 1024, 768 };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);
	// ������ ����
	g_hWnd = CreateWindowEx(
		0,
		L"BasicWindowClass",
		L"undertale",
		WS_OVERLAPPEDWINDOW,	// OR�������� ���յ� ������â ��Ÿ��
		0, 0,	// ������ġ
		clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, // �ʺ�, ����
		NULL, NULL, hInstance, NULL
	);

	if (!g_hWnd)
	{
		MessageBox(NULL, L"������ ���� ����", L"����", MB_OK | MB_ICONERROR);
	}

	// ������ ǥ��
	ShowWindow(g_hWnd,SW_SHOWNORMAL);
	UpdateWindow(g_hWnd);

	//Direct2D�Լ��� ȣ���Ͽ� �ʱ�ȭ���ش�.
	m_pRenderer->InitDirect2D(g_hWnd);
	ResourceManager::pInstance->D2D=m_pRenderer;
	GameTime::InitTime();
}

void D2DBasic::Run()
{
	MSG msg;
	// �⺻ �޽��� ����. ���⼭ �޼����� ó�����ش�.
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			//������ �޽��� ó�� 
			TranslateMessage(&msg); // Ű�Է°��� �޽��� ��ȯ  WM_KEYDOWN -> WM_CHAR
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
	m_pRenderer->UninitDirect2D(); //�޼����� ����Ǹ� Direct2d ������ ����
}

void D2DBasic::Render()
{

}

void D2DBasic::Update(float times)
{
}
// ������ ���ν��� �Լ� ����
LRESULT CALLBACK D2DBasic::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY://WM_DESTROY�޼����� ���޹����� ����.
		PostQuitMessage(0);
		break;
	default: //�� �ܿ��� �⺻ ���ν����� ó���մϴ�.
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
