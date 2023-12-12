// 04_지뢰찾기.cpp : Defines the entry point for the application.

#include "framework.h"
#include "API_HOMEWORK_2.h"
#include <stdio.h>		// printf 사용
#include <stdlib.h>		// srand, rand 사용
#include <time.h>		// time 함수 사용

#pragma comment(lib, "winmm.lib")

#define MAX_LOADSTRING 100

// *** 앱 만들 떄 필요한 작업(중요!!!)
/*

    1. 더블 버퍼링 가져오기

        // (1) 더블 버퍼링에 이용할 버퍼 생성 (프로그램 끝날 때까지 사용해야하니 전역변수로 선언) - bitblt() 함수를 사용하기 위해 가져와야 하는 라이브러리
            HDC buffer_hdc;
            HBITMAP buffer_bitmap;

        // (2) HDC 버퍼를 사용할 화면 HBITMAP 픽셀을 비트로 바꿔 저장할 선언/정의부 작성

        // 선언부
            void CreateBackPage(HWND hWnd, HINSTANCE hInst, HDC* memDC, HBITMAP* memBitmap);

        // 정의부
            void CreateBackPage(HWND hWnd, HINSTANCE hInst, HDC* memDC, HBITMAP* memBitmap)
            {
                HDC hdc = GetDC(hWnd);

                *memDC = CreateCompatibleDC(hdc); // 버퍼 하나 만들기

                RECT rect; // 사각형의 정보를 저장할 구조체

                // 윈도우 창의 크기를 받아와서 rect에 저장하는 함수
                GetClientRect(hWnd, &rect);

                *memBitmap =
                    CreateCompatibleBitmap(     // 비트맵을 새로이 생성하여 할당
                        hdc,                    // 비트맵 정보를 받아올 hdc
                        rect.right,             // 비트맵의 좌우 크기
                        rect.bottom             // 비트맵의 상하 크기
                    );

                // 만들어둔 비트맵을 버퍼 화면에 할당
                (HBITMAP)SelectObject(*memDC, *memBitmap);


                // 특정 구간의 사각형을 채우는 함수
                FillRect(*memDC,
                    &rect,                                  // 채울 범위 지정
                    (HBRUSH)GetStockObject(WHITE_BRUSH)     // 어느 색으로 채울 것인지 지정
                ); // 맨 처음의 버퍼 화면을 하얀색으로 채워서 초기화하는 역할

                ReleaseDC(hWnd, hdc); // 할당한 hdc(붓) 해제 (delete는 없애는것.. 조금 다른 의미)
            }

    2. 윈도우 창 크기와 관련된 작업 윈도우 창 크기를 저장할 RECT구조체 (방법 1/2 중 선택)

        // 방법1) 만들 윈도우 창의 기본적인 사이즈를 미리 여기서 선언

            RECT window_init_size =
            {
                // 윈도우 창에서의 좌표에서 0은 왼쪽 위를 가리킴
                // 0에서 값이 높아질수록 X좌표는 오른쪽, Y좌표는 아래로 이동

                0,      // left - 사각형의 왼쪽 위 꼭지점의 X좌표
                0,      // top - 사각형의 왼쪽 위 꼭지점의 Y좌표
                640,    // right - 사각형의 오른쪽 아래 꼭지점의 X좌표
                480,    // bottom - 사각형의 오른쪽 아래 꼭지점의 Y좌표

                // 창 크기의 비율은 보통 4:3이나 16:9 로 맞춰서 모니터의 화면비에 가급적 맞추는 걸 권장 (필수는 아님)
            };

        // 방법2) 아예 매크로 사용해서도 가능 (전역 변수 선언하는 공간에서 RECT window_init_size를 위와 같이 고쳐 사용해도 됨)

            #define WINDOWS_SIZE_WIDTH 640
            #define WINDOWS_SIZE_HEIGHT 480

            RECT window_init_size =
            {
                0,
                0,
                WINDOWS_SIZE_WIDTH,
                WINDOWS_SIZE_HEIGHT
            };

    3. 지정한 윈도우 창 크기를 반영 시키는 과정
        BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
        {
            hInst = hInstance; // Store instance handle in our global variable

            // 우리가 작업할 공간을 포함한, 윈도우 창이 실제로 차지하게 되는 크기
                int actual_window_size_x;
                int actual_window_size_y;

                actual_window_size_x = window_init_size.right    // 작업할 창의 가로 크기
                    + GetSystemMetrics(SM_CXFRAME) * 2;          //  창의 좌우 프레임(틀)의 크기, 좌우 각각 하나씩 있으니 *2 (프레임 : 윈도우 창 뜨면 윗변 아랫변 같이 창틀 같은 부분..)


                actual_window_size_y = window_init_size.bottom    // 작업할 창의 가로 크기
                + GetSystemMetrics(SM_CYFRAME) * 2           // 창의 좌우 프레임(틀)의 크기, 좌우 각각 하나씩 있으니 *2 (프레임 : 윈도우 창 뜨면 윗변 아랫변 같이 창틀 같은 부분..)
                + GetSystemMetrics(SM_CYCAPTION)             // 창의 제목 표시줄의 크기
                + GetSystemMetrics(SM_CYMENU);


            // 창 크기를 모니터 사이즈에 맞출거라면 아무 문제 없지만, 우리는 창이 그정도로 큰것을 원치 않는다.
            actual_window_size_y = GetSystemMetrics(SM_CYFULLSCREEN); // 모니터 상하 길리를 그대로 이용



            // 위에서 지정한 사이즈 반영 시키기
                HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT, 0,
                    actual_window_size_x,
                    actual_window_size_y,
                    nullptr, nullptr, hInstance, nullptr);



    4. framework에 헤더 추가
        #include <windowsx.h>       // 마우스 클릭을 했을 때 그 좌표를 기록할 함수를 이용하는데 필요한 라이브러리 (GET_X_LPARAM - 여기서는 마우스 좌표를 가져오기 위해)
        #include <Mmsystem.h>		// 윈도우에서 사용하는 시간관련 헤더 (콘솔의 time 헤더 느낌)

    5. 소스파일에 헤더 추가
        #pragma comment(lib, "winmm.lib")

    6. 마우스 위치를 기록할 POINT 구조체 가져오기
        POINT mouse_dir = // POINT : 좌표 저장하는 구조체
        {
            0,  // 점의 X좌표
            0   // 점의 Y좌표
        };

    7. 더블 버퍼링을 1에서 만들었으니 호출 타이밍을 6번에서 걸어줌
        case WM_CREATE: // 창이 처음 생성되었을 때 가동
        CreateBackPage(hWnd, hInst, &buffer_hdc, &buffer_bitmap); // 더블 버퍼링에 사용할 버퍼 초기화
        break;

    8. 창을 만들 때 더블 버퍼링을 위해 동적 할당했던 버퍼와 비트맵을 창이 꺼질 때 할당 해제

        case WM_DESTROY:
        DeleteObject(buffer_hdc);
        DeleteBitmap(buffer_bitmap);
        PostQuitMessage(0);
        break;

    9. PAINT 부분에 작업 처리

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

*/


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// 더블 버퍼링에 이용할 버퍼 생성 (프로그램 끝날 때까지 사용해야하니 전역변수로 선언) - bitblt() 함수를 사용하기 위해 가져와야 하는 라이브러리
HDC buffer_hdc;
HBITMAP buffer_bitmap;

// 2. 번 작업(윈도우 창 크기 조절)
#define WINDOWS_SIZE_WIDTH 640
#define WINDOWS_SIZE_HEIGHT 480

// 마우스 좌표
int mouse_pos_x = 0;   // 마우스의 X좌표를 저장할 값
int mouse_pos_y = 0;   // 마우스의 Y좌표를 저장할 값

RECT window_init_size =
{
    0,
    0,
    WINDOWS_SIZE_WIDTH,
    WINDOWS_SIZE_HEIGHT
};

// 지뢰찾기 게임판 크기를 여기서 설정
#define MINESWEEPER_X 10
#define MINESWEEPER_Y 10

// 지뢰 갯수
#define MINE_COUNT 7

// 폭탄 설치된 정보를 저장할 변수
char mine_table[MINESWEEPER_Y][MINESWEEPER_X];
// 이차원 배열으로 해도 되기는 하지만
// 삼차원 배열로 만들어서([Y][X][2])
// 이 [2]의 첫번째 칸에 해당 칸의 정보를, 두번쨰 칸에 클릭 여부를 적어두는 게 더 편하긴 함


// 클릭한 위치가 맵의 어디를 건드렸는지 판별하기 위한 변수
int map_x;
int map_y;


// 지뢰찾기의 각 칸의 정보를 저장해둘 이중 배열 저장소
// 이중배열은 무조건 상수로만 선언가능(변수는 바뀔 가능성 있어서 안됨)
// int mine_map[MINESWEEPER_X][MINESWEEPER_Y];

// 창 크기를 기반으로, 각 칸이 차지할 좌우/상하 크기를 미리 정의
int cell_width = window_init_size.right / (MINESWEEPER_X + 1); // + 1 하는 이유는 첫 칸은 띄우려고
int cell_height = window_init_size.bottom / (MINESWEEPER_Y + 1);

bool is_button_clicked = false;
int button_status = 0;
POINT mouse_dir = // POINT : 좌표 저장하는 구조체
{
    0,  // 점의 X좌표
    0   // 점의 Y좌표
};


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void CreateBackPage(HWND hWnd, HINSTANCE hInst, HDC* memDC, HBITMAP* memBitmap);
void CreateMineTable(char mine_table[][MINESWEEPER_X]);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    //현재 시간을 기준으로 난수 설정
    srand((unsigned)time(NULL));

    // 폭탄 설치 정보 구성
    CreateMineTable(mine_table);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_APIHOMEWORK2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APIHOMEWORK2));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APIHOMEWORK2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_APIHOMEWORK2);
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

    // 우리가 작업할 공간을 포함한, 윈도우 창이 실제로 차지하게 되는 크기
    int actual_window_size_x;
    int actual_window_size_y;

    actual_window_size_x = window_init_size.right    // 작업할 창의 가로 크기
        + GetSystemMetrics(SM_CXFRAME) * 2;          //  창의 좌우 프레임(틀)의 크기, 좌우 각각 하나씩 있으니 *2 (프레임 : 윈도우 창 뜨면 윗변 아랫변 같이 창틀 같은 부분..)

    /*
    */
    actual_window_size_y = window_init_size.bottom    // 작업할 창의 세로 크기
        + GetSystemMetrics(SM_CYFRAME) * 2           // 창의 상하 프레임(틀)의 크기, 좌우 각각 하나씩 있으니 *2 (프레임 : 윈도우 창 뜨면 윗변 아랫변 같이 창틀 같은 부분..)
        + GetSystemMetrics(SM_CYCAPTION)             // 창의 제목 표시줄의 크기
        + GetSystemMetrics(SM_CYMENU);

    /*
    actual_window_size_y = GetSystemMetrics(SM_CYFULLSCREEN); // 모니터 상하 길리를 그대로 이용
    창 크기를 모니터 사이즈에 맞출거라면 아무 문제 없지만, 우리는 창이 그정도로 큰것을 원치 않는다.
    */


    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0,
        actual_window_size_x,
        actual_window_size_y,
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
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

WCHAR  text[100] = L""; // 마우스 좌표 확인용

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WCHAR  text[100] = L"";
    switch (message)
    {
    case WM_CREATE: // 창이 처음 생성되었을 때 가동
        CreateBackPage(hWnd, hInst, &buffer_hdc, &buffer_bitmap); // 더블 버퍼링에 사용할 버퍼 초기화
        break;

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
        // 글씨 쓰기
        for (int y = 0; y < MINESWEEPER_Y; y++)
        {
            // 한줄 정보 출력
            for (int x = 0; x < MINESWEEPER_X; x++)
                printf("%c", mine_table[cell_height * y + cell_height][cell_width * x + cell_width]);
            printf("\n");
        }
        printf("\n");
        */


        // 3*3의 격자판(바둑판)을 만들어본다고 가정

        // 1. 각 칸 하나하나를 네모로 그리기

        /*
            2. 칸을 그리는 대신 줄(LineEx)을 그어서 격자를 만들기

                시간상 못했으니 직접 시도해볼 것을 권장.

                속도는 위의 Rect에 비해선 훨씬 빠른데
                MoveToEx를 어떻게 사용하냐에 따라서 코드 자체의 난이도는 조금 높을 수도 있음
                제출까지 한번 시도해보는 것을 권장

        */

        // 테이블의 현재 정보에 맞게 각 칸의 색을 다르게 출력
        HBRUSH whiteBrush, redBrush, grayBrush;
        whiteBrush = GetStockBrush(WHITE_BRUSH); // 흰색
        redBrush = CreateSolidBrush(RGB(255, 0, 0)); // 적색 브러시
        grayBrush = GetStockBrush(GRAY_BRUSH); // 회색 브러시
        // GetStockBrush = 이미 윈도우에서 기본적으로 지정해두고 있는 브러시를 가져오는 것
        // 이걸로 만들 수 있는 브러시는 한정적이라 만능은 아님

        HBRUSH oldBrush;

        for (int i = 0; i < MINESWEEPER_Y; i++)
        {
            for (int j = 0; j < MINESWEEPER_X; j++)
            {
                int is_brush_changed = 0;

                // 지뢰 테이블에 따라 그릴 네모의 배경색을 설정
                switch (mine_table[i][j])
                {
                case '@': // 터진 폭탄이 있는 칸의 배경색을 붉은 색으로 변경
                    oldBrush = (HBRUSH)SelectObject(buffer_hdc, redBrush);
                    is_brush_changed = 1;
                    break;

                case '#': // 눌린 빈칸의 배경색을 회색으로 변경
                case 'A': // 숫자가 있건 없건 배경색은 다 회색이니 회색으로 출력
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                    oldBrush = (HBRUSH)SelectObject(buffer_hdc, grayBrush);
                    is_brush_changed = 2;
                    break;


                    // 흰색 배경
                case '*':
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                default:
                    oldBrush = (HBRUSH)SelectObject(buffer_hdc, whiteBrush);
                    is_brush_changed = 3;
                    break;
                }
                /*
                지뢰 테이블의 값에 따라 출력해야 하는 칸 색의 진리표

                출력할 위치의 값        |     출력해야 할 색
                '*'(안 눌린 폭탄)            흰색 그대로
                '0' ~ '8'(안 눌린 칸)        흰색 그대로
                '@'(터진 폭탄)               붉은색
                '#'(눌린 빈칸)               회색 + 글자는 없음
                'A' ~ 'H'(눌린 숫자칸)       회색 + 글자가 있음

                */

                Rectangle(buffer_hdc,
                    cell_width * j + cell_width / 2,            // 맨 처음 x좌표 빈 부분을 띄우기 위해 cell_width / 2 더해주는것
                    cell_height * i + cell_height / 2,          // 맨 처음 y좌표 빈 부분을 띄우기 위해 cell_height / 2 더해주는것
                    cell_width * (j + 1) + cell_width / 2,
                    cell_height * (i + 1) + cell_height / 2
                );

                // cell_width * j + cell_width / 2 + cell_width * (j + 1) + cell_width / 2
                // = cell_width * j + cell_widht * (j + 1) + cell_width / 2 + cell_width / 2
                // = cell_width * (j + j + 1) + cell_width
                // = cell_width * (2j + 2)
                // = 2 * cell_width * (j + 1)
                // 여기서 2를 나누면 cell_width * (j + 1)

                if (mine_table[i][j] >= 'A' && mine_table[i][j] <= 'H')
                    // 이 칸이 눌린 칸이고 숫자 1~8 중 무언가가 들어있는 칸인지 검사
                {
                    WCHAR click_text[100] = L"";
                    wsprintf(click_text, L"%c", mine_table[map_y][map_x] - 16);
                    TextOutW(buffer_hdc, cell_width * (j + 1), cell_height * (i + 1), text, lstrlen(text));
                }

                if (is_brush_changed > 0) // 배경색을 변경했다면 이에 대한 뒷처리
                {

                    switch (is_brush_changed)
                    {
                    case 1:
                        redBrush = (HBRUSH)SelectObject(buffer_hdc, oldBrush);
                        break;
                    case 2:
                        grayBrush = (HBRUSH)SelectObject(buffer_hdc, oldBrush);
                        break;
                    case 3:
                        whiteBrush = (HBRUSH)SelectObject(buffer_hdc, oldBrush);
                        break;
                    }

                    /*
                    // 변수가 2종밖에 되지 않는다면 코드 1~2줄로 끝나도록 삼항 연산자 이용
                    oldBrush = (HBRUSH)SelectObject(buffer_hdc,
                        (is_brush_changed == 1) ? redBrush : grayBrush);
                        // is_brush_changed가 1이면 redBrush를 사용했던 거니 그것과 재교환
                        // 아니면 gray를 사용한 거니 그 쪽과 재교환
                    */
                }
            }
        }




        /*
        // 지정한 색으로 칠하도록 설정된 붓을 생성
        HBRUSH oldBrush = (HBRUSH)SelectObject(buffer_hdc, myBrush);
        // 기존에 사용하던 붓(이하 브러쉬)을 다른 임시 객체에 저장
        */

        // 붓 사용이 다 끝났으면 기존 붓으로 교체


        RECT rect; // 사각형의 정보를 저장할 구조체

        // 윈도우 창의 크기를 받아와서 rect에 저장하는 함수
        GetClientRect(hWnd, &rect);

        // 더블버퍼의 내용을 메인 hdc에 복사해오는 함수 (메인이 아니라 먼저 버퍼에 그려진다)
        BitBlt(
            hdc,            // (도화지 1)
            0,              // 복사를 지정할 영역의 왼쪽 위 X좌표 (buffer -> main)
            0,              // 복사를 지정할 영역의 왼쪽 위 Y좌표 (buffer -> main)
            rect.right,     // 복사를 지정할 영역의 오른쪽 아래 X좌표
            rect.bottom,    // 복사를 지정할 영역의 오른쪽 아래 Y좌표
            buffer_hdc,     // (도화지 2) 복사해올 데이터가 담겨있는 버퍼(화면)
            0,              // buffer_hdc 내용을 hdc 에 복사해 가는 X좌표 (main -> buffer)
            0,              // buffer_hdc 내용을 hdc 에 복사해 가는 Y좌표 (main -> buffer)
            SRCCOPY         // 복사하는 방식을 지정. 지금은 그냥 SRCCOPY(소스 완전 복사)만 이용
        );

        wsprintf(text, L"x : %d | Y : %d", mouse_pos_x, mouse_pos_y);
        // printf와 비슷하지만, 직접 출력이 아닌 문자열 변수 등에 저장하는 함수
        // 맨 앞의 text가 문자열을 저장해둘 위치



        EndPaint(hWnd, &ps);
    }
    break;

    // 마우스 왼쪽 컨트롤 부분
    case WM_LBUTTONDOWN: // f12로 정보를 보면 각 버튼마다 명령어가 다르게 실행되는 걸 확인 할 수 있다.

        // 마우스 좌표 확인용
        mouse_dir.x = GET_X_LPARAM(lParam);
        mouse_dir.y = GET_Y_LPARAM(lParam);

        if (mouse_dir.x < cell_width / 2                            // 첫번째 셀보다 왼쪽에 있거나      
            || mouse_dir.x > cell_width * 10 + cell_width / 2       // 마지막 셀보다 오른쪽에 있거나 ('+ cell_width / 2'를 하는 이유는 맨 첫 부분 띄어져 있는 부분을 클릭 했을 떄를 제하기 위해)
            || mouse_dir.y <= cell_height / 2                       // 세로 첫번째 셀보다 위에 있거나
            || mouse_dir.y >= cell_height * 10 + cell_height / 2)   // 마지막 셀보다 아래에 있으면
        {
            break;
            // 처리하지 않고 종료
        }

        // 여기에 있던 지역변수 map_x, map_y(현재 마우스로 클릭한 위치)는
        // 전역 변수로 옮기기

        map_x =
            (mouse_dir.x // 마우스 X좌표
                - cell_width / 2) // 게임판 왼쪽의 빈 공간을 계산에서 제하기
            / cell_width; // 남은 값을 그대로 칸으 크기로 나누고, 나머지는 버리고 몫만 취함

        map_y =
            (mouse_dir.y // 마우스 Y좌표
                - cell_height / 2) // 게임판 왼쪽의 빈 공간을 계산에서 제하기
            / cell_height; // 남은 값을 그대로 칸으 크기로 나누고, 나머지는 버리고 몫만 취함

        // 그럼 이제 클릭한 칸에 맞게 해당 칸의 정보를 변경

        /*
        진리표 : 한 작업에서 입력값 혹은 기존값에 따라 결과 처리시 어떤 값이 올 수 있는지
        전부 한 표에 적어서 정리한 표

        지뢰 테이블의 진리표를 한번 작성해보면

        클릭하기 전의 값   |   ----좌클릭--->     | 클릭한 후의 값
            *(42)                                       @(64) + 테이블의 모든 '*'를 골뱅이로 변환
            '0'(48)                                     #(35)
            '1'(49)                                     'A'(65)
            '2'(50)                                     'B'(66)
            '3'(51)                                     'C'(67)
            '4'(52)                                     'D'(68)
            '5'(53)                                     'E'(69)
            '6'(54)                                     'F'(70)
            '7'(55)                                     'G'(71)
            '8'(56)                                     'H'(72)

        */


        switch (mine_table[map_y][map_x])
        {
        case '*': // 폭탄을 클릭했을 경우
            for (int i = 0; i < MINESWEEPER_Y; i++)
                for (int j = 0; j < MINESWEEPER_X; j++) // 테이블 내 모든 칸을 검사해서
                    if (mine_table[i][j] == '*') mine_table[i][j] = '@'; // 모든 폭탄이 있는 칸을 폭발
            break;

        case '0': // 빈 칸을 클릭했을 경우
            mine_table[map_y][map_x] = '#';
            break;

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            mine_table[map_y][map_x] += 16;
            // '1'(49) ~ '8'(56) + 16 = 'A'(65) ~ 'H'(72)로 변환
            break;

        }



        /*
            이제 남은 부분은 지난 시간, 클릭할 때마다 칸의 색이 달라지게 하는 기능을 구현했던 것을 응용해서 지뢰를 클릭했는지, 빈칸을 클릭했는지 판별하는 기능을 만들어보기
            추가로 위에서 만들었던 지뢰판을 초기화하는 과정도 필요. 지뢰의 위치는 랜덤으로 만들면 좋긴 하지만, 시간이 오래 걸리겠다 싶으면 고정된 위치로 해도 됩니다.
        */

        // Invalidate(무효화)함수 : 기존의 화면은 다 썼다, 지정한 부분만큼을 새로 그려라 (true -> 기존 정보를 유지 한 상태로 다른 그림 그리기)
        InvalidateRect(
            hWnd,   // 명령 내릴 창
            NULL,   // 원래는 이 매개변수에다가 사각형 정보(RECT)를 넘겨서 범위 지정, NULL이면 전체를 지정
            false    // 지정한 범위를 새로 그릴 때 기존 화면을 지울까 말까 true(리셋 다시 그리기), false(잔상 남기고 새로그리기)로 결정 --> 여기서는 더블 버퍼를 쓰기 때문에 false로 둔다
        );

        break;

    case WM_DESTROY:
        // 창을 만들 때 더블 버퍼링을 위해 동적 할당했던 버퍼와 비트맵을 창이 꺼질 때 할당 해제
        DeleteObject(buffer_hdc);
        DeleteBitmap(buffer_bitmap);
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

void CreateBackPage(HWND hWnd, HINSTANCE hInst, HDC* memDC, HBITMAP* memBitmap)
{
    HDC hdc = GetDC(hWnd);

    *memDC = CreateCompatibleDC(hdc); // 버퍼 하나 만들기

    RECT rect; // 사각형의 정보를 저장할 구조체

    // 윈도우 창의 크기를 받아와서 rect에 저장하는 함수
    GetClientRect(hWnd, &rect);

    *memBitmap =
        CreateCompatibleBitmap(     // 비트맵을 새로이 생성하여 할당
            hdc,                    // 비트맵 정보를 받아올 hdc
            rect.right,             // 비트맵의 좌우 크기
            rect.bottom             // 비트맵의 상하 크기
        );

    // 만들어둔 비트맵을 버퍼 화면에 할당
    (HBITMAP)SelectObject(*memDC, *memBitmap);


    // 특정 구간의 사각형을 채우는 함수
    FillRect(*memDC,
        &rect,                                  // 채울 범위 지정
        (HBRUSH)GetStockObject(WHITE_BRUSH)     // 어느 색으로 채울 것인지 지정
    ); // 맨 처음의 버퍼 화면을 하얀색으로 채워서 초기화하는 역할

    ReleaseDC(hWnd, hdc); // 할당한 hdc(붓) 해제 (delete는 없애는것.. 조금 다른 의미)
}

void CreateMineTable(char mine_table[][MINESWEEPER_X])
{
    int x, y, mine_count; // mine 정보를 저장할 메모리에 모두 0 채우기

    for (y = 0; y < MINESWEEPER_Y; y++)
        for (x = 0; x < MINESWEEPER_X; x++) 
            mine_table[y][x] = 0;

    // 폭탄을 MINE_COUNT 개 만큼 생성
    for (mine_count = 0; mine_count < MINE_COUNT; mine_count++)
    {
        // 난수 사용하여 폭탄이 위치할 곳 생성
        x = rand() % MINESWEEPER_X;
        y = rand() % MINESWEEPER_Y;

        // 폭탄이 설치된 곳이 아니라면 폭탄 설치하고 이미 설치 됐으면 폭탄수 줄여 다시 배치
        if (mine_table[y][x] == 0) mine_table[y][x] = '*';
        else mine_count--;
    }


    // 빈칸에 폭탄 계수를 체크
    for (y = 0; y < MINESWEEPER_Y; y++)
    {
        for (x = 0; x < MINESWEEPER_X; x++)
        {
            // 폭탄이 아니라면 인접한 위치에 폭탄 몇개 있는지 체크
            if (mine_table[y][x] == 0)
            {
                // 폭탄 갯수 초기화
                mine_count = 0;

                /*
                    현재 위치 (c) 중심으로 총 8 방향의 위치에 폭탄 몇개인지 체크

                    1	2	3
                    4  (c)	5
                    6	7	8
                */

                if ((y - 1) >= 0)
                {
                    // 음수 안나오게 체크
                    // 1 2 3 체크
                    if ((x - 1) >= 0 && mine_table[y - 1][x - 1] == '*') mine_count++;
                    if (mine_table[y - 1][x] == '*') mine_count++;
                    if ((x + 1) < MINESWEEPER_X && mine_table[y - 1][x + 1] == '*') mine_count++;
                }

                // 4, 5 체크
                if ((x - 1) >= 0 && mine_table[y][x - 1] == '*') mine_count++;
                if ((x + 1) < MINESWEEPER_X && mine_table[y][x + 1] == '*') mine_count++;

                // 6, 7, 8 체크 
                if ((y + 1) < MINESWEEPER_Y)
                {
                    // 범위 벗어나지 않게 체크
                    if ((x - 1) >= 0 && mine_table[y + 1][x - 1] == '*') mine_count++;
                    if (mine_table[y + 1][x] == '*') mine_count++;
                    if ((x + 1) < MINESWEEPER_X && mine_table[y + 1][x + 1] == '*') mine_count++;
                }

                // 계산된 폭탄 수를 정수에서 문자로 변경해서 현재 위치에 대입 (ex. 5 면 '5'로 저장)
                mine_table[y][x] = '0' + mine_count;
            }
        }
    }
}
