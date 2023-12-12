// API_HOMWORK.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

/*
    기존에 사용 했던 것 중에 사용 예정인 것

    1. 더블버퍼링 : bitblt() 함수를 이용하기 위한 라이브러리 및 더블버퍼링 관련 함수 및 전역변수
    2. 윈도우 창 크기와 관련된 작업을 위한 RECT 구조체
    3. 마우스 위치를 기록할 POINT 구조체와 마우스 클릭을 했을 때 그 좌표를 기록할 함수를 이용하는데 필요한 라이브러리를 가져오기
       => <windowsx.h> <- GET_X(or Y)_LPARAM() 함수를 이용하기 위해 필요
*/

#include "framework.h"
#include "API_HOMWORK.h"
#pragma comment(lib, "winmm.lib") // 라이브러리(lib)에 속하는 종류의 "파일명"을 불러오라는 전처리기
// + 프레임워크에서 해당하는 헤더도 가져와 이 쪽의 헤더에 추가
// 이 경우는 Mmsystem.h

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


// 더블 버퍼링에 이용할 버퍼 생성
HDC buffer_hdc;
HBITMAP buffer_bitmap;

// 만들 창의 기본적인 사이즈를 선언
#define WINDOWS_SIZE_WIDTH 640
#define WINDOWS_SIZE_HEIGHT 480

// 지뢰찾기 게임판의 크기를 설정
#define MINESWEEPER_X 10
#define MINESWEEPER_Y 10



RECT window_init_size = {
    // 윈도우 창에서의 0은 왼쪽 위를 가리킴
    0,      // left 사각형의 왼쪽 위 꼭지점 x좌표
    0,      // top 사각형의 왼쪽 위 꼭지점 y좌표
    WINDOWS_SIZE_WIDTH,    // right 사각형의 오른쪽 아래 꼭지점 x좌표
    WINDOWS_SIZE_HEIGHT,    // bottom 사각형의 오른쪽 아래 꼭지점 y좌표
};

// 창의 크기를 기반으로, 각 칸이 차지할 좌우 상하 크기를 미리 정의
int cell_width = window_init_size.right / (MINESWEEPER_X + 1);
int cell_height = window_init_size.bottom / (MINESWEEPER_Y + 1);

// 지뢰찾기 각 칸의 정보를 저장할 저장소
int mine_map[MINESWEEPER_X][MINESWEEPER_Y];

POINT mouse_dir = { // 마우스의 좌표를 저장할 포인트 구조체
    0,  // 점의 x좌표
    0   // 점의 y좌표
};


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_APIHOMWORK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APIHOMWORK));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APIHOMWORK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_APIHOMWORK);
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

   // 작업할 공간을 포함한 윈도우 창이 실제로 차지하게 되는 크기
   int actual_window_size_x;
   int actual_window_size_y;

   actual_window_size_x = window_init_size.right    // 작업할 창의 크기 
       + GetSystemMetrics(SM_CXFRAME) * 2;  // 창의 좌우 프레임의 크기, 좌 우 각각 하나이므로 *2
   
   actual_window_size_y = window_init_size.bottom    // 작업할 창의 크기 
       + GetSystemMetrics(SM_CYFRAME) * 2   // 창의 좌우 프레임의 크기, 상 하 각각 하나이므로 *2
       + GetSystemMetrics(SM_CYCAPTION)     // 창의 제목 표시줄 크기
       + GetSystemMetrics(SM_CYMENU);       // 창의 각 도구 모음 한줄 크기
   

   //actual_window_size_y = GetSystemMetrics(SM_CYFULLSCREEN); // 모니터 상하의 크기를 그대로 이용
   // 창 크기를 모니터 사이즈에 맞출 경우


   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT,
       0, 
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
    case WM_CREATE: // 창이 처음 생성되었을 떄 가동
        CreateBackPage(hWnd, hInst, &buffer_hdc, &buffer_bitmap);
        // 더블 버퍼링에 사용할 버퍼 초기화
        break;

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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            // m * n 격자판 만들기
             
            // 1. 각 칸을 네모로 그리기
           
            for (int i = 0; i < MINESWEEPER_X; i++) {
                for (int j = 0; j < MINESWEEPER_Y; j++) {
                    Rectangle(
                        buffer_hdc,
                        cell_width * i + cell_width / 2,
                        cell_height * j + cell_height / 2,
                        cell_width * (i + 1) + cell_width / 2,
                        cell_height * (j + 1) + cell_height / 2
                    );
                }
            }

            // 2. 칸을 그리는 대신 줄을 그어 (LineEx) 격자 만들기
            // 속도가 더 빠르지만 MoveToEx 사용레 따라 코드 난이도가 높을 수 있음



            RECT rect; // 사각형의 정보를 저장할 구조체

            // 윈도우 창의 크기를 받아와서 rect에 저장하는 함수
            GetClientRect(hWnd, &rect);

            // 버퍼의 내용을 메인 hdc에 복사해오는 함수
            BitBlt(
                hdc, // 복사를 해서 실제로 출력할 화면을 가리키는 hdc
                0, // 복사를 지정할 영역의 왼쪽 위 X좌표 (buffer -> main)
                0, // 복사를 지정할 영역의 왼쪽 위 Y좌표 (buffer -> main)
                rect.right, // 복사를 지정할 영역의 오른쪽 아래 X좌표
                rect.bottom, // 복사를 지정할 영역의 오른쪽 아래 Y좌표
                buffer_hdc, // 복사해올 데이터가 담겨있는 버퍼(화면)
                0,  // 복사를 지정할 영역의 왼쪽 위 X좌표 (main -> buffer)
                0,  // 복사를 지정할 영역의 왼쪽 위 Y좌표 (main -> buffer)
                SRCCOPY // 복사하는 방식을 지정. 지금은 그냥 SRCCOPY(소스 완전 복사)만 이용
            );


            EndPaint(hWnd, &ps);
        }
        break;

    case WM_LBUTTONDOWN:    // 왼클릭이 되었을 때

        mouse_dir.x = GET_X_LPARAM(lParam);
        mouse_dir.y = GET_Y_LPARAM(lParam);

        if (mouse_dir.x < cell_width / 2                                     // 가로 첫 셀 보다 왼쪽
            || mouse_dir.x > cell_width * MINESWEEPER_X + cell_width / 2     // 가로 마지막 셀보다 오른쪽
            || mouse_dir.y < cell_height / 2                                 // 세로 첫 셀 보다 위쪽
            || mouse_dir.y > cell_height * MINESWEEPER_Y + cell_height / 2)  // 세로 마지막 셀보다 아래
        {
            break;  // 처리 하지 않는다.
        }

        // 맵 어디를 클릭했는지 판단 변수
        int map_x;
        int map_y;

        map_x = (mouse_dir.x - cell_width / 2)  // 마우스 x좌표 - 맵 왼쪽 여백
            / cell_width;                       //  / 셀의 크기 = 셀의 가로 번호

        map_y = (mouse_dir.y - cell_height / 2)  // 마우스 y좌표 - 맵 위쪽 여백
            / cell_height;                       //  / 셀의 크기 = 셀의 세로 번호

       // 이제 남은 부분은 지난 시간, 클릭할 때마다 칸의 색이 달라지게 하는 기능을 구현했던 것을
       // 응용해서 지뢰를 클릭했는지, 빈 칸을 클릭했는지 판별하는 기능을 만들어보기

       // 추가로 위에서 만들었던 지뢰판을 초기화하는 과정도 필요
       // 지뢰의 위치는 랜덤으로 만들면 좋긴 하지만, 시간이 오래 걸리겠다 싶으면 고정된 위치로 해도 됩니다


        //Invalidate(무효화)함수 : 기존의 화면은 다 썼다, 지정한 부분만큼을 새로 그려라 (true -> 기존 정보를 유지 한 상태로 다른 그림 그리기)
        InvalidateRect(
            hWnd,   // 명령 내릴 창
            NULL,   // 원래는 이 매개변수에다가 사각형 정보(RECT)를 넘겨서 범위 지정, NULL이면 전체를 지정
            false    // 지정한 범위를 새로 그릴 때 기존 화면을 지울까 말까 true(리셋 다시 그리기), false(잔상 남기고 새로그리기)로 결정
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