// API_DAY_5.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "API_DAY_5.h"

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

// 더블 버퍼링에 이용할 버퍼 생성
HDC buffer_hdc;
HBITMAP buffer_bitmap;

// 각 도형의 위치값을 저장할 변수
int rect_x = 100, rect_y = 100; // 이번에 실제로 사용했던 사각형의 위치를 저장할 변수
int circle_x = 300, circle_y = 100; // 이번엔 사용할 일 없었던 원의 위치를 저장할 변수 
// int triangle_x = 100, triangle_y = 300; // 이하동문 삼각형
// 
// 각 화살표 키가 눌려있는지를 체크할 변수
bool is_pressed_left = false; // 좌
bool is_pressed_right = false; // 우
bool is_pressed_up = false; // 상
bool is_pressed_down = false; // 하

// 쉬프트에 대항하는 플래그
bool is_pressed_shift = false;

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
void CreateBackPage(HWND hWnd, HINSTANCE hInst, HDC* memDC, HBITMAP* memBitmap);

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
    LoadStringW(hInstance, IDC_APIDAY5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APIDAY5));

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

        time_stamp = current_time; // 마지막으로 기록한 시각을 이번에 기록했던 시각으로 갱신

        if (frame >= 17) {  // 가산된 시간이 지정해둔 정규 프레임 단위와 비교해 상정한 시간이 경과되었는지 체크
            frame -= 17; // 경과되었다면 그 값을 제하고 동작
            if (is_pressed_shift == false) {
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
            }

            if (is_pressed_shift == true) {
                // 왼쪽을 눌렀을 때
                if (is_pressed_left == true)
                {
                    //rect_x -= 5;
                    circle_x -= 5;
                    // triangle_x -= 5;
                }
                // 오른쪽을 눌렀을 때
                if (is_pressed_right == true)
                {
                    //rect_x += 5;
                    circle_x += 5;
                    // triangle_x += 5;
                }
                // 위를 눌렀을 때
                if (is_pressed_up == true)
                {
                    //rect_y -= 5;
                    circle_y -= 5;
                    // triangle_y -= 5;
                }
                // 아래를 눌렀을 때
                if (is_pressed_down == true)
                {
                    //rect_y += 5;
                    circle_y += 5;
                    // triangle_y += 5;
                }
            }
           
            InvalidateRect(msg.hwnd, NULL, false); 
            // 기존 화면에 새 화면을 완전히 덮어 씌우는 것으로 더블 버퍼링을 구현 : false
            // 바로 밑에서 새 화면을 흰색으로 다시 채우는 것이 새로 그리는 것이기 때문이다.
            /*
                기존 방식은 그 장소에 다시 새로 그리기 떄문에 화면이 깜빡거리는 것 처럼 보였는데
                더블 버퍼링은 도화지 두개가 있는 상태에
                도화지1에 그림 1을 그리고 
                우리가 보이지 않는 상태에서 도화지2에 다른 그림을 그리고 있다가
                순식간에 바꿔치기를 하는 구조임

                InvalidateRect(msg.hwnd, NULL, true);

                기존(도화지1개 뿐..)에는 사각형 무효화 함수(InvalidateRect)에 이렇게 마지막을 
                true 값 주면 지우고 새로 그리기 (새도화지에 그리기)
                false 값 주면 그려진데 덮어씌워 그리기 (잔상)

                더블버퍼링은 도화지 1개가 아닌 2개를 이용하여 그리고 도화지1(그림1) 도화지(그림2)
                를 바꿔치기 하는 방식이라 사실 새로 지우고 그릴 필요가 없어서 false값을 줘도
                바꿔지는 순간 도화지1 도화지2가 바뀌며 기존 그림이 사라지고 또 새로 그리기를 반복
            */

            RECT rect; // 사각형의 정보를 저장할 구조체

            // 윈도우 창의 크기를 받아와서 rect에 저장하는 함수
            GetClientRect(msg.hwnd, &rect);

            // 특정구간의 사격형을 채우는 함수
            FillRect(
                buffer_hdc,
                &rect,  // 채울 범위 지정
                (HBRUSH)GetStockObject(WHITE_BRUSH) // 어느 색으로 채울 것인지 지정
            );  // 맨 처음의 버퍼 화면을 하얀색으로 채워서 초기화하는 역할

        }

        

        /*

       과제 -

       더블버퍼링으로 깜빡이지 않고 색이 들어간 도형을 만들어서 움직여보도록 할 것
       과제 내용 자체는 지난번과 동일하나, 더블버퍼링 적용

       힌트 ) 지금 저희는 WM_PAINT에서 그릴 떄 그냥 Rectangle이나 Ellipse를 사용했는데
       그보다는 FeelRect 같은 다른 함수를 사용하는 것이 충돌이 날 가능성이 더 적을 수 있다

       기존 함수로도 불가능한 건 아님. 단지 인터넷에서 확인 가능한 예제들은 이걸 잘 안 씀

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APIDAY5));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_APIDAY5);
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
    case WM_CREATE:// 창이 처음 생성되었을 떄 가동
    {
        CreateBackPage(hWnd, hInst, &buffer_hdc, &buffer_bitmap); // 더블 버퍼링에 사용할 버퍼 초기화
        break;
    }
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
        Rectangle(buffer_hdc,
            rect_x - 50,  // 사각형의 왼쪽 위 지점의 X좌표
            rect_y - 50,  // 사각형의 왼쪽 위 지점의 Y좌표
            rect_x + 50, // 사각형의 오른쪽 아래 지점의 X좌표
            rect_y + 50  // 사각형의 오른쪽 아래 지점의 Y좌표
        );

        Ellipse(buffer_hdc,
            circle_x - 50,
            circle_y - 50,
            circle_x + 50,
            circle_y + 50
        );

        RECT rect; // 사각형의 정보를 저장할 구조체

        // 윈도우 창의 크기를 받아와서 rect에 저장하는 함수
        GetClientRect(hWnd, &rect);

        // 버퍼의 내용을 메인 hdc에 복사해오는 함수
        BitBlt(
            hdc,
            0, // 복사를 지정할 영역의 왼쪽 위 X좌표
            0, // 복사를 지정할 영역의 왼쪽 위 Y좌표
            rect.right, // 복사를 지정할 영역의 오른쪽 아래 X좌표
            rect.bottom, // 복사를 지정할 영역의 오른쪽 아래 Y좌표
            buffer_hdc, // 복사해올 데이터가 담겨있는 버퍼(화면)
            0,
            0,
            SRCCOPY // 복사하는 방식을 지정. 지금은 그냥 SRCCOPY(소스 완전 복사)만 이용
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
            
        case VK_SHIFT:
            is_pressed_shift = true;
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
        case VK_SHIFT:
            is_pressed_shift = false;
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

void CreateBackPage(HWND hWnd, HINSTANCE hInst, HDC* memDC, HBITMAP* memBitmap) {
    HDC hdc = GetDC(hWnd);

    *memDC = CreateCompatibleDC(hdc);

    RECT rect; // 사각형의 정보를 저장할 구조체

    GetClientRect(hWnd, &rect); // 윈도우창의 크기를 받아 rect에 저장하는 함수

    *memBitmap = CreateCompatibleBitmap( // 비트맵을 새로이 생성하여 할당
        hdc, // 비트맵의 정보를 받아올 hdc
        rect.right, // 비트맵의 좌우 크기
        rect.bottom // 비트맵의 상하 크기
    );

    // 만들어둔 비트맵을 버퍼 화면에 할당
    (HBITMAP)SelectObject(*memDC, *memBitmap);

    // 특정구간의 사격형을 채우는 함수
    FillRect(
        *memDC,
        &rect,  // 채울 범위 지정
        (HBRUSH)GetStockObject(WHITE_BRUSH) // 어느 색으로 채울 것인지 지정
    );  // 맨 처음의 버퍼 화면을 하얀색으로 채워서 초기화하는 역할

    ReleaseDC(hWnd, hdc);
}