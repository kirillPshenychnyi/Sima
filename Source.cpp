#include <windows.h>         // ����������� ���������� � ��������� API
#include <cassert>
#include "commonInfo.hpp"
#include "resource.h"

// ���������� ����������:
HINSTANCE hInst; 	// ��������� ����������
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "Sima";

// ��������������� �������� �������

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// �������� ��������� 
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	MSG msg;

	// ����������� ������ ���� 
	MyRegisterClass(hInstance);

	// �������� ���� ����������
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// ���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//  FUNCTION: MyRegisterClass()
//  ������������ ����� ���� 

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;	// ����� ����
	wcex.lpfnWndProc = (WNDPROC)WndProc; // ������� ���������
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;		// ��������� ����������
	wcex.hIcon = LoadIcon(NULL, IDI_HAND);		// ����������� ������
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);    // ����������� �������
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW);   // ��������� ����
	wcex.lpszMenuName = NULL;		// ����������� ����
	wcex.lpszClassName = szWindowClass;	// ��� ������
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); // ����������� ������ ����
}

// FUNCTION: InitInstance(HANDLE, int)
// ������� ���� ���������� � ��������� ��������� ���������� � ���������� hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // ��������� ��������� ���������� � ���������� hInst
	HMENU menu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));

	hWnd = CreateWindow(szWindowClass, // ��� ������ ����
		szTitle,   // ��� ����������
		WS_OVERLAPPEDWINDOW, // ����� ����
		CW_USEDEFAULT,	// ��������� �� �
		CW_USEDEFAULT, 	// ��������� �� Y
		CW_USEDEFAULT,    // ������ �� �
		CW_USEDEFAULT,    // ������ �� Y
		NULL,	// ��������� ������������� ����
		menu,       // ��������� ���� ����
		hInstance,  // ��������� ����������
		NULL);     // ��������� ��������.

	if (!hWnd) // ���� ���� �� ���������, ������� ���������� FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);		// �������� ����
	UpdateWindow(hWnd);			// �������� ����
	return TRUE;				//�������� ���������� �������
}

//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//  ������� ���������. ��������� � ������������ ��� ���������, ���������� � ����������


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static CommonInfo s_commonInfo;

	switch (message)
	{
	case WM_CREATE: // ��������� �������� ��� �������� ����
		break;

/***************************************************************************/

	case WM_PAINT:  // ������������ ����
		s_commonInfo.m_hdc = BeginPaint(hWnd, &s_commonInfo.m_ps);	// ������ ����������� �����
		
		if (!s_commonInfo.m_pGame)
			break;
		
		if (s_commonInfo.m_pGame->isOver())
			break;

		if (s_commonInfo.m_first && s_commonInfo.m_second)
		{
			bool connected = s_commonInfo.m_pProcessor->drawLine(s_commonInfo.m_hdc, * s_commonInfo.m_first, * s_commonInfo.m_second);
		
			if (connected)
			{
				s_commonInfo.m_pGame->addPoints( * s_commonInfo.m_first, *s_commonInfo.m_second);

				s_commonInfo.m_pGame->onStep();
			}

			s_commonInfo.m_winner = s_commonInfo.m_pGame->getWinner();

			if ( !s_commonInfo.m_winner.empty())
				s_commonInfo.m_pProcessor->printWinner( hWnd, s_commonInfo.m_winner);
			
			s_commonInfo.m_first = s_commonInfo.m_second = nullptr;
		}

		s_commonInfo.m_pProcessor->drawPoints(s_commonInfo.m_hdc, s_commonInfo.m_pGame->getField().getPoints() );

		EndPaint(hWnd, &s_commonInfo.m_ps);	// ��������� ����������� �����
		break;

/***************************************************************************/

	case WM_LBUTTONDOWN:

		if (!s_commonInfo.m_pGame)
			break;

		s_commonInfo.m_x = LOWORD(lParam);

		s_commonInfo.m_y = HIWORD(lParam);

		s_commonInfo.m_temp = s_commonInfo.m_pGame->getField().onClicked(s_commonInfo.m_x, s_commonInfo.m_y );

		if (!s_commonInfo.m_click && s_commonInfo.m_temp)
		{
			s_commonInfo.m_first = s_commonInfo.m_temp;

			s_commonInfo.m_click++;

			InvalidateRect(hWnd, NULL, FALSE);
		}

		else if (s_commonInfo.m_click && s_commonInfo.m_temp )
		{
			s_commonInfo.m_second = s_commonInfo.m_temp;
			
			s_commonInfo.m_click = 0;

			InvalidateRect(hWnd, NULL, FALSE);

		}

		break;

/***************************************************************************/

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_GAME_NEWGAME:
			if (s_commonInfo.m_pGame)
				s_commonInfo.m_pGame.reset();
			s_commonInfo.m_pGame = std::make_unique<Game>( "John", "Jack" ); // ������ ����� ���� 
			InvalidateRect(hWnd, NULL, TRUE); // ������������� ������� ������� 
			break;
		default:
			break;
		}
		break;

/***************************************************************************/

	case WM_DESTROY: // ���������� ������
		PostQuitMessage(0);
		break;
	default:
		// ��������� ���������, ������� �� ���������� �������������
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

