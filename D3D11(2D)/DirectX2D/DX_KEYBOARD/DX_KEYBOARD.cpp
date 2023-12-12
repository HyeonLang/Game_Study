﻿// DX_KEYBOARD.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "DX_KEYBOARD.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND hWnd;

Float2 object_pos;
UINT key_map = 0;
/*
    키보드의 키 눌림 여부를 저장하는 비트플래그

    비트 플래그의 맵핑을 여기서 정의

    비트값         할당된키
    1               LEFT
    2               RIGHT
    4               UP
    8               DWON
    16
    32
    64
*/
DWORD time_stamp;
POINT mouse_pos = { 0, 0 };

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DXKEYBOARD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DXKEYBOARD));

    MSG msg = {};
    Program program;

    // 기본 메시지 루프입니다:
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        program.Update();
        program.Render();
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DXKEYBOARD));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DXKEYBOARD);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT windows_size = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
   AdjustWindowRect(&windows_size, WS_OVERLAPPEDWINDOW, false);
   // 함수의 작동방식 : right, bottom 값 뿐만 아니라 left up도 바꾸게 되어있음
   // 그 분량만큼 밑에서 창 크기를 지정할 때 더해주어야 사이즈가 인식

   
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, 
       windows_size.right - windows_size.left, windows_size.bottom - windows_size.top,
       nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
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
    case WM_KEYDOWN:
        // 동시입력 키를 사용하기 위해 switch문이 아닌 if문을 사용
        //각 조건문마다 키가 눌려있는지 여부를 반환받아 0x8000과 and 연산하여 판단.
        if (GetAsyncKeyState(VK_UP) & 0x8000)
        {
            key_map |= 4;
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            key_map |= 8;
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            key_map |= 1;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            key_map |= 2;
        }
        // 0x8000은 Short에서 표기가능한 가장 큰수의 절반값
        // GetAsyncKeyState()는 short를 반환
        // 0x8000은 현재 키가 눌려있는가를 반환 
        break;
    case WM_KEYUP:
        if (!(GetAsyncKeyState(VK_UP) & 0x8000))
        {
            key_map &= ~4;
            // UP이 대응되는 값을 플래그에서 이탈시킨다.
        }
        if (!(GetAsyncKeyState(VK_DOWN) & 0x8000))
        {
            key_map &= ~8;
        }
        if (!(GetAsyncKeyState(VK_LEFT) & 0x8000))
        {
            key_map &= ~1;
        }
        if (!(GetAsyncKeyState(VK_RIGHT) & 0x8000))
        {
            key_map &= ~2;
        }
    case WM_PAINT:
        { 
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_MOUSEMOVE:
        mouse_pos.x = GET_X_LPARAM(lParam);
        mouse_pos.y = GET_Y_LPARAM(lParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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