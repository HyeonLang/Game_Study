// DX_VertexUV.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "DX_VertexUV.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

HWND hWnd;
Float2 object_pos;
UINT key_map = 0;
DWORD time_stamp = timeGetTime();
POINT mouse_pos = { 0, 0 };
RECT windows_size = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

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
    LoadStringW(hInstance, IDC_DXVERTEXUV, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DXVERTEXUV));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DXVERTEXUV));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DXVERTEXUV);
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

    AdjustWindowRect(&windows_size, WS_OVERLAPPEDWINDOW, true);
    // 이 함수의 작동방식은 right, bottom만 값을 바꾸는 것이 아니라
    // left, up 역시 바꾸게 되어있음
    // 그 분량만큼을 밑에서 창의 크기를 지정할 때 더해줘야 제대로 된 사이즈가 인식이 됨


    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0,
        windows_size.right - windows_size.left,
        windows_size.bottom - windows_size.top,
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
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler
(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// ImGui에서 정의된 함수이지만 선언은 이루어지지 않음
// 윈도우 프로시저에서의 실행을 위해 쉽게 접근하도록함.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;
    // 윈도우 메시지 발생시 ImGui에서도 프로시저를 실행하도록 한다.

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
    case WM_KEYDOWN:
        if (GetAsyncKeyState(VK_UP) & 0x8000)
            // API 당시에는 키 입력을 위해서
            // 입력된 키가 어떤 키인지를 switch문으로 걸렀었음
            // 이번엔 GetAsyncKeyState라는 함수를 이용해서,
            // 각 조건문마다 특정 키가 눌려있는지의 여부를 반환받고
            // 이를 저 값(해당 키가 눌려있음을 의미하는 값)과 AND 연산을 해서
            // 현재 눌려있는지 판단

            // 기존에는 해당 키가 눌려져있었는지 아닌지를
            // 다른 변수를 눌릴 때/떼일 때마다 관리해야만 했었음
            // 하지만 이 방식을 쓰면 그 방식을 써야만 할 이유는 반쯤 사라짐
        {
            key_map |= 4;
            // UP 키에 대응하는 비트(3번 비트)를 OR 연산으로 비트 플래그에 포함시킨다
        }
        // 이 과정을 각 키들에 대응시키면 OK


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
        // 0x8000 -> 0100 0000 0000 0000
        // 이 값은 Short에서 표기 가능한 제일 커다란 수의 절반(-1)인 2^15
        // GetAsyncKeyState()는 SHORT를 반환하는 함수고
        // 값의 각 비트를 스위치삼아서 정보를 저장하는 비트 마스크로서 사용되는 값이기도 함
        // 그 값들 중 지금 상황에서 유효한 값인 "해당 키가 현재 눌려있는가"를 저장하는 부분만 뗴와서
        // 키가 현재 눌려있는지의 여부를 검사하는 것
        break;

    case WM_KEYUP:
        if (!(GetAsyncKeyState(VK_DOWN) & 0x8000))
        {
            key_map &= ~8;
            // DOWN이 대응하는 4번째 비트(8)를 저장된 플래그에서 이탈시킨다
            // 8(=4번쨰 비트만 1이고 나머지 값은 전부 0인 값)을 비트 반전시켜서
            // 4번 비트만 0으로 만들고
            // 이 값을 비트 플래그에 AND 연산시켜서 다른 값은 보존, 이 값만 확실하게 제거
        }
        if (!(GetAsyncKeyState(VK_UP) & 0x8000))
        {
            key_map &= ~4;
        }
        if (!(GetAsyncKeyState(VK_RIGHT) & 0x8000))
        {
            key_map &= ~2;
        }
        if (!(GetAsyncKeyState(VK_LEFT) & 0x8000))
        {
            key_map &= ~1;
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
