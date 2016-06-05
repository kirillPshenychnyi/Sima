#include <windows.h>         // ����������� ���������� � ��������� API
#include <cassert>
#include "commonInfo.hpp"
#include "resource.h"

// ���������� ����������:
HINSTANCE hInst; 	// ��������� ����������
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "Sima";
int g_nCmdShow;
static CommonInfo g_globalnfo;

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
	g_nCmdShow = nCmdShow;

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

BOOL CALLBACK getNameDlg(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
	static char name[30], name2[30];
	switch (iMsg) 
	{
		case WM_INITDIALOG:   
			return TRUE;

		case WM_COMMAND:   
			switch (LOWORD(wParam)) 
			{ 
				case IDC_EDIT2:
					if (HIWORD(wParam) == EN_UPDATE)
						GetWindowText(HWND(lParam), name, 30);
					break;

				case IDC_EDIT3:
					if (HIWORD(wParam) == EN_UPDATE)
						GetWindowText(HWND(lParam), name2, 30);
					break;

				case IDOK:   
					EndDialog(hDlg, 0);

					if (!strlen(name) || !strlen(name2))
					{
						MessageBox(hDlg, "All fields should be filled", "Input error", MB_OK);
						break;
					}
					
					g_globalnfo.m_firstName = name;
					g_globalnfo.m_secondName = name2;

					return TRUE;

				case IDCANCEL:
					EndDialog(hDlg, 0);
					return TRUE; 
			}   

			break;

		default:
			break;
	}  
	
	return FALSE;
}

//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//  ������� ���������. ��������� � ������������ ��� ���������, ���������� � ����������



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE: // ��������� �������� ��� �������� ����
		break;

/***************************************************************************/

	case WM_PAINT:  // ������������ ����
		g_globalnfo.m_hdc = BeginPaint(hWnd, &g_globalnfo.m_ps);	// ������ ����������� �����
		
		if (!g_globalnfo.m_pGame)
			break;
		
		if (g_globalnfo.m_pGame->isOver())
			break;

		if (g_globalnfo.m_first && g_globalnfo.m_second)
		{
			bool connected = g_globalnfo.m_pProcessor->drawLine(g_globalnfo.m_hdc, * g_globalnfo.m_first, * g_globalnfo.m_second);
		
			if (connected)
			{
				g_globalnfo.m_pGame->addPoints( * g_globalnfo.m_first, *g_globalnfo.m_second);

				g_globalnfo.m_pGame->onStep();
			}

			g_globalnfo.m_winner = g_globalnfo.m_pGame->getWinner();

			if (!g_globalnfo.m_winner.empty())
			{
				g_globalnfo.m_pProcessor->printWinner(hWnd, g_globalnfo.m_winner);

				g_globalnfo.m_pProcessor->printTriangle(g_globalnfo.m_hdc, g_globalnfo.m_pGame->getTriangle() );

			}
			g_globalnfo.m_first = g_globalnfo.m_second = nullptr;
		}

		g_globalnfo.m_pProcessor->drawPoints(g_globalnfo.m_hdc, g_globalnfo.m_pGame->getField().getPoints() );

		EndPaint(hWnd, &g_globalnfo.m_ps);	// ��������� ����������� �����
		break;

/***************************************************************************/

	case WM_LBUTTONDOWN:

		if (!g_globalnfo.m_pGame)
			break;

		g_globalnfo.m_x = LOWORD(lParam);

		g_globalnfo.m_y = HIWORD(lParam);

		g_globalnfo.m_temp = g_globalnfo.m_pGame->getField().onClicked(g_globalnfo.m_x, g_globalnfo.m_y );

		if (!g_globalnfo.m_click && g_globalnfo.m_temp)
		{
			g_globalnfo.m_first = g_globalnfo.m_temp;

			g_globalnfo.m_click++;

			InvalidateRect(hWnd, NULL, FALSE);
		}

		else if (g_globalnfo.m_click && g_globalnfo.m_temp )
		{
			g_globalnfo.m_second = g_globalnfo.m_temp;
			
			g_globalnfo.m_click = 0;

			InvalidateRect(hWnd, NULL, FALSE);

		}

		break;

/***************************************************************************/

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_GAME_NEWGAME:
			if (g_globalnfo.m_pGame)
				g_globalnfo.m_pGame.reset();
			
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, getNameDlg);
	
			if (g_globalnfo.m_firstName.empty() || g_globalnfo.m_secondName.empty())
				break;

			g_globalnfo.m_pGame = std::make_unique<Game>( g_globalnfo.m_firstName, g_globalnfo.m_secondName ); // ������ ����� ���� 
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

