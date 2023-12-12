// WindowsProject1.cpp : Defines the entry point for the application.
//


/*
    stack을 사용하여 undo, redo 기능 구현


*/

/*
    Win API
    - Windows Application Program Interface
    - 윈도우를 개발하고, 표현하는데 사용하는 함수의 집합

    Windows : 운영체제
    API : 운영체제가 제공하는 응용프로그램을 만들기위한 함수의 집합
*/

#include "stdafx.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING] = PROGRAM_TITLE;  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND g_hWnd;
POINT g_mouse_pos;
HDC g_hDC;

MainGame* main_game = nullptr;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


/*
    Handle
    - 운영체제 내부에 있는 리소스(자원)의 주소를 정수로 치환한 값
    - 핸들 테이블에서 핸들과 리소스의 주소가 관리된다.

    Resource : 각종 하드웨어 장치 또는 저장장치(메모리, 하드 들)에 들어있는 데이터 자료

    Instance Handle : 윈도우에서 현재 실행중인 프로세서의 핸들을 가리키는 것
*/
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // 프로그램의 핸들 인스턴스     
                     _In_opt_ HINSTANCE hPrevInstance,  // 이전에 실행된 핸들 인스턴스 
                     _In_ LPWSTR    lpCmdLine,          // 명령행으로 입력 된 프로그램 인수 - 실행할 때 프로그램의 초기설정 변경 가능
                     _In_ int       nCmdShow)           // 프로그램이 시작될 때 형태(최소화, 보통 등의 상태 값)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    // 창을 초기화해주고 생성해주는 부분
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    HDC hdc = GetDC(g_hWnd); // 메인 DC를 받는다.
    g_hDC = CreateCompatibleDC(hdc); // 메인 DC를 사용하여 백 버퍼로 사용할 DC 생성
    // 비트맵 : 픽셀 이미지를 저장하는 이진파일 또는 메모리 저장 방식
    HBITMAP bit_map = (HBITMAP)(CreateCompatibleBitmap)(hdc, WINSIZE_X, WINSIZE_Y); // 렌더할 비트맵 생성
    SelectObject(g_hDC, bit_map); // 백 버퍼 DC에 생성한 비트맵 객체를 연결시켜준다.

    main_game = new MainGame;
    main_game->Init();

    // Main message loop:
    //while (GetMessage(&msg, nullptr, 0, 0)) // GetMessage : 메시지 큐에서 메시지를 읽는다.
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg); // 메시지를 읽을 수 있는 형태로 변경  
    //        DispatchMessage(&msg);  // 메시지를 신고(메시지 처리 함수로 보내준다.)
    //    }
    //}

    while (1)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;

            TranslateMessage(&msg);
            DispatchMessage(&msg); 
        }

        if (main_game != nullptr)
        {
            main_game->Update();
            main_game->Render();
        }
    }


    DeleteObject(bit_map);
    DeleteDC(g_hDC);

    delete main_game;

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // 윈도우의 정보를 저장하는 구조체
    // 창을 어떤식으로 만들것인지에 대해서 작성한다.
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX); // 구조체의 크기 정보를 넣는다.

    // CS_HREDRAW | CS_VREDRAW : 가로, 세로 크기 변경시 창을 다시 그린다.
    wcex.style          = CS_HREDRAW | CS_VREDRAW;                                      // 윈도우 스타일   
    wcex.lpfnWndProc    = WndProc;                                                      // 메시지 처리 함수 지정
    wcex.cbClsExtra     = 0;                                                            // 클래스 여분 메모리
    wcex.cbWndExtra     = 0;                                                            // 윈도우 여분 메모리
    wcex.hInstance      = hInstance;                                                    // 인스턴스
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));    // 창의 아이콘
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);                               // 마우스 커서
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);                                     // 배경색
    wcex.lpszMenuName   = NULL;                        // 메뉴이름(NULL일시 메뉴 제거)
    wcex.lpszClassName  = szWindowClass;                                                // 클래스 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));         // 작은 아이콘

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   // 화면 해상도 받기
   int resolution_x = GetSystemMetrics(SM_CXSCREEN);
   int resolution_y = GetSystemMetrics(SM_CYSCREEN);

   // 창 화면 중앙 위치 계산
   int win_pos_x = resolution_x / 2 - WINSIZE_X / 2;
   int win_pos_y = resolution_y / 2 - WINSIZE_Y / 2;

   HWND hWnd = CreateWindowW(
       szWindowClass,       // 윈도우 클래스의 이름
       szTitle,             // 타이틀바의 이름
       WS_OVERLAPPEDWINDOW, // 윈도우 스타일
       win_pos_x,           // 윈도우 화면 좌표 X : 실행할 때 창을 어느위치에서 띄울것인지
       win_pos_y,           // 윈도우 화면 좌표 Y
       WINSIZE_X,           // 윈도우 가로 사이즈
       WINSIZE_Y,           // 윈도우 세로 사이즈
       nullptr,             // 부모 윈도우
       nullptr,             // 메뉴 핸들
       hInstance,           // 인스턴스 지정
       nullptr              // 자식 윈도우를 생성하면 지정, 없다면 NULL
   );

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   {
       // 현재 윈도우 크기 받는다.
       RECT rt = { win_pos_x, win_pos_y, win_pos_x + WINSIZE_X, win_pos_y + WINSIZE_Y };

       // 원하는 작업 영역의 크기, 스타일값, 메뉴의 여부를 넘기면
       // 원하는 작업영역에 맞는 윈도우 크기를 계산해 rt에 넣어준다.
       AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

       // 윈도우의 위치, 크기를 변경한다.
       MoveWindow(
           hWnd,
           win_pos_x,
           win_pos_y,
           rt.right - rt.left,
           rt.bottom - rt.top,
           TRUE
       );
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

/*
    Proc
    - 메시지 처리 함수
    - Win API는 메시지 기반 프로그래밍이다.(생성되는 메시지를 처리한다.)
    - 메시지를 담는 거대한 메시지 큐가 존재한다. -> 마지막에 들어온 메시지는 앞에 메시지가
    처리될때까지 동작을 할 수 없어 느리다.
    - api로 모든것을 처리하기에는 느리기에 기본적인 창띄우기, 마우스 처리 용도 정도만 사용한다.
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_CREATE: // 창이 생설될 때 1번 호출되는 메시지
    {
        srand(time(NULL));
        break;
    }

    case WM_MOUSEMOVE:
    {
        g_mouse_pos.x = LOWORD(lParam);
        g_mouse_pos.y = HIWORD(lParam);
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
