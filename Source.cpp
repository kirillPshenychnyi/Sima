#include <windows.h>         // ����������� ���������� � ��������� API
#include <cassert>
#include "Game.hpp"
#include "GUI_Processor.hpp"
#include "Point.hpp"

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

	hWnd = CreateWindow(szWindowClass, // ��� ������ ����
		szTitle,   // ��� ����������
		WS_OVERLAPPEDWINDOW, // ����� ����
		CW_USEDEFAULT,	// ��������� �� �
		CW_USEDEFAULT, 	// ��������� �� Y
		CW_USEDEFAULT,    // ������ �� �
		CW_USEDEFAULT,    // ������ �� Y
		NULL,	// ��������� ������������� ����
		NULL,       // ��������� ���� ����
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
	PAINTSTRUCT ps;
	HDC hdc;
	static std::unique_ptr < Game > s_pGame = std::make_unique< Game >("John", "Jack");
	static std::unique_ptr < GUIProcessor > s_pProcessor = std::make_unique< GUIProcessor >();

	static int x, y;

	static  Point::Point * first = nullptr;
	static  Point::Point * second = nullptr;
	static  Point::Point * temp = nullptr;
	std::string winner;
	static int click = 0;

	switch (message)
	{
	case WM_CREATE: // ��������� �������� ��� �������� ����
		break;

	case WM_PAINT:  // ������������ ����
		hdc = BeginPaint(hWnd, &ps);	// ������ ����������� �����
		
		if ( first && second)
		{
			bool connected = s_pProcessor->drawLine(hdc, *first, *second);
		
			if ( connected )
				s_pGame->addPoint( * first);

			winner = s_pGame->getWinner();

			first = second = nullptr;
		}

		s_pProcessor->drawPoints( hdc, s_pGame->getField().getPoints() );

		EndPaint(hWnd, &ps);	// ��������� ����������� �����
		break;

	case WM_LBUTTONDOWN:

		x = LOWORD(lParam);

		y = HIWORD(lParam);

		temp = s_pGame->getField().onClicked( x, y );

		if (!click && temp)
		{
			first = temp;

			click++;

			InvalidateRect(hWnd, NULL, FALSE);
		}

		else if ( click && temp )
		{
			second = temp;
			
			click = 0;

			InvalidateRect(hWnd, NULL, FALSE);

		}

		break;

	case WM_DESTROY: // ���������� ������
		PostQuitMessage(0);
		break;
	default:
		// ��������� ���������, ������� �� ���������� �������������
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}