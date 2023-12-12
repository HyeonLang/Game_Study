// Brand_new_AIP.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Drawing.h"

#pragma comment(lib, "Msimg32.lib")
// GradientFill

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    // 지금 이 프로그램의 ID(=핸들)를 받아오는 매개 변수
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    // 프로그램 실행 시 추가로 입력한 명령어를 받아오는 매개 변수
    // ex| abc.exe -windowed <- 여기서 -windowed가 lpCmdLine에 저장
    _In_ int       nCmdShow)
{
    // 입력받았던 매개 변수를 전처리
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    // 인스턴스를 통해 프로그램의 제목을 받아오는 함수
    LoadStringW(hInstance, IDC_DRAWING, szWindowClass, MAX_LOADSTRING);
    // 인스턴스를 통해 프로그램의 클래스명을 받아오는 함수
    MyRegisterClass(hInstance);
    // 인스턴스를 통해 앞으로 생성할 윈도우 창을 기본 설정

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAWING));

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
    // 윈도우 정보를 기록해둘 구조체

    wcex.cbSize = sizeof(WNDCLASSEX);
    // 구조체 전체의 크기를 구조체 안에 멤버로서 등록

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    // 윈도우 창의 스타일
    wcex.lpfnWndProc = WndProc;
    // 윈도우 프로시저 등록 = 우리가 만들 윈도우 창은 저 함수를 통해 작업을 하겠다
    wcex.cbClsExtra = 0;
    // 클래스에 할당할 여분 메모리(보통 여러 개를 켜먼 메모리 분배가 잘 안 되므로 이렇게 명시해 막음)
    wcex.cbWndExtra = 0;
    // 윈도우 쪽의 여분 메모리
    wcex.hInstance = hInstance;
    // 윈도우 창이 사용할 인스턴스
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAWING));
    // 만들 창이 사용할 기본 아이콘
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    // 윈도우 창 안에서 보여주는 커서를 여기서 설정
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    // 윈도우 창의 기본 배경색을 여기서 설정
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DRAWING);
    // 윈도우 창의 메뉴의 이름을 여기에 등록
    wcex.lpszClassName = szWindowClass;
    // 윈도우 클래스의 이름을 등록
    // 만약 여기 등록한 클래스 이름이 이 프로그램이 돌아가는 윈도우 클래스와 다르면 정상작동을 안 함
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    // 만들 창이 사용할 소형 아이콘
    // 없을 경우(nullptr) 기본 아이콘을 적절히 변형해 사용

    return RegisterClassExW(&wcex);
    // 위에서 설정한 윈도우 클래스 정보를 전체 프로그램에 등록
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

    HWND hWnd =
        CreateWindowW(
            szWindowClass,           // 새로이 만들 클래스 객체의 객체명
            szTitle,                 // 새로이 만들 창의 이름
            WS_OVERLAPPEDWINDOW,     // 윈도우 스타일을 결정하는 플래그
            CW_USEDEFAULT,                    // 창의 초기 위치 중 X좌표 
            0,                     // 창의 초기 위치 중 Y좌표
            CW_USEDEFAULT,           // 창의 초기 좌우 너비
            0,                     // 창의 초기 상하 높이
            nullptr,                 // 만약 만들어지는 창이 다른 창에서 파생된 자식 창이라면, 여기다가 부모를 기입해준다
            nullptr,                 // 윈도우에서 사용할 메뉴의 핸들을 지정
            hInstance,               // 창과 연결할 모듈 인스턴스
            nullptr                  // CREATECONSTRUCT라는 구조체에 이용할 값. 어지간하면 nullptr 고정
        );

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
    case WM_PAINT: // 윈도우 창의 화면에서 그림이나 문자 등을 띄워주는 작업을 하는 영역
    {
        PAINTSTRUCT ps; // 윈도우 창에 그릴 캔버스를 한 장 준비한다
        HDC hdc = BeginPaint(hWnd, &ps); // 그 캔버스에 그릴 사람
        // TODO: Add any drawing code that uses hdc here...



        TextOut(hdc, // 그림을 그릴 사람이 누구인가를 명시
            100, // 글씨를 표시할 X좌표
            100, // 글씨를 표시할 Y좌표
            L"다시 한 번 Hello, World!", // 우리가 출력할 문자열
            wcslen(L"다시 한 번 Hello, World!") // 출력할 문자열의 크기
        );

        const TCHAR* new_string = L"또 한번 우려먹는 Hello, World!";

        SetTextColor(hdc,   // 그림을 그릴 사람
            RGB(200, 100, 0) // 사람이 그리고 싶은 글씨의 색 설정
        );
        // RGB = Red, Green, Blue 세가지 빛의 삼원색
        // 적색, 녹색, 청색 3개 색의 비율을 통해 색을 표기
        // 그림판 -> 색 편집을 통해 색 비율 직접 확인 가능
        TextOut(hdc, 100, 200, new_string, wcslen(new_string));


        // https://www.rapidtables.org/ko/convert/color/index.html
        // 색상표에서 찾은 색의 16진수 코드를 위 사이트의 변환기를 통해 쉽게 변환


        HBRUSH myBrush = CreateSolidBrush(RGB(173, 255, 47));
        // 지정한 색으로 칠하도록 설정된 붓을 생성
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
        // 기존에 사용하던 붓(이하 브러쉬)을 다른 임시 객체에 저장


        // 사각형 그리기
        Rectangle(hdc,
            550,  // 사각형의 왼쪽 위 지점의 X좌표
            50,  // 사각형의 왼쪽 위 지점의 Y좌표
            950, // 사각형의 오른쪽 아래 지점의 X좌표
            400  // 사각형의 오른쪽 아래 지점의 Y좌표
        );

        // 붓 사용이 다 끝났으면 기존 붓으로 교체
        myBrush = (HBRUSH)SelectObject(hdc, oldBrush);

        /*
        // 사용이 끝난 붓은 할당 해제
        DeleteObject(myBrush);

        밑에서 다시 사용할 거라 아직은 할당 해제하지 않았음
        */

        // 투명한 사각형 만들기
        HBRUSH clearBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        // 윈도우에서 기본적으로 마련해준 브러시들 중 명시한 것을 가져오라는 함수
        // https://learn.microsoft.com/ko-kr/windows/win32/api/wingdi/nf-wingdi-getstockobject
        // 위 주소에서 다른 브러시가 무엇이 있는지 확인 가능
        oldBrush = (HBRUSH)SelectObject(hdc, clearBrush);

        // 사각형의 테두리 색 설정
        HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
        HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

        // 사각형 그리기
        Rectangle(hdc,
            50,  // 사각형의 왼쪽 위 지점의 X좌표
            50,  // 사각형의 왼쪽 위 지점의 Y좌표
            400, // 사각형의 오른쪽 아래 지점의 X좌표
            400  // 사각형의 오른쪽 아래 지점의 Y좌표
        );

        //원(타원) 그리기
        Ellipse(hdc,
            550,  // 타원의 왼쪽 위 지점의 X좌표
            50,  // 타원의 왼쪽 위 지점의 Y좌표
            950, // 타원의 오른쪽 아래 지점의 X좌표
            400  // 타원의 오른쪽 아래 지점의 Y좌표
        );


        // 붓 사용이 다 끝났으면 기존 붓으로 교체
        clearBrush = (HBRUSH)SelectObject(hdc, oldBrush);
        myPen = (HPEN)SelectObject(hdc, oldPen);

        // 사용이 끝난 붓은 할당 해제
        DeleteObject(clearBrush);
        // 펜도 할당해제
        DeleteObject(myPen);


        /*

        과제 : 삼각형은 어떻게 그려야 할까?
        = API에 삼각형을 그리는 함수는 없습니다.
        따라서 삼각형을 그리려면 선 3개를 직접 그어야 그릴 수 있음

        MoveToEx(), LineTo()라는 함수를 이용해 그림

        이걸 조사하여, 삼각형 혹은 다른 도형을 그려오기

        추가 ) 만약 완성했다면 이 도형 안에 색을 채울 수 있는지도 조사

        */

        // 해법 1 : BeginPath(), EndPath(), StrokeAndFillPath() 이용
        oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
        // 위에서 사용했던 myBrush 재활용

        BeginPath(hdc); // 여기서부터 채워야 할 영역을 지정한다 선언
        MoveToEx(hdc, 450, 450, NULL);
        LineTo(hdc, 550, 600);
        LineTo(hdc, 350, 600);
        LineTo(hdc, 450, 450);
        EndPath(hdc); // 여기까지가 채워야 할 영역이라 선언
        StrokeAndFillPath(hdc); // 외곽선을 그리고 내부를 채우라고 선언

        myBrush = (HBRUSH)SelectObject(hdc, oldBrush);
        // 사용이 끝난 붓을 초기 붓으로 교체

        // 강의 도중 이 방법이 안 됐던 건 사실 브러쉬를 투명 브러쉬를 써서 안 된 것처럼 보였던 것이지
        // 실제로는 문제없이 되고 있었음


        // 사용이 끝난 붓은 할당 해제
        DeleteObject(myBrush);


        // 2. 비트맵을 이용해 각 정점의 정보를 정의 후 이용
        // 이 방법은 DX와 비슷한 방식

        // 이하의 내용은 다음 주소에서 확인 가능
        // https://learn.microsoft.com/ko-kr/windows/win32/gdi/drawing-a-shaded-triangle
        TRIVERTEX vertex[3]; // 그릴 삼각형 각각의 정점에 대한 정보를 저장

        vertex[0].x = 150; // 정점 0번의 X좌표
        vertex[0].y = 400; // 정점 0번의 Y좌표
        // 이 밑의 3개는 이 정점의 RGB
        vertex[0].Red = 0xff00; // 정점의 RGB 색 정보 중 붉은색
        vertex[0].Green = 0x8000; // 정점의 RGB 색 정보 중 초록색
        vertex[0].Blue = 0x0000; // 정점의 RGB 색 정보 중 파란색
        vertex[0].Alpha = 0x0000; // 정점의 알파값

        vertex[1].x = 0;
        vertex[1].y = 550;
        vertex[1].Red = 0x9000;
        vertex[1].Green = 0x0000;
        vertex[1].Blue = 0x9000;
        vertex[1].Alpha = 0x0000;

        vertex[2].x = 300;
        vertex[2].y = 550;
        vertex[2].Red = 0x9000;
        vertex[2].Green = 0x0000;
        vertex[2].Blue = 0x9000;
        vertex[2].Alpha = 0x0000;

        // Create a GRADIENT_TRIANGLE structure that
        // references the TRIVERTEX vertices.
        GRADIENT_TRIANGLE gTriangle; // 음영처리된 삼각형이 사용할 정점의 인덱스를 저장하는 고유 멤버
        gTriangle.Vertex1 = 0; // 1번 멤버엔 인덱스 0을
        gTriangle.Vertex2 = 1; // 2번 멤버엔 인덱스 1
        gTriangle.Vertex3 = 2; // 3번엔 2

        // Draw a shaded triangle.
        GradientFill(
            hdc,
            vertex, // 사용할 정점의 정보가 저장된 위치
            3, // 정점의 개수(사각형도 공식적으로 지원, 오각형 이상은 확인불가)
            &gTriangle, // 우리가 정점의 정보를 이용해 만들 도형
            1, // 이 도형을 만들 개수
            GRADIENT_FILL_TRIANGLE // 만들 도형을 어떻게 그릴지 스타일을 설정하는 플래그
        );
        // 본 함수를 이용하려면 MsImg32.lib를 이용해야 함. 본 문서 최상단의 전처리문 확인


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
