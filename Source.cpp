#include <windows.h>         // подключение библиотеки с функциями API
#include <cassert>
#include "commonInfo.hpp"
#include "resource.h"

// Глобальные переменные:
HINSTANCE hInst; 	// Указатель приложения
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "Sima";
int g_nCmdShow;
static CommonInfo g_globalnfo;

// Предварительное описание функций

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Основная программа 
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	MSG msg;

	// Регистрация класса окна 
	MyRegisterClass(hInstance);

	// Создание окна приложения
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//  FUNCTION: MyRegisterClass()
//  Регистрирует класс окна 

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;	// стиль окна
	wcex.lpfnWndProc = (WNDPROC)WndProc; // оконная процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;		// указатель приложения
	wcex.hIcon = LoadIcon(NULL, IDI_HAND);		// определение иконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);    // определение курсора
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW);   // установка фона
	wcex.lpszMenuName = NULL;		// определение меню
	wcex.lpszClassName = szWindowClass;	// имя класса
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); // регистрация класса окна
}

// FUNCTION: InitInstance(HANDLE, int)
// Создает окно приложения и сохраняет указатель приложения в переменной hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	g_nCmdShow = nCmdShow;

	hInst = hInstance; // сохраняет указатель приложения в переменной hInst
	HMENU menu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));

	hWnd = CreateWindow(szWindowClass, // имя класса окна
		szTitle,   // имя приложения
		WS_OVERLAPPEDWINDOW, // стиль окна
		CW_USEDEFAULT,	// положение по Х
		CW_USEDEFAULT, 	// положение по Y
		CW_USEDEFAULT,    // размер по Х
		CW_USEDEFAULT,    // размер по Y
		NULL,	// описатель родительского окна
		menu,       // описатель меню окна
		hInstance,  // указатель приложения
		NULL);     // параметры создания.

	if (!hWnd) // Если окно не создалось, функция возвращает FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);		// Показать окно
	UpdateWindow(hWnd);			// Обновить окно
	return TRUE;				//Успешное завершение функции
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
//  Оконная процедура. Принимает и обрабатывает все сообщения, приходящие в приложение



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE: // Сообщение приходит при создании окна
		break;

/***************************************************************************/

	case WM_PAINT:  // Перерисовать окно
		g_globalnfo.m_hdc = BeginPaint(hWnd, &g_globalnfo.m_ps);	// Начать графический вывод
		
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

		EndPaint(hWnd, &g_globalnfo.m_ps);	// Закончить графический вывод
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

			g_globalnfo.m_pGame = std::make_unique<Game>( g_globalnfo.m_firstName, g_globalnfo.m_secondName ); // создаём новую игру 
			InvalidateRect(hWnd, NULL, TRUE); // перерисовывем рабочую область 
			break;
		default:
			break;
		}
		break;

/***************************************************************************/

	case WM_DESTROY: // Завершение работы
		PostQuitMessage(0);
		break;
	default:
		// Обработка сообщений, которые не обработаны пользователем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

