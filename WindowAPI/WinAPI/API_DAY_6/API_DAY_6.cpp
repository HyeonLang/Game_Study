// API_DAY_6.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "API_DAY_6.h"
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
RECT window_init_size = {
    // 윈도우 창에서의 0은 왼쪽 위를 가리킴
    0,      // left 사각형의 왼쪽 위 꼭지점 x좌표
    0,      // top 사각형의 왼쪽 위 꼭지점 y좌표
    640,    // right 사각형의 오른쪽 아래 꼭지점 x좌표
    480,    // bottom 사각형의 오른쪽 아래 꼭지점 y좌표
};  

bool is_button_clicked = false;
int button_status = 0;
POINT mouse_dir = { // 마우스의 좌표를 저장할 포인트 구조체
    0,  // 점의 x좌표
    0   // 점의 y좌표
};

RECT switch_rect = {    // 스위치의 범위를 지정할 RECT 객체
     window_init_size.right / 2 - 30,  // 사각형의 왼쪽 위 지점의 X좌표
     window_init_size.bottom / 2 - 30,  // 사각형의 왼쪽 위 지점의 Y좌표
     window_init_size.right / 2 + 30, // 사각형의 오른쪽 아래 지점의 X좌표
     window_init_size.bottom / 2 + 30  // 사각형의 오른쪽 아래 지점의 Y좌표
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
    LoadStringW(hInstance, IDC_APIDAY6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APIDAY6));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APIDAY6));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_APIDAY6);
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

   HWND hWnd = CreateWindowW(
       szWindowClass, 
       szTitle,
       WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 
       0,
       window_init_size.right,   // 창의 크기를 결정하는 부분 좌우
       window_init_size.bottom,  // 상하
       nullptr,
       nullptr, 
       hInstance,
       nullptr);

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

            HBRUSH myBrush;
            if (is_button_clicked == false)
                myBrush = CreateSolidBrush(RGB(173, 255, 47));
            else
            {
                switch (button_status)
                {
                case 1:
                    myBrush = CreateSolidBrush(RGB(255, 0, 0));
                    break;
                case 2:
                    myBrush = CreateSolidBrush(RGB(0, 255, 0));
                    break;
                case 0:

                default:
                    myBrush = CreateSolidBrush(RGB(0, 0, 255));
                    break;
                }
            }

            // 지정한 색으로 칠하도록 설정된 붓을 생성
            HBRUSH oldBrush = (HBRUSH)SelectObject(buffer_hdc, myBrush);
            // 기존에 사용하던 붓(이하 브러쉬)을 다른 임시 객체에 저장

             // 사각형 그리기
            Rectangle(buffer_hdc,
                switch_rect.left, // 사각형의 왼쪽 위 지점의 X좌표
                switch_rect.top, // 사각형의 왼쪽 위 지점의 Y좌표
                switch_rect.right, // 사각형의 오른쪽 아래 지점의 X좌표
                switch_rect.bottom // 사각형의 오른쪽 아래 지점의 Y좌표
            );

            // 붓 사용이 다 끝났으면 기존 붓으로 교체
            myBrush = (HBRUSH)SelectObject(buffer_hdc, oldBrush);

            DeleteObject(myBrush);

            RECT rect; // 사각형의 정보를 저장할 구조체

            // 윈도우 창의 크기를 받아와서 rect에 저장하는 함수
            GetClientRect(hWnd, &rect);

            // 버퍼의 내용을 메인 hdc에 복사해오는 함수
            BitBlt(
                hdc, // 복사를 해서 실제로 출력할 화면을 가리키는 hdc
                0, // 복사를 지정할 영역의 왼쪽 위 X좌표
                0, // 복사를 지정할 영역의 왼쪽 위 Y좌표
                rect.right, // 복사를 지정할 영역의 오른쪽 아래 X좌표
                rect.bottom, // 복사를 지정할 영역의 오른쪽 아래 Y좌표
                buffer_hdc, // 복사해올 데이터가 담겨있는 버퍼(화면)
                0,
                0,
                SRCCOPY // 복사하는 방식을 지정. 지금은 그냥 SRCCOPY(소스 완전 복사)만 이용
            );


            /*
            과제 :

            지뢰찾기 만들기

            모눈종이처럼 생긴 판이 있고, 모든 판은 클릭이 가능
            이 중에서 일부 칸에는 지뢰가 있고
            지뢰를 클릭하면 게임에서 짐

            칸의 개수와 지뢰의 개수는 게임 난이도에 따라 달라지는데,
            이에 대해선 자율적으로 정해도 무방

            1. 지뢰찾기 게임판을 만들기
            각 칸은 아직 클릭하지 않음 & 클릭했고 지뢰가 없음 & 클릭했고 지뢰가 있음 최소 3가지 형태 보유
            지뢰찾기 판을 랜덤으로 만들 필요는 딱히 없음, 지뢰찾기의 외형만 얼추 구현하면 됨

            2. 클리어와 게임오버 자체는 구현하지 않아도 됩니다만
            최소한 게임오버, 즉 지뢰가 클릭됐을 떄 다른 지뢰가 전부 표기되는 사양까지는 구현해야 함

            ___ 이하는 추가 도전과제 ___

            3. 빈 칸은 인접한 칸(대각선을 포함)에 지뢰가 몇 개 있는지 표시하는 기능을 구현
            색으로 할 필요는 없고 그냥 텍스트만 출력하는 식으로 해도 무방

            4. 아직 클릭하지 않은 칸에 우클릭으로 깃발을 꽂는 기능도 구현
            깃발을 꽂은 칸은 좌클릭해도 눌리지 않습니다

            5. 여기서부터는 실제 지뢰찾기를 최대한 구현해보기

            */

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_LBUTTONDOWN:

        mouse_dir.x = GET_X_LPARAM(lParam);
        mouse_dir.y = GET_Y_LPARAM(lParam);

        // 마우스의 클릭시 위치가 스위치 내부이면
        if (mouse_dir.x >= switch_rect.left && mouse_dir.x <= switch_rect.right
            && mouse_dir.y <= switch_rect.bottom && mouse_dir.y >= switch_rect.top)
        {
            is_button_clicked = true;
            button_status++;

            if (button_status == 3) 
                button_status = 0;
        }
        else
            is_button_clicked = false;

        //Invalidate(무효화)함수 : 기존의 화면은 다 썼다, 지정한 부분만큼을 새로 그려라 (true -> 기존 정보를 유지 한 상태로 다른 그림 그리기)
        InvalidateRect(
            hWnd,   // 명령 내릴 창
            NULL,   // 원래는 이 매개변수에다가 사각형 정보(RECT)를 넘겨서 범위 지정, NULL이면 전체를 지정
            false    // 지정한 범위를 새로 그릴 때 기존 화면을 지울까 말까 true(리셋 다시 그리기), false(잔상 남기고 새로그리기)로 결정
        );

        break;

    case WM_LBUTTONUP:

        is_button_clicked = false;
        InvalidateRect(
            hWnd,   // 명령 내릴 창
            NULL,   // 원래는 이 매개변수에다가 사각형 정보(RECT)를 넘겨서 범위 지정, NULL이면 전체를 지정
            false    // 지정한 범위를 새로 그릴 때 기존 화면을 지울까 말까 true(리셋 다시 그리기), false(잔상 남기고 새로그리기)로 결정
        );
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