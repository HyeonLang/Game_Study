// DirectX2D.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DirectX2D.h"

#define MAX_LOADSTRING 100

struct Vertex
{
    XMFLOAT3 position;
    // directX에서 사용하는, float 3개를 저장할 수 있는 구조체
};

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND hWnd;

ID3D11Device* device; // DirectX의 전반적인 과정을 감독 및 구동할 객체
ID3D11DeviceContext* device_context; // device를 통해 실제로 그림을 그리는 주체

IDXGISwapChain* swap_chain; // 더블 버퍼링에 사용되는 객체
ID3D11RenderTargetView* render_target_view; // 마찬가지

ID3D11VertexShader* vertex_shader; // "정점 셰이더" 
ID3D11PixelShader* pixel_shader; // "픽셀 셰이더"
// 이 둘은 화면의 각 픽셀(모니터에 출력하는 제일 작은 단위)에 들어가는 정보를 관리하는 부분

ID3D11InputLayout* input_layout;
ID3D11Buffer* vertex_buffer;
// 위의 셰이더가 제대로 처리할 수 있도록
// 셰이더에 들어갈 자료를 저장하는 버퍼

// DirectX를 통해서 화면을 출력하고자 할 때
// 그 과정에서 사용되는 각 객체들


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void InitDevice();
void Render();
void ReleaseDevice();

float ratio_pos_x(int pos_x, int mode);
float ratio_pos_y(int pos_x, int mode);

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
    LoadStringW(hInstance, IDC_DIRECTX2D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DIRECTX2D));

    MSG msg = {};

    InitDevice();

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

        Render();
    }

    ReleaseDevice();

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIRECTX2D));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DIRECTX2D);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

    RECT rect = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

    hWnd = CreateWindowW(szWindowClass,
        szTitle, WS_OVERLAPPEDWINDOW,
        WIN_START_X, WIN_START_Y,
        rect.right - rect.left, // 만들어지는 윈도우 창의 크기를 결정하는 부분(가로)
        rect.bottom - rect.top, // (세로)
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

void InitDevice() // 장치 초기화
// = DirectX를 사용하기 위해 관련 객체들을 여기서 초기화한다
{
    UINT width = WIN_WIDTH;
    UINT height = WIN_HEIGHT;

    DXGI_SWAP_CHAIN_DESC sd = {};
    // 더블 버퍼링을 구성할 때 그 더블 버퍼링의 각종 설정을 정의해두는 객체
    // API에서 MyRegisterClass 함수를 이용해
    // 윈도우 창의 설정을 담당할 객체를 만들고 각종 값들을 설정했던 것처럼
    // DX의 더블 버퍼링에선 sd가 그 역할을 한다

    sd.BufferCount = 1; // 더블버퍼링에 사용할 버퍼의 개수를 의미
    // 더블 버퍼링 외에도 버퍼를 총 3개 사용하는 삼중 버퍼링 같은 기법도 있는 등
    // 버퍼링을 처리하는 방법이 한둘이 아닌데, 그러다보니 사용하는 버퍼의 개수도 달라질 수 있어서
    // 그 개수를 여기다 명시하는 것

    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    // 버퍼가 다룰 화면의 크기를 지정

    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // DirectX에서는 화면 출력 등을 위해 DX의 각 모듈 사이에서 데이터를 보낼 때
    // 정확히 정해진 규격에서만 작동하도록 되어 있고
    // 그 규격과 일치하지 않으면 제대로 동작하지 않고 오류가 발생하게 됨
    // 이 규격이 어느 규격인지를 여기에서 정의

    // 이거 말고 다른 종류의 자료형들이 더 있긴 한데 지금은 다루지 않음
    // R8G8B8A8 = Red를 기록하는데 8비트, Green에 8비트, Blue에 8비트, Alpha값에 8비트
    // 이렇게 총 32비트를 다루는 포멧을 이용하겠다는 지정

    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    // 화면의 주사율을 설정하는 부분
    // (디스플레이의 모드 갱신률 : Numerator / Denominator)
    // 이 코드에서는 주시율을 60Hz, 초당 60화면이 지나갈 것을 상정한다

    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    // 버퍼가 어디에 사용될 것인지를 명시하는 것
    // 화면을 구성할 때 사용된다
    sd.OutputWindow = hWnd;
    // 어느 창에 이 더블 버퍼링을 구현할 것인지 등록하는 것

    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    // 이 둘은 설명 생략
    // 나중에 DirectX3D를 다룰 경우에 배우게 될 내용인데,
    // 2D에선 안 씀
    // 우리는 이 값은 각각 1, 0으로만 고정해둔다고 기억할 것

    sd.Windowed = true;
    // 창모드로 할 것인지 아닌지를 여기서 설정

    // 이렇게 위에서 설정한 내용들을 통해
    // DirectX 모듈에 더블버퍼링이 가능하도록 초기화를 해주는 함수
    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &sd,
        &swap_chain,
        &device,
        nullptr,
        &device_context
    );
    // API의 더블버퍼링과는 다르게, 일단 처음에 이렇게 세팅을 해뒀다면
    // 앞으로 우리가 더블 버퍼링을 위해 그릴 때 버퍼에 그림을 그린다던가 하는 작업을 거칠 필요 없음
    // 덤으로 위 함수의 각 매개변수의 의미는 설명하지 않을 예정 :
    // 이 함수의 의미를 우리가 기억해둘 이유가 없음. 대부분 이걸 그냥 가져다 쓸 예정이므로.

    ID3D11Texture2D* backBuffer = nullptr;
    // 더블 버퍼링에 사용할 진짜 버퍼가 저장될 변수
    swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &render_target_view);
    backBuffer->Release();

    device_context->OMSetRenderTargets(1, &render_target_view, nullptr);

    // 더블버퍼링 세팅을 완료하는 과정

    // 뷰포트 : 간단히 말해 시점
    // 3D 공간을 만들었다 치면, 단순히 놓여져있는 것만으론 안 되고
    // 그 공간의 어디서 어느 방향으로 보느냐에 따라서 실제로 우리 눈에 보이는 건 달라지기 마련
    // 그걸 "화면에 출력할 데이터를 전체 3D 공간에서 어느 부분을 보면 되는지를 지정하는 역할"

    // 실제 공간에 있는 데이터들을
    // 화면에 출력하기 위해 재구성하는데 필요한 요소

    // 그런 뷰포트를 바로 여기서 설정
    D3D11_VIEWPORT viewPort;
    viewPort.Width = width; // 우리가 설정한 창의 크기 전체를 화면에 표시하겠다
    viewPort.Height = height; // 마찬가지
    viewPort.MinDepth = 0.0f; // 깊이를 따지는 내용
    viewPort.MaxDepth = 1.0f; // 이에 대해서는 추후 3D를 배울 떄 다루게 될 것
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    device_context->RSSetViewports(1, &viewPort);
    // 그렇게 설정한 뷰포트를 device_context에 등록


    // 지금부터 설명할 내용들은
    // HLSL파일(= 셰이더 파일)을 만들고 진행해야 함
    // 해당 파일의 설명은 그 파일을 참조

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
    // 셰이더 파일을 불러올 때 사용하는 설정값
    // 우리는 이걸 건드릴 일이 없으니 위 설정대로만 간다 생각해도 무방

    ID3DBlob* vertexBlob;
    D3DCompileFromFile(L"Shader/VertexShader.hlsl", nullptr, nullptr, "VS",
        "vs_5_0", flags, 0, &vertexBlob, nullptr);
    // 우리가 만든 셰이더 파일을 DirectX 엔진에 설치하기 위해
    // hlsl 파일을 로드하는 과정

    device->CreateVertexShader(vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), nullptr, &vertex_shader);
    // 로드한 파일을 가지고 VertexShader를 구성하기 위해 사전작업을 하는 부분

    D3D11_INPUT_ELEMENT_DESC layouts[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    // 그래픽 파이프라인은 정해진 규격이 아니면 제대로 처리할 수 없어서,
    // 그 규격에 맞도록 입력될 데이터의 형식을 구성해줘야 함
    // 이 layouts는 그 입력될 데이터의 형식이 어떤 형식인지를 시스템에 미리 고지하는 역힐

    // 이게 선언된 뒤로는, 앞으로 VertexShader에 입력될 데이터는
    // 위에 언급된 규격과 정확히 일치해야 함

    // 이 규격의 자세한 구조에 대해선 추후 설명

    UINT layoutSize = ARRAYSIZE(layouts);
    // 그렇게 규격을 지정한 layouts의 총 용량을 계산
    // 바로 밑의 CreateInputLayout 함수에서 layouts의 총 용량을 직접 계산하지 못하기 때문에,
    // 우리가 미리 계산해서 알려줄 필요가 있기 때문

    device->CreateInputLayout(layouts, layoutSize, vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), &input_layout);
    vertexBlob->Release();
    // 위의 일련의 과정을 통해 실제로 그리기 위해 필요한 데이터를 저장해둘 공간을 마련하고,
    // 만들어진 버퍼를 DirectX 객체에 등록하는 코드
    // 등록이 완료되면 더 이상 필요없는 blob은 할당 해제

    // 이 모든 과정을 픽셀 셰이더에도 마찬가지로 해줌
    // 단, 픽셀 셰이더 쪽은 정점의 데이터를 직접 받는 게 아니고
    // 이미 정점 셰이더 쪽에서 처리된 데이터를 이용하기 때문에
    // 자료의 레이아웃을 다시 설정해줘야 할 필요는 없음
    ID3DBlob* pixelBlob;
    D3DCompileFromFile(L"Shader/VertexShader.hlsl", nullptr, nullptr, "PS",
        "ps_5_0", flags, 0, &pixelBlob, nullptr);

    device->CreatePixelShader(pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(), nullptr, &pixel_shader);
    pixelBlob->Release();

    // 여기까지가 픽셀 셰이더를 처리하는 부분

    // API의 경우, 도형을 그리기 위해선
    // API에서 기본적으로 제공되고 있던 함수를 이용하기만 하면 됐음
    // Rectangle() 등이 대표적
    // 반면, 그런 함수가 없는 경우엔 직접 선을 여러개 긋고 해서 그려야 했음
    // 삼각형 그릴 때의 LineTo가 대표적

    // DirectX는 이와는 정반대
    // 이 쪽은 삼각형을 그리는 함수가 기본적으로 제공되며,
    // 사각형이나 원 등을 기본적으로 그리도록 제공하는 함수가 없음

    // 그나마도 말이 기본제공이지
    // 정점들을 입력하면 그 입력된 정점들을 바탕으로 그리는 식

    // 여튼, 도형을 그리기 위해선 그 도형이 가지고 있는 정점을 이렇게 입력을 해줘야 함
    Vertex vertices[] =
    {
        // 2D로서 이용한다고는 해도 기본 시스템 자체는 3D이므로
        // 3D에서 사용하는 값으로서 만들어줘야 함
        XMFLOAT3(-0.8f, -0.8f, 0.0f), // X, Y, Z를 입력한 것
        XMFLOAT3(-0.2f, -0.2f, 0.0f), // 이런 점을 총 3개 입력
        XMFLOAT3(-0.2f, -0.8f, 0.0f),
        // 여기까지 첫번째 삼각형

        // 삼각형의 좌표를 보면
        // API에서는 화면 왼쪽 위를 기점으로 해서 X좌표와 Y좌표의 절대좌표를 이용했었지만
        // DirectX에서는 기본적으로 창의 정중앙을 기점으로 해서
        // 왼쪽 끝과 아래쪽 끝을 각각 -1.0으로, 오른쪽 끝과 위쪽 끝을 1.0으로 잡는
        // 상대좌표계를 이용하고 있음

        XMFLOAT3(-0.2f, -0.2f, 0.0f),
        XMFLOAT3(-0.8f, -0.8f, 0.0f),
        XMFLOAT3(-0.8f, -0.2f, 0.0f),
        // 3개의 점을 더 입력해서 2번째 삼각형을 만들었음

        // 여기서 주의해야 할 점 :
        // 3D 그래픽에선 모든 그래픽은 "폴리곤"(삼각형)을 기준으로 그림
        // 그리고 3D 그래픽에선 "앞면"과 "뒷면"이라는 개념이 있음
        // 실제 우리 생활을 생각해보면 우리는 모니터를 당장 보고 있지만
        // 우리 눈에는 모니터의 "뒷면"은 보이지 않고 있음
        // 실제 우리 눈에 보이는 것만 알아서 보이는 현실과는 달리
        // 프로그래밍 상의 공간에서는 그 어느 것이 보이고 어느 것이 보이지 않는지를
        // 알아서 판단해주지 않고 우리가 직접 지정을 해줘야 함
        // 이걸 하지 않는다 가정하면,
        // 커다란 주사위가 공간상에 존재하고 있다 칠 때 우리가 그걸 보면
        // 원래대로라면 많아봐야 3개 면만 볼 수 있음
        // 하지만 프로그램상 이 3개 면 외에 다른 면들도 존재하는데
        // 만약 이 면들이 보이는지 안 보이는지 처리를 하지 않으면
        // 이미 우리가 보고 있는 앞면 외에도 본래 보이지 말아야 할 뒷면이 보이는 상황이 생길 수 있음

        // 그리고 이 앞면과 뒷면이라는 것은 우리가 시점을 바꿀 때마다 항상 달라질 수 밖에 없음
        // 그러다보니 일일이 우리가 지정하는 게 아닌, 
        // 무언가 기준을 만들어서 그 기준에 맞으면 출력하고, 맞지 않으면 출력하지 않는 방식으로
        // 실제로 화면에 출력할 대상을 지정해야 정상적으로 오브젝트가 투과되어 보이지 않게 할 수 있음

        // 그 기준으로는 폴리곤의 "앞면"만을 화면에 출력하도록 정의되어 있음
        // 그리고 이게 폴리곤의 사전적 정의는 다각형임에도 무조건 삼각형으로만 사용되는 이유
        // = 3차원 공간에서는 3개의 점으로 만들어지는 평면은 단 하나밖에 존재하지 않고,
        // 반대로 그 어떤 경우건 점 3개면 반드시 하나의 평면을 표현할 수 있기 때문

        // 그리고 그 평면의 "앞면"은
        // 주어진 3개의 정점을 통해 만들어지는 평면에서,
        // 이 정점들을 나열했을 때 "시계방향"으로 보이는 방향을 앞면이라고 정의함

        // 따라서, DirectX에서 그래픽을 그릴 때, 화면에서 우리 눈에 보이게 하려면
        // 반드시 정점은 시계방향 순서대로 나열되어야만 함


        // 이하는 상대좌표 계산 함수를 만든 뒤 추가하는 좌표들

        XMFLOAT3(ratio_pos_x(140, 0), ratio_pos_y(180, 0), 0.0f), // 1번, 좌상
        XMFLOAT3(ratio_pos_x(320, 0), ratio_pos_y(100, 0), 0.0f), // 2번, 상
        XMFLOAT3(ratio_pos_x(320, 0), ratio_pos_y(260, 0), 0.0f), // 3번, 중앙
        XMFLOAT3(ratio_pos_x(500, 0), ratio_pos_y(180, 0), 0.0f), // 4번, 우상
        XMFLOAT3(ratio_pos_x(500, 0), ratio_pos_y(340, 0), 0.0f), // 5번, 우하
        XMFLOAT3(ratio_pos_x(320, 0), ratio_pos_y(420, 0), 0.0f), // 6번, 하
        XMFLOAT3(ratio_pos_x(320, 0), ratio_pos_y(260, 0), 0.0f), // 3번, 중앙
        XMFLOAT3(ratio_pos_x(140, 0), ratio_pos_y(340, 0), 0.0f), // 7번, 좌하
        XMFLOAT3(ratio_pos_x(140, 0), ratio_pos_y(180, 0), 0.0f),  // 8번=1번, 좌상

        // TRIANGLESTRIP을 사용했을 경우,
        // 짝수번째 삼각형을 그릴 때는 직전에 사용했던 2개 정점을
        // 순서를 바꿔서 삼각형을 그리는데 사용
        // 홀수번째는 다시 뒤쪽의 2개를 순서를 바꾸지 않고 그대로 사용

        // 이를 이용해 삼각형 6개로 육각형을 만들고자 할 때
        // 그 어떤 방법을 이용하더라도 결코 사용할 수 없는 선분이 하나 생김

        // 이 상황에서의 방법은 2가지 :
        // 1. 아예 해당 선분이 사용되는 것을 포기하고 다음 정점들에서부터 처리되도록 구성하는 것
        // 2. 아예 Draw 함수에서부터 이를 끊어버리고 새 Draw 함수를 이용하는 방법 2가지가 있음
        // (지금은 쓸 수 없는 방법인) 3. 애초에 이런 경우가 발생하지 않도록 도형을 구성하는 것



        XMFLOAT3(ratio_pos_x(880, 0), ratio_pos_y(180, 0), 0.0f),
        XMFLOAT3(ratio_pos_x(1080, 0), ratio_pos_y(180, 0), 0.0f),
        XMFLOAT3(ratio_pos_x(980, 0), ratio_pos_y(100, 0), 0.0f),
        XMFLOAT3(ratio_pos_x(980, 0), ratio_pos_y(260, 0), 0.0f),
        XMFLOAT3(ratio_pos_x(880, 0), ratio_pos_y(180, 0), 0.0f),
        // LINESTRIP용 정점들
    };
    // 위 내용을 보면, 분명히 점을 6개 입력했는데 만들어지는 삼각형이 2개
    // 거기에 두 삼각형은 서로 같은 점을 2개 이용하고 있음
    // 이에 대해선 Render()에서 하술


    // 위에서 설정된 정점들의 정보를 가지고
    // 정점 셰이더에서 입력받을 수 있는 형태의 데이터 저장 버퍼를 만들어내는 부분
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(vertices); // 위에서 구성한 정점들의 총 개수
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices;

    device->CreateBuffer(&bd, &initData, &vertex_buffer);
    // 이 7줄의 코드를 통해, 정점 셰이더에 우리가 구성했던 정점 데이터들을 전달
}

void Render() // 렌더링에서 말하는 렌더(Render = 세우다, 만들다, 빌드하다)
// = 화면에 실제로 출력할 결과물을 여기서 만들어낸다
// API에선 WM_PAINT 메세지를 받았을 때 처리했던 것을 DX에서는 이 Render 함수에서 처리한다
{
    float clear_color[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    // 앞에서부터 R, G, B, Alpha값 총 4개의 값을 저장
    // Alpha값을 다루는 날이 오기 전까진 1.0만 입력한다고 생각할 것
    // 
    // 색이 입력된 형태를 보면
    // API의 0~255까지의 값을 이용하는 게 아닌,
    // 0.0f~1.0f까지의 값을 이용하는 것
    // 따라서 우리가 지금까지 사용했던 색상표의 값을 그대로 사용하기는 힘듦
    // 지금까지 0~255까지 사용했던 것을 0.0f~1.0f의 범위로 스케일링해서 사용해야 한다
    device_context->ClearRenderTargetView(render_target_view, clear_color);
    // 화면 전체를 지정한 색으로 채워 초기화하는 함수

    UINT stride = sizeof(Vertex);
    // 버퍼에 정점을 저장할 때,
    // 정점에 들어갈 데이터가 프로그램 구성에 따라 다르다보니
    // 그 총 용량 역시 달라지게 되어있음
    // 따라서, 지금 사용되는 정점의 데이터 크기가 얼마나 되는지를 직접 계산해서 넣어줘야 함
    UINT offset = 0;
    // 오프셋 설정 - 나중에 다룰 때 설명. 지금 당장은 안 쓰니 0

    device_context->IASetInputLayout(input_layout);
    // input_layout을 device_context에 등록

    // 디바이스에 우리가 출력할 정점들의 정보를 넘겨주는 함수
    device_context->IASetVertexBuffers(
        0, // StartSlot : 넘겨주는 정점들 중 몇번째 정점부터 사용할 것인지 지정
        // 정점의 데이터를 처음부터 이용하지 않고 중간부터 이용하는 경우가 있을 수 있어서
        // 몇번째 데이터부터 사용하는지를 명시하는 것이 매개변수로 들어가있음
        1, // 버퍼를 하나만 보낼 수 있는 게 아니라
        // 버퍼가 저장된 포인터의 배열을 보낼 수도 있어서, 그런 케이스인 경우
        // 총 몇 개의 버퍼가 넘어가는지를 여기다 명시
        &vertex_buffer, // 실제로 정점 셰이더에 넘어갈 데이터가 저장된 버퍼
        &stride,
        &offset
    );

    device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    // 앞으로 우리가 그릴 그래픽이 무엇인지 열거형을 통해 설정
    // TRIANGLELIST : 입력된 정점들을 3개 단위로 묶어서,
    // 그 3개의 정점마다 삼각형을 하나씩 그리라고 설정
    // 
    // 이것 말고도 굉장히 많은 종류의 열거형 값이 있지만
    // 지금 당장은 생략 설명

    // 몇몇 예외를 제외하면 기본적으로 정점은 최소 3개를 필요로 한다 생각하면 됨
    // 몇몇 예외 중 하나 : LINELIST, LINESTRIP
    // LINELIST : 정점을 2개 단위로 받아서 각 2개 정점마다 선을 그리는 것
    // LINESTRIP : 정점을 최소 2개 이상 받아서, 
    // 첫번째 정점에서부터 연속적으로 다음 정점에 선을 그리는 방식

    // 도형 자체를 내일 이거저거 그려볼 예정이라 자세한 건 내일 설명드리도록 하겠습니다


    device_context->VSSetShader(vertex_shader, nullptr, 0);
    device_context->PSSetShader(pixel_shader, nullptr, 0);
    // 위에서 초기화해둿던 정점 셰이더와 픽셀 셰이더를 장치에 세팅

    device_context->Draw(6, 0);
    // 총 n개의 정점을, 전체 정점 리스트 중에서 k번째 정점부터 시작하여 그려라

    // 지금까지 설정된 값들을 토대로 총 6개의 정점을 그려라

    // 3D 공간에선 그래픽을 표시할 때 "폴리곤"을 최소 단위로 하여 화면에 표시
    // 따라서 뭘 그리고자 해도 최소 3개의 정점을 필요로 함
    // 그래서 3의 배수가 아니면 이 폴리곤을 구성할 수 있는 최소 정점의 개수가 확보가 되지 않아
    // 3의 배수를 만족하지 못한 데이터들은 화면에 출력되지 못하는 것

    device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    // 앞으로 그릴 도형을 변경
    // 삼각형을 그리는 것은 동일한데, LIST가 아닌 STRIP 방식으로 그림

    // TRIANGLESTRIP으로 그릴 경우,
    // 마지막으로 삼각형을 그린 뒤 그 삼각형에 사용되었던 정점 중 뒤쪽의 2개를 재활용해서
    // 새로 입력된 정점과 합해 삼각형을 그리는 것

    // 장점 : TRIANGLELIST에 비해 정점을 사용하는 양이 훨씬 적음
    // 한 삼각형이 무조건 정점 3개를 이용하는 LIST에 비해,
    // 기존의 정점을 재활용하는 STRIP은 사용하는 정점의 양이 더 적음
    // 나중에 가면 정점 하나에 저장되는 정보량이 무시 못할 정도로 불어나고, 
    // 사용하는 정점의 양 자체도 굉장히 늘어남

    // 단점 : 정점의 위치를 매번 반전하는 정점 순서에 맞게 고려해야 하다보니까
    // 원하는 대로 그리기에 쓰는 데는 난이도가 상당히 높음
    // 한마디로 쓰기가 좀 더 어려움

    device_context->Draw(9, 6);
    // 인덱스 6번 점(7번째 점)부터 3개의 정점을 이용해 도형을 그릴 것
    // 핵심은 출력하라고 명령한 정점의 개수가 3의 배수가 아니라는 것

    device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    // 앞으로 그릴 도형을 다시 변경
    // 이번에는 LINELIST를 그릴 것
    // LINELIST : 정점들을 2개씩 짝지어서, 그 두 정점을 잇는 선을 그리는 모드
    // 무조건 2개씩 짝지으므로 홀수개의 정점만 출력하라 할 경우엔 제대로 출력되지 않음

    device_context->Draw(2, 7);
    // 7,8번째 점은 마름모의 중앙에 있던 삼각형의 변을 출력
    // 다만 현재는 선과 도형의 색이 동일해서 그려도 의미가 없긴 함

    device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    // LINESTRIP : LINE의 STRIP, 즉 기존 정점을 재활용해서 선을 그리는 것
    // API로 쳤을 때의 MoveTo와 유사한 방식

    device_context->Draw(5, 15);


    swap_chain->Present(0, 0);
    // 다 그렸으면 더블 버퍼링을 시행해 그렸던 내용을 화면에 출력한다
}

void ReleaseDevice() // 프로그램 종료 시 동적 할당했던 것들 할당 해제
// 처음에 선언했던 것들을 보면 알 수 있듯,
// 지금 이 간략판에서조차 동적 할당을 해야 할 객체만 최소 8가지 이상
// 따라서 이것들을 반드시 프로그램이 종료될 때 할당을 해제해줘야 되고
// 이것들을 일일이 해제해주는 것은 번잡해지기 좋으니
// 관련한 할당 해제 코드를 이 ReleaseDevice 함수 하나에 몰아서 관리하는 것
{
    device->Release();
    device_context->Release();

    swap_chain->Release();
    render_target_view->Release();

    vertex_shader->Release();
    pixel_shader->Release();

    input_layout->Release();
    vertex_buffer->Release();
}

float ratio_pos_x(int pos_x, int mode)
// 입력한 절대좌표를 DirectX에서 쓸 수 있는 상대좌표로 변환해주는 함수
// 지금은 이렇게 임시로 만들지만 나중에 나갈 내용 중에 이를 대체하는 기능을 다룰 예정
{
    // mode : 기준점을 어디로 잡을 것인지를 설정하는 플래그
    // API에서 쓰던 대로 왼쪽 위를 기준점으로 잡고 싶을 경우 : 0,
    // DX에서 쓰는 그대로 정중앙을 기준점으로 잡고 싶을 경우 : 1

    float ratio;

    switch (mode)
    {
    case 0:
        ratio = ((float)pos_x - WIN_CENTER_X) / WIN_CENTER_X;
        break;
        // DX의 상대좌표계는 화면 전체를 기준으로 해서
        // 중앙에서 얼마나 멀리 떨어져있나를 기준점으로 삼음
        // 따라서 범위가 -1~1인데
        // API식으로 할 경우엔 입력범위가 0 ~ 화면 전체의 좌우 크기까지
        // 따라서 음수가 없음
        // 실제로 쓰기 위해선 보정을 거쳐서 -1~1까지의 범위로 만들어줄 필요가 있고
        // 이에 따라 화면 정중앙의 좌표를 입력받은 절대좌표에서 빼서 스케일링을 해줘야 할 필요가 있다

    case 1:
    default:
        ratio = (float)pos_x / WIN_CENTER_X;
        // DX에서 쓰던 대로 중앙을 기준으로 하고 절대좌표를 쓸 경우엔
        // 입력하는 순간부터 양수/음주를 결정해 입력하므로
        // 그런 보정을 할 필요가 없음
        // 따라서 그냥 입력받은 걸 그대로 화면 크기에 맞게 리사이징해주면 끝
        break;
    }

    return ratio;
}

float ratio_pos_y(int pos_y, int mode)
{
    float ratio;

    switch (mode)
    {
    case 0:
        ratio = -((float)pos_y - WIN_CENTER_Y) / WIN_CENTER_Y;
        break;
        // DX의 상대좌표계는 화면 전체를 기준으로 해서
        // 중앙에서 얼마나 멀리 떨어져있나를 기준점으로 삼음
        // 따라서 범위가 -1~1인데
        // API식으로 할 경우엔 입력범위가 0 ~ 화면 전체의 좌우 크기까지
        // 따라서 음수가 없음
        // 실제로 쓰기 위해선 보정을 거쳐서 -1~1까지의 범위로 만들어줄 필요가 있고
        // 이에 따라 화면 정중앙의 좌표를 입력받은 절대좌표에서 빼서 스케일링을 해줘야 할 필요가 있다

    case 1:
    default:
        ratio = (float)pos_y / WIN_CENTER_Y;
        // DX에서 쓰던 대로 중앙을 기준으로 하고 절대좌표를 쓸 경우엔
        // 입력하는 순간부터 양수/음주를 결정해 입력하므로
        // 그런 보정을 할 필요가 없음
        // 따라서 그냥 입력받은 걸 그대로 화면 크기에 맞게 리사이징해주면 끝
        break;
    }

    return ratio;
}

/*

과제 :

아까 봤듯이, 현재 출력되는 모든 도형들은 흰색으로 나오고 있음
이 색을 바꾸기 위해서는 어떤 식으로 해야 하는지에 대해선 설명한 적 없지만,

어제 설명했던 내용에서 색을 바꿀 수 있는 힌트는 이미 전부 드린 바 있음

-> 출력하는 도형들의 색을 흰색에서 다른 색으로 바꿔 출력해볼 것
-> 도형마다 다르게 출력하는 건 진짜 지금단계에선 불가능하고
모든 도형의 색을 흰색이 아닌 다른 색으로 바꾸는 것까지만 하면 됨

+ 기왕이면 지금 이렇게 그린 도형들 외에 다른 도형도 한번 그리는 것을 시도해보기
제일 난이도가 높을 거라 예상되는 건 원,
그거 말고 다른 걸 그려봐도 문제는 없음. 여튼 독자적으로 도형을 그려보기

*/