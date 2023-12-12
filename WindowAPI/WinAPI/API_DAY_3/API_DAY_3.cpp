// API_DAY_3.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "API_DAY_3.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

int mouse_pos_x = 0; // 마우스 x위치를 저장한 값
int mouse_pos_y = 0; // 마우스 y위치를 저장한 값

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
    LoadStringW(hInstance, IDC_APIDAY3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APIDAY3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APIDAY3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_APIDAY3);
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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(
    HWND hWnd,      // 이 명령이 수행될 창의 핸들
    UINT message,   // 이 함수에 전달된 명령
    WPARAM wParam,  // Word Parameter = 단문형 매개변수, 변수 딱 하나만 들어온 데이터
    LPARAM lParam)  // Long Parameter = 장문형 매개변수, 포인터 형식으로 들어온 데이터
    /*
        * 마우스로 wParam, lParam 예시를 들어보면
        * wParam = 마우스 각 버튼의 클릭여부를 한 변수에 몰아서 받는다
        * ex | 이진수로 왼클릭만이면 10, 오른클릭만이면 01, 둘 다 클릭이면 11, 둘 다 안 눌렸으면 00
        * (실제로 이 값인 건 아님)
        * lParam = 마우스의 현재 좌표 같이 변수 하나에 저장하기엔 복잡한 값
        * ex | 마우스의 현재 x,y좌표
    */
{
    WCHAR text[100] = L""; // 문자열을 저장해둘 변수
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
    case WM_PAINT: // 화면을 출력하라는 명령이 들어와야 새로그림
        // 즉, 새로 그리라는 명령이 없으면 어떤 일이 있어도 화면을 새로 그리지 않음
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            MoveToEx(hdc, mouse_pos_x, mouse_pos_y - 50, NULL);
            LineTo(hdc, mouse_pos_x - 50, mouse_pos_y + 50);
            LineTo(hdc, mouse_pos_x + 50, mouse_pos_y + 50);
            LineTo(hdc, mouse_pos_x, mouse_pos_y - 50);

            wsprintf(text, L"X : %d | Y : %d", mouse_pos_x, mouse_pos_y);
            // printf와 비슷하지만, 직접 출력이 아닌 문자열 변수 등에 저장하는 함수
            // 맨 앞의 text가 문자열을 저장해둘 위치

            TextOutW(hdc, mouse_pos_x + 10, mouse_pos_y + 10, text, lstrlen(text));
            // TextOut의 유니코드 판. TextOut은 유니코드 환경일 경우 자동적으로 W로 변환,
            // 아닐 경우 TextOutA(Ascii)로 변환

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_MOUSEMOVE:
        switch (wParam)
        {
        case VK_LBUTTON:
            mouse_pos_x = GET_X_LPARAM(lParam);
            mouse_pos_y = GET_Y_LPARAM(lParam);
            // GET_(?)_LPARAM 함수는 <windowsx.h>를 include해야만 작동하므로 주의!

            // 기존의 화면은 다 썼다, 지정한 부분만큼을 새로 그려라 명령하는 함수
            // 이 함수를 이용하지 않으면 화면이 갱신되지 않음
            InvalidateRect(
                hWnd, // 명령을 내릴 창
                NULL, // 원래는 이 매개변수에 사각형 정보를 넘겨 범위 지정
                true  // 지정한 범위를 새로 그릴 때 기존 화면을 지울까 말까 true, false로 결정 (잔상)
            );

            /*
               // 사각형을 정의하는 구조체 RECT
               typedef struct tagRECT
               {
                   LONG    left; // 왼쪽 위 점의 X좌표
                   LONG    top; // 왼쪽 위 점의 Y좌표
                   LONG    right; // 오른쪽 아래 점의 X좌표
                   LONG    bottom; // 오른쪽 아래 점의 Y좌표
               } RECT
               */
            break;

        case VK_RBUTTON:
            mouse_pos_x = 100;
            mouse_pos_y = 100;
            InvalidateRect(
                hWnd, // 명령을 내릴 창
                NULL, // 원래는 이 매개변수에다가 사각형 정보(RECT)를 넘겨서 범위 지정
                    // NULL이면 창 전체를 지정
                true // 지정한 범위를 새로 그릴 때 기존 화면을 지울까 말까 true, false로 결정
            );

            break;
        // 위 2개 케이스는 각각 좌클릭, 우클릭"만" 되어있을 때 작동
        // 즉, 쌍클릭 중에는 동작하지 않는 것이 정상
        }
        break;

        /*
       *          과제
       *
       * 오늘 실습으로 만든 건 클릭 즉시 반응이 아니라 클릭 후 움직이는 것에만 반응했다
       *
       * 그러면, 클릭하자마자 반응하도록 하려면 어떻게 해야 하는가?
       * -> 반응하도록 만들어올 것, 즉 클릭하자마자 삼각형 위치와 좌표 정보가 바뀌도록 할 것
       *
       * 힌트 : VK가 아닌 WM 단계에서 해결해야 하는 문제
       */
    case WM_LBUTTONDOWN: // f12로 정보를 보면 각 버튼마다 명령어가 다르게 실행되는 걸 확인 할 수 있다.
        mouse_pos_x = GET_X_LPARAM(lParam);
        mouse_pos_y = GET_Y_LPARAM(lParam);


        //Invalidate(무효화)함수 : 기존의 화면은 다 썼다, 지정한 부분만큼을 새로 그려라 (true -> 기존 정보를 유지 한 상태로 다른 그림 그리기)
        InvalidateRect(
            hWnd,   // 명령 내릴 창
            NULL,   // 원래는 이 매개변수에다가 사각형 정보(RECT)를 넘겨서 범위 지정, NULL이면 전체를 지정
            true    // 지정한 범위를 새로 그릴 때 기존 화면을 지울까 말까 true(리셋 다시 그리기), false(잔상 남기고 새로그리기)로 결정
        );

        break;

        /*
        */
        // 1) 마우스 오른 버튼으로 삼각형 원위치시키기
    case WM_RBUTTONDOWN:
        mouse_pos_x = 100;
        mouse_pos_y = 100;

        InvalidateRect(
            hWnd, // 명령을 내릴 창
            NULL, // 원래는 이 매개변수에다가 사각형 정보(RECT)를 넘겨서 범위 지정
            //NULL이면 창 전체를 지정
            true // 지정한 범위를 새로 그릴 때 기존 화면을 지울까 말까 true, false로 결정
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
