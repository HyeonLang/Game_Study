// WindowsProject1.cpp : Defines the entry point for the application.
//


/*
    stack�� ����Ͽ� undo, redo ��� ����


*/

/*
    Win API
    - Windows Application Program Interface
    - �����츦 �����ϰ�, ǥ���ϴµ� ����ϴ� �Լ��� ����

    Windows : �ü��
    API : �ü���� �����ϴ� �������α׷��� ��������� �Լ��� ����
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
    - �ü�� ���ο� �ִ� ���ҽ�(�ڿ�)�� �ּҸ� ������ ġȯ�� ��
    - �ڵ� ���̺��� �ڵ�� ���ҽ��� �ּҰ� �����ȴ�.

    Resource : ���� �ϵ���� ��ġ �Ǵ� ������ġ(�޸�, �ϵ� ��)�� ����ִ� ������ �ڷ�

    Instance Handle : �����쿡�� ���� �������� ���μ����� �ڵ��� ����Ű�� ��
*/
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // ���α׷��� �ڵ� �ν��Ͻ�     
                     _In_opt_ HINSTANCE hPrevInstance,  // ������ ����� �ڵ� �ν��Ͻ� 
                     _In_ LPWSTR    lpCmdLine,          // ��������� �Է� �� ���α׷� �μ� - ������ �� ���α׷��� �ʱ⼳�� ���� ����
                     _In_ int       nCmdShow)           // ���α׷��� ���۵� �� ����(�ּ�ȭ, ���� ���� ���� ��)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    // â�� �ʱ�ȭ���ְ� �������ִ� �κ�
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    HDC hdc = GetDC(g_hWnd); // ���� DC�� �޴´�.
    g_hDC = CreateCompatibleDC(hdc); // ���� DC�� ����Ͽ� �� ���۷� ����� DC ����
    // ��Ʈ�� : �ȼ� �̹����� �����ϴ� �������� �Ǵ� �޸� ���� ���
    HBITMAP bit_map = (HBITMAP)(CreateCompatibleBitmap)(hdc, WINSIZE_X, WINSIZE_Y); // ������ ��Ʈ�� ����
    SelectObject(g_hDC, bit_map); // �� ���� DC�� ������ ��Ʈ�� ��ü�� ��������ش�.

    main_game = new MainGame;
    main_game->Init();

    // Main message loop:
    //while (GetMessage(&msg, nullptr, 0, 0)) // GetMessage : �޽��� ť���� �޽����� �д´�.
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg); // �޽����� ���� �� �ִ� ���·� ����  
    //        DispatchMessage(&msg);  // �޽����� �Ű�(�޽��� ó�� �Լ��� �����ش�.)
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
    // �������� ������ �����ϴ� ����ü
    // â�� ������� ����������� ���ؼ� �ۼ��Ѵ�.
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX); // ����ü�� ũ�� ������ �ִ´�.

    // CS_HREDRAW | CS_VREDRAW : ����, ���� ũ�� ����� â�� �ٽ� �׸���.
    wcex.style          = CS_HREDRAW | CS_VREDRAW;                                      // ������ ��Ÿ��   
    wcex.lpfnWndProc    = WndProc;                                                      // �޽��� ó�� �Լ� ����
    wcex.cbClsExtra     = 0;                                                            // Ŭ���� ���� �޸�
    wcex.cbWndExtra     = 0;                                                            // ������ ���� �޸�
    wcex.hInstance      = hInstance;                                                    // �ν��Ͻ�
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));    // â�� ������
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);                               // ���콺 Ŀ��
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);                                     // ����
    wcex.lpszMenuName   = NULL;                        // �޴��̸�(NULL�Ͻ� �޴� ����)
    wcex.lpszClassName  = szWindowClass;                                                // Ŭ���� �̸�
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));         // ���� ������

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

   // ȭ�� �ػ� �ޱ�
   int resolution_x = GetSystemMetrics(SM_CXSCREEN);
   int resolution_y = GetSystemMetrics(SM_CYSCREEN);

   // â ȭ�� �߾� ��ġ ���
   int win_pos_x = resolution_x / 2 - WINSIZE_X / 2;
   int win_pos_y = resolution_y / 2 - WINSIZE_Y / 2;

   HWND hWnd = CreateWindowW(
       szWindowClass,       // ������ Ŭ������ �̸�
       szTitle,             // Ÿ��Ʋ���� �̸�
       WS_OVERLAPPEDWINDOW, // ������ ��Ÿ��
       win_pos_x,           // ������ ȭ�� ��ǥ X : ������ �� â�� �����ġ���� ��������
       win_pos_y,           // ������ ȭ�� ��ǥ Y
       WINSIZE_X,           // ������ ���� ������
       WINSIZE_Y,           // ������ ���� ������
       nullptr,             // �θ� ������
       nullptr,             // �޴� �ڵ�
       hInstance,           // �ν��Ͻ� ����
       nullptr              // �ڽ� �����츦 �����ϸ� ����, ���ٸ� NULL
   );

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   {
       // ���� ������ ũ�� �޴´�.
       RECT rt = { win_pos_x, win_pos_y, win_pos_x + WINSIZE_X, win_pos_y + WINSIZE_Y };

       // ���ϴ� �۾� ������ ũ��, ��Ÿ�ϰ�, �޴��� ���θ� �ѱ��
       // ���ϴ� �۾������� �´� ������ ũ�⸦ ����� rt�� �־��ش�.
       AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

       // �������� ��ġ, ũ�⸦ �����Ѵ�.
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
    - �޽��� ó�� �Լ�
    - Win API�� �޽��� ��� ���α׷����̴�.(�����Ǵ� �޽����� ó���Ѵ�.)
    - �޽����� ��� �Ŵ��� �޽��� ť�� �����Ѵ�. -> �������� ���� �޽����� �տ� �޽�����
    ó���ɶ����� ������ �� �� ���� ������.
    - api�� ������ ó���ϱ⿡�� �����⿡ �⺻���� â����, ���콺 ó�� �뵵 ������ ����Ѵ�.
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

    case WM_CREATE: // â�� ������ �� 1�� ȣ��Ǵ� �޽���
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
