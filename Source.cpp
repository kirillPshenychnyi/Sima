#include <windows.h>         // подключение библиотеки с функциями API
#include <cassert>
#include "commonInfo.hpp"
#include "resource.h"

// Глобальные переменные:
HINSTANCE hInst; 	// Указатель приложения
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "Sima";

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

//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//  Оконная процедура. Принимает и обрабатывает все сообщения, приходящие в приложение


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static CommonInfo s_commonInfo;

	switch (message)
	{
	case WM_CREATE: // Сообщение приходит при создании окна
		break;

/***************************************************************************/

	case WM_PAINT:  // Перерисовать окно
		s_commonInfo.m_hdc = BeginPaint(hWnd, &s_commonInfo.m_ps);	// Начать графический вывод
		
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

		EndPaint(hWnd, &s_commonInfo.m_ps);	// Закончить графический вывод
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
			s_commonInfo.m_pGame = std::make_unique<Game>( "John", "Jack" ); // создаём новую игру 
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

