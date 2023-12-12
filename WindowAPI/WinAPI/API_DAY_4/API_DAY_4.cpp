// API_DAY_4.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "API_DAY_4.h"

#pragma comment(lib, "winmm.lib") // 라이브러리(lib)에 속하는 종류의 "파일명"을 불러오라는 전처리기
// #pragma comment(comment-type [ , "comment-string" ] )
// comment-type에 지정한 타입에 따라 각기 다른 명령을 수행.
// 대괄호 안의 내용은 명령에 따라 필요로 하지 않는 경우도 있음
// lib : 뒤쪽의 comment에 적혀있는 라이브러리를 링크하라는 명령
// 그 외에 compiler, linker, exestr, user 등이 들어갈 수 있음

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// 각 도형의 위치값을 저장할 변수
int rect_x = 100, rect_y = 100; // 이번에 실제로 사용했던 사각형의 위치를 저장할 변수
// int circle_x = 300, circle_y = 100; // 이번엔 사용할 일 없었던 원의 위치를 저장할 변수 
// int triangle_x = 100, triangle_y = 300; // 이하동문 삼각형
// 
// 각 화살표 키가 눌려있는지를 체크할 변수
bool is_pressed_left = false; // 좌
bool is_pressed_right = false; // 우
bool is_pressed_up = false; // 상
bool is_pressed_down = false; // 하
// 이해가 편하도록 강의 중엔 각 변수마다 작업했지만, 일반적으로는 비트 플래그를 이용.
// 위의 경우, 0과 1의 비트 4개를 한 변수에 저장하는 식으로 처리할 수 있음

// ex | 좌우상하가 각각 true, false, false, true일 경우
// 1 / 0 / 0 / 1의 4개 비트로 처리가 가능
// 이를 10진수로 바꿀 경우 5가 되는 식
// 코드화시키면 다음과 같음
/*
char is_pressed_key = 0;

(...)

case WM_KEYDOWN:
    switch(wParam)
    {
        case VK_LEFT:
        is_pressed_key |(비트 연산자 or) 0b1000(2진수로 표기한 수 1000 = 8;
        break;

        case VK_DOWN:
        is_pressed_key | 0b0001(2진수로 표기한 수 0001 = 1);
        break;
    }

case WM_KEYUP:
    switch(wParam)
    {
        case VK_LEFT:
        is_pressed_key ^(비트 연산자 xor : 서로 다른 값이면 1) 0b1000(제외할 첫번째 플래그만 XOR로 제거);
        break;

        case VK_DOWN:
        is_pressed_key ^ 0b0001;
        break;
    }

그리고 메인에선 if (is_pressed_left == true) 대신 다음과 같이 진행

if(is_pressed_key & 0b1000)
    {
        rect_x -= 5;
        // circle_x -= 5;
        // triangle_x -= 5;
    }
if(is_pressed_key & 0b0001)
    {
        rect_x -= 5;
        // circle_x -= 5;
        // triangle_x -= 5;
    }

이 과정은 당연히 함수화할 수 있으며, 경우에 따라선 함수화하는 것이 더 효율적일 수 있음

*/


// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_APIDAY4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APIDAY4));

    MSG msg;


    DWORD time_stamp;           // DWORD = unsigned long(=int) : 프레임을 계산하기 위해 현재 시각을 기록해둘 변수
    time_stamp = timeGetTime(); // 윈도우즈(=컴퓨터)를 켠 뒤로 흐른 시간을 반환하는 함수 , 단위 : ms(정수) 
                                // Mmsystem.h 헤더와 winmm.lib를 포함시켜야 사용 가능

    DWORD frame = 0;    // 경과 시간을 기록해둘 변수

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // 메인에서 처리해야 할 반복 작업이 있을 경우 여기서 처리
        // 특정 메세지(특 키 눌림 등)를 받았을 때만 처리하면 안 되는 경우에 여기서 사용

        // 이하의 코드는 메인 루프 동안 키보드 입력 상태에 따라 움직임을 처리하는 코드

        DWORD current_time = timeGetTime(); // 매 루프마다 현재 시각을 측정
        frame += current_time - time_stamp; // 마지막으로 측정한 시각과 현재 시각을 비교하여, 경과한 시간을 frame에 가산

        if (frame >= 17) {  // 가산된 시간이 지정해둔 정규 프레임 단위와 비교해 상정한 시간이 경과되었는지 체크
            frame -= 17; // 경과되었다면 그 값을 제하고 동작

            // 왼쪽을 눌렀을 때
            if (is_pressed_left == true)
            {
                rect_x -= 5;
                // circle_x -= 5;
                // triangle_x -= 5;
            }
            // 오른쪽을 눌렀을 때
            if (is_pressed_right == true)
            {
                rect_x += 5;
                // circle_x += 5;
                // triangle_x += 5;
            }
            // 위를 눌렀을 때
            if (is_pressed_up == true)
            {
                rect_y -= 5;
                // circle_y -= 5;
                // triangle_y -= 5;
            }
            // 아래를 눌렀을 때
            if (is_pressed_down == true)
            {
                rect_y += 5;
                // circle_y += 5;
                // triangle_y += 5;
            }
            InvalidateRect(msg.hwnd, NULL, true);
        }

        time_stamp = current_time; // 마지막으로 기록한 시각을 이번에 기록했던 시각으로 갱신

        /*

        과제 -

        도형의 종류는 상관없습니다.

        방향키만 눌렀을 때 움직이는 도형과,
        방향키에 추가로 다른 버튼(왼쪽 쉬프트 등)까지 같이 눌렀을 때만 움직이는 도형을 만들어볼 것

        조건 : 방향키만 눌렀을 때 움직이는 도형은 다른 버튼을 누르고 움직이는 도형이 움직일 땐
        움직여선 안 됩니다.
        = 한 번에 움직이는 도형은 딱 하나만

        힌트 1 : 방향키 외에 다른 버튼이 눌려있는지도 같이 검사하는 식으로 접근하면 쉬울 것
        힌트 2 : 방향키 말고 다른 어떤 키가 있는지는 저번에 제공해드린 코드에서 안내드린 바 있음

        본 과제 특성상 스크린샷 몇 장 같은 식으로 제출하기는 힘드니
        동영상을 찍어서 gif로 만들어 올리기
        ex | https://ezgif.com/video-to-gif
        위와 같은 무료 동영상 gif 컨버팅 사이트를 이용하면 편리

        */

        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APIDAY4));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_APIDAY4);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
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
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...

        /*
        본 강의에서 사용할 예정이었지만 결국 사용하지 못했던 2일차의 코드는 제거했습니다.

        복습에 필요하시다면 기존 프로젝트에서 가져오셔서 뜯어고치셔도 됩니다.
        */

        // 사각형 그리기
        Rectangle(hdc,
            rect_x - 50,  // 사각형의 왼쪽 위 지점의 X좌표
            rect_y - 50,  // 사각형의 왼쪽 위 지점의 Y좌표
            rect_x + 50, // 사각형의 오른쪽 아래 지점의 X좌표
            rect_y + 50  // 사각형의 오른쪽 아래 지점의 Y좌표
        );

        EndPaint(hWnd, &ps);
    }
    break;

    // https://learn.microsoft.com/ko-kr/windows/win32/inputdev/virtual-key-codes
    // VK(=Virtual Key, 가상 키 코드)
    // 키보드 및 다른 입력장치의 다른 키들은 어떤 값을 이용하는지 위 페이지에서 확인 가능

    // WM의 종류는 MS 도움말에 한 페이지에 정리된 것이 없어 일일이 찾아봐야 함

    case WM_KEYDOWN: // 키가 눌렸을 경우 처리되는 구문.
        // 누른 순간만을 판단하는 것이 아님에 유의. 길이 상관없이 키가 눌려있기만 하면 이 메세지가 발생

        switch (wParam) // 눌린 키에 따라 처리
        {
            // 이하의 내용은 각 키가 눌려있는지를 검사할 플래그의 값을 바꾸는 코드
        case VK_LEFT: // 왼쪽 키
            is_pressed_left = true;
            break;

        case VK_RIGHT: // 오른쪽 키
            is_pressed_right = true;
            break;

        case VK_UP: // 위쪽 키
            is_pressed_up = true;
            break;

        case VK_DOWN: // 아래쪽 키
            is_pressed_down = true;
            break;
        }

        break;

    case WM_KEYUP: // 키가 떼진 경우
        switch (wParam) // 눌린 키에 따라 처리
        {
        case VK_LEFT: // 왼쪽 키
            is_pressed_left = false;
            break;

        case VK_RIGHT: // 오른쪽 키
            is_pressed_right = false;
            break;

        case VK_UP: // 위쪽 키
            is_pressed_up = false;
            break;

        case VK_DOWN: // 아래쪽 키
            is_pressed_down = false;
            break;
        }

        break;

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
