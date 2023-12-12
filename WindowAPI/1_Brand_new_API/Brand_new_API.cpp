// Brand_new_API.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Brand_new_API.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // 이 프로그램의 ID(핸들)를 받아오는 매개 변수
                     _In_opt_ HINSTANCE hPrevInstance,  
                     _In_ LPWSTR    lpCmdLine,          // 프로그램 실행 시 추가로 입력한 명령어를 받아오는 매개변수 ex) abc.exe *-windowed* 
                     _In_ int       nCmdShow)           
{
    // 입력 받았던 매개변수를 전처리
    UNREFERENCED_PARAMETER(hPrevInstance); 
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);         // 인스턴스를 통해 프로그램의 제목을 받아오는 함수
    LoadStringW(hInstance, IDC_BRANDNEWAPI, szWindowClass, MAX_LOADSTRING); // 인스턴스를 통해 프로그램의 클래스명을 받아오는 함수
    MyRegisterClass(hInstance);                                             // 인스턴스를 통해 앞으로 생성할 윈도우 창을 기본 설정

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BRANDNEWAPI));

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
    WNDCLASSEXW wcex;   // 윈도우 정보를 기록할 구조체
            
    wcex.cbSize = sizeof(WNDCLASSEX);   // 구조체 전체의 크기를 구조체 안 멤버로 등록

    wcex.style          = CS_HREDRAW | CS_VREDRAW;  //윈도우 창의 스타일
    wcex.lpfnWndProc    = WndProc;                  // 윈도우 프로시저 등록 = 우리가 만들 윈도우 창은 저 함수를 통해 작업
    wcex.cbClsExtra     = 0;                        // 클래스에 할당할 여분 메모리
    wcex.cbWndExtra     = 0;                        // 윈도우 쪽의 여분 메모리
    wcex.hInstance      = hInstance;                // 윈도우 창이 사용할 인스턴스
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BRANDNEWAPI));    // 윈도우 창 제목 표시줄에 표시되는 아이콘
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);           // 윈도우 창 안에서 보여지는 커서
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);                 // 윈도우 창의 기본 배경색을 여기서 설정                
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BRANDNEWAPI);        // 윈도우 창의 메뉴의 이름을 여기서 등록
    wcex.lpszClassName  = szWindowClass;                            // 윈도우 클래스의 이름을 등록 
                                                                    //(만약 여기 등록한 클래스 이름이 돌아가는 윈도우 클래스와 다르면 정상작동 하지않음.)
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
       szWindowClass,       // 새로 만들 클래스 객체의 객체명
       szTitle,             // 새로 만들 창의 이름
       WS_OVERLAPPEDWINDOW, // 윈도우 스타일을 결정하는 플래스
       CW_USEDEFAULT,       // 창의 초기 위치 중 x좌표
       0,                   // 창의 초기 위치 중 y좌표, x좌표가 CW_USEDEFAULT이면 y값은 무시
       CW_USEDEFAULT,       // 창의 초기 좌우 넓이 
       0,                   // 창의 초기 상하 넓이
       nullptr,             // 이 hwnd가 다른 창에서 파생된 자식 창이라면 부모를 기입함.
       nullptr,             // 윈도우에서 사용할 메뉴의 핸들 지정(포커스)
       hInstance,           // 창과 연결할 모듈 인스턴스
       nullptr);            // CREATECONSTRUCT라는 구조체에 이용할 값. 어지간 하면 nullptr 고정

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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
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
