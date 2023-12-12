// DX_FirstStep.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DX_FirstStep.h"

#define MAX_LOADSTRING 100

struct Vertex // Vertex : 정점 = 3차원 공간에서의 한 점
{
    XMFLOAT3 position;
};

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND hWnd;                               
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

ID3D11Device* device;                       // cpu 연산, 리소스 로딩 등 출력 외 다른 기능들을 종합적으로 하는 기본 장치
ID3D11DeviceContext* deviceContext;         // gpu 연산 담당

IDXGISwapChain* swapChain;                  // 더블버퍼링에 사용되는 객체
ID3D11RenderTargetView* renderTargetView;   // 후면 버퍼에서 사용할 메모리

ID3D11VertexShader* vertexShader;
ID3D11PixelShader* pixelShader;

ID3D11InputLayout* inputLayout;             // CPU에서 처리된 각 정점에 대한 정보를 GPU에 넘길 때 필요한 객체
ID3D11Buffer* vertexBuffer;                 // GPU가 실제로 뭔가 출력하려면 VRAM에 메모리 정보가 저장되어 있어야 하고,
                                            // 그 정보를 저장해서 GPU에 할당해주는 메모리가 바로 이 버퍼


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


void InitDevice();
void Render();
void ReleaseDevice();

float calc_ratio_pos_x(int pos_x, int mode);
float calc_ratio_pos_y(int pos_y, int mode);

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
    LoadStringW(hInstance, IDC_DXFIRSTSTEP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DXFIRSTSTEP));

    MSG msg = {};

    InitDevice();

    // 기본 메시지 루프입니다:
    while (msg.message != WM_QUIT)  // WM_QUIT : 윈도우 창 종료 메세지
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            Render();
        }
    }
    // 윈도우 창이 꺼지기 전까지는 메세지를 처리 혹은 Render() 호출

    ReleaseDevice();

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DXFIRSTSTEP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DXFIRSTSTEP);
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

   RECT rect = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
   AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);   // RECT 구조체를 받아 그 크기로 윈도우 테두리 부분까지 고려하여 크기를 조절 

   hWnd = CreateWindowW(szWindowClass, 
       L"DirectX 2D With 3D",
       WS_OVERLAPPEDWINDOW,
       WIN_START_X, 
       WIN_START_Y, 
       rect.right - rect.left, 
       rect.bottom - rect.top, 
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

void InitDevice()   // 장치 초기화 : DirectX를 이용해 화면을 출력하기 위해 필요한 초기화
{
    UINT width = WIN_WIDTH; // UINT = unsigned int를 typedef로 다른 이름 붙인 것
    UINT height = WIN_HEIGHT; 

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;     // 다중 버퍼링을 위해 사용할 추가 버퍼 개수
    sd.BufferDesc.Width = width;     // 버퍼의 가로 세로 크기 설정
    sd.BufferDesc.Height = height;

    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // 버퍼가 취급할 자료의 형태 정의
    // 버퍼가 취급할 자료의 형태 정의
    // 정확히 어떤 자료형이 있는지는 다음 주소를 참고
    // https://learn.microsoft.com/ko-kr/windows/win32/api/dxgiformat/ne-dxgiformat-dxgi_format

    // R8G8B8A8은 RGBA 각각 8비트씩 총 32비트를 사용한다는 의미
    // R5G6B5는 RGB 3종류만 써서, 총합 16비트만을 사용하도록 데이터를 아껴 표기한다

    // R5G6B5로 했을때 오류가 난 이유 :
    // 우리가 버퍼에다 집어넣었던 색상값이 32비트 값이었기 때문

    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    // RefreshRate = 주사율 (디스플레이 모드 갱신률 Numerator / Denominator)

    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // 버퍼가 사용될 곳을 명시
    sd.OutputWindow = hWnd;     // sd 객체가 출력될 창

    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    // 주요 기능은 아니므로 특별히 알아볼 필요까지는 없음

    sd.Windowed = true;     // 창모드 유무
    
    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &sd,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );  // 각각의 매개변수의 의미를 지금은 다루지 않음 : 위에서 선언한 전역 포인터 변수를 초기화하는 개념
    

    // 이 부분이 더블 버퍼핑을 위해 버퍼링 설정을 하는 부분
    // DX에서는 우리가 만든 객체들이 알아서 더블버퍼링을 해준다.

    ID3D11Texture2D* backBuffer = nullptr;
    //void포인터
    //IID(Interface ID)
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

    // 여기까지 더블 버퍼링

    //------------------------------------------------------------------------

    D3D11_VIEWPORT viewPort;
    viewPort.Width = width;
    viewPort.Height = height;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    deviceContext->RSSetViewports(1, &viewPort);
    // 뷰포트를 설정하는 부분

    // 뷰포트 : 시점
    // 실제로 만들어진 데이터 중, 우리가 봐야 할 영역의 범위를 뷰포트를 통해 정의


    // 아래 내용은 설명을 위해 HLSL 파일(셰이더 파일)을 만들어야 한다.

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    // hlsl 파일을 로드하여 셰이더를 DirectX 개체에 설치하는 과정
    ID3DBlob* vertexBlob;
    D3DCompileFromFile(L"Shader/VertexShader.hlsl", nullptr, nullptr, "VS",
        "vs_5_0", flags, 0, &vertexBlob, nullptr);
     
    // 설치과정 2
    device->CreateVertexShader(vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), nullptr, &vertexShader);
    
    // 그렇게 설치한 셰이더를 통해 그림을 그릴 좌표가 지정되면 그 값을 가져와 저장할 공간을 만든다.
    D3D11_INPUT_ELEMENT_DESC layouts[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT layoutSize = ARRAYSIZE(layouts);   // 저장된 총량을 여기서 계산

    // 여기 까지를 통해 실제로 기리기 위해 필요한 데이터를 저장해둘 공간을 마련, 이를 DirectX 객체에 등록
    // 등록과정에서 잠시 사용했던 blob은 할당 해제
    device->CreateInputLayout(layouts, layoutSize, vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), &inputLayout);
    vertexBlob->Release();

    // 위 과정은 셰이더 중 vertex 셰이더, 즉 정점을 주로 다루는 셰이더에서만 했던 것
    // 이 과정을 화면의 픽셀을 관리하는 셰이더에 대해서도 마찬가지로 처리
    ID3DBlob* pixelBlob;
    D3DCompileFromFile(L"Shader/VertexShader.hlsl", nullptr, nullptr, "PS",
        "ps_5_0", flags, 0, &pixelBlob, nullptr);

    device->CreatePixelShader(pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(), nullptr, &pixelShader);
    pixelBlob->Release();

    // DirectX에서 화면을 출력할 때는 이 셰이더라는것을 정점 셰이더, 픽셀셰이더 최소 2개를 필요로 한다.

    //폴리곤(Polygon) : 정점 3개로 이루어진 삼각형
    // 
    // 3D : 기본적으로 풀력시 폴리곤을 최소 단위로 출력
    // 삼각형 등을 통해 조합
    //
    // 왼손법칙을 따른다.(시계방향 앞면) -> 정점 순서에 따라서 시계방향이 앞면을 의미하며 앞면만 출력된다.
    Vertex vertices[] =
    {
        //XMFLOAT3(-0.5f, -0.5f, 0.0f), 
        //XMFLOAT3(+0.5f, +0.5f, 0.0f),
        //XMFLOAT3(+0.5f, -0.5f, 0.0f),
        //// 첫번째 삼각형

        //XMFLOAT3(+0.5f, +0.5f, 0.0f),
        //XMFLOAT3(-0.5f, -0.5f, 0.0f),
        //XMFLOAT3(-0.5f, +0.5f, 0.0f),
        //// 두번째 삼각형

        XMFLOAT3(calc_ratio_pos_x(-50, 1),calc_ratio_pos_y(-50, 1),0.0f),
        XMFLOAT3(calc_ratio_pos_x(-50, 1),calc_ratio_pos_y(50, 1),0.0f),
        XMFLOAT3(calc_ratio_pos_x(50, 1),calc_ratio_pos_y(50, 1),0.0f),

        XMFLOAT3(calc_ratio_pos_x(50, 1),calc_ratio_pos_y(50, 1),0.0f),
        XMFLOAT3(calc_ratio_pos_x(50, 1),calc_ratio_pos_y(-50, 1),0.0f),
        XMFLOAT3(calc_ratio_pos_x(-50, 1),calc_ratio_pos_y(-50, 1),0.0f),

        
    };  
   /* Vertex vertices[] =
    {
        XMFLOAT3(-0.75f, 0.25f, 0.0f), 
        XMFLOAT3(-0.25f, 0.75f, 0.0f),
        XMFLOAT3(0.0f, 0.0f, 0.0f),

        XMFLOAT3(-0.25f, 0.75f, 0.0f),
        XMFLOAT3(0.25f, 0.75f, 0.0f),
        XMFLOAT3(0.0f, 0.0f, 0.0f),

        XMFLOAT3(0.25f, +0.75f, 0.0f),
        XMFLOAT3(0.75f, 0.25f, 0.0f),
        XMFLOAT3(0.0f, 0.0f, 0.0f),

        XMFLOAT3(0.75f, 0.25f, 0.0f),
        XMFLOAT3(0.75f, -0.25f, 0.0f),
        XMFLOAT3(0.0f, 0.0f, 0.0f),

        XMFLOAT3(0.75f, -0.25f, 0.0f),
        XMFLOAT3(0.25f, -0.75f, 0.0f),
        XMFLOAT3(0.0f, 0.0f, 0.0f),

        XMFLOAT3(0.25f, -0.75f, 0.0f),
        XMFLOAT3(-0.25f, -0.75f, 0.0f),
        XMFLOAT3(0.0f, 0.0f, 0.0f),

        XMFLOAT3(-0.25f, -0.75f, 0.0f),
        XMFLOAT3(-0.75f, -0.25f, 0.0f),
        XMFLOAT3(0.0f, 0.0f, 0.0f),

        XMFLOAT3(-0.75f, -0.25f, 0.0f),
        XMFLOAT3(-0.75f, 0.25f, 0.0f),
        XMFLOAT3(0.0f, 0.0f, 0.0f),
        
    }; */  
    // XMFLOAT3의 값이 지정하는 값 : 화면 전체 비율에서 중앙을 0.0으로 한다. [왼쪽/아래 -1.0 ~ 1.0 오른쪽/위]
    // (API는 왼쪽 위 기준, DX는 왼쪽 아래 기준)
    // 세번째 값은 z축 (앞 뒤)
    // 정점 3개를 입력해 폴리곤(삼각형)을 하나 만들어뒀음
    // 사실 여기서 만들어둬야 하는 것까진 아니고
    // 예시를 위해서 여기서 삼각형 하나를 만들어두고 그 정점을 입력한 것으로
    // 나중에는 여기가 아니라 메인 코드를 실행할 때 사용할 자료값

    // API에서 색 채우는 삼각형 그릴 때
    // 범위 지정하거나 선 긋는 걸로 그리는 거 말고
    // 각 꼭지점들의 위치를 지정해서 그렸던 것을 기억할 건데

    // 그 때는 각 꼭지점들을 그리기 직전에 세팅해서 그떄그때 추가해가지고 그렸던 건데
    // 지금은 그 꼭지점들을 미리 만들어둔 것

    // 지금 이건 나중에 도형을 그릴 때 사용할 꼭지점만 미리 만들어둔 것으로,
    // 이걸로 아직 도형이 만들어진 건 아님

    // 폴리곤을 기반으로 DX에서 다룰 객체가 사용할 버퍼를 설정
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(vertices);
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices;
    // DirectX에서 이런 꼭지점들을 사용하려면 이것들을 셰이더에 호환되는 구조의 버퍼에 저장해서
    // 그 버퍼의 내용을 셰이더로 옮기는 과정을 거쳐야 한다.

    device->CreateBuffer(&bd, &initData, &vertexBuffer);    // 최종적으로 여기서 그림을 그릴 내용을 저장해둘 버퍼가 등록
}

void Render()
{
    // 출력할 색을 저장하는 배열 : red, green, blue, alpha 를 8bit씩 이용: 0.0f ~ 1.0f 
    // API에서의 0~255를 0~1로 조정
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };   
    // B5G6R5로 위에서 선언했다면 알파값을 취급하지 않으므로 에러

    deviceContext->ClearRenderTargetView(renderTargetView, clearColor); // 화면을 clearColor에 지정해둔 색으로 초기화

    UINT stride = sizeof(Vertex);   // 버퍼에 저장할 정점의 구조에 따라 변동하는 정점 하나 데이터의 용량 저장 변수
    UINT offset = 0;                // offset 설정

    deviceContext->IASetInputLayout(inputLayout);
    // deviceContext에 inputLayout 등록

    deviceContext->IASetVertexBuffers(
        0,                  // StartSlot : 넘겨주는 정점들 중 몇번째 정점부터 사용할 것인지 지정
        1,                  // 버퍼 배열의 주소가 넘어 갈 경우, 버퍼의 개수를 표기, 보통은 1
        &vertexBuffer,      // 디바이스에 넘길 버퍼의 주소
        &stride,            // 버퍼가 보유하는 각 정점 하나의 메모리 용량
        &offset             
    );
    // 디바이스에 우리가 출력할 정점들의 정보를 넘겨주기
    
    // 아까 InitDevice에서 정점들을 만들어서 그 정점 정보는 버퍼에 넘긴것을 화면출력장치에 넘겨주는 함수
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    // 이제 이 장비를 통해 우리가 뭘 출력할 것인지를 지정
    // 정확히는 미리 열거형을 통해 정의되어있는 "출력 가능한 도형" 중 어느 것을 이용할 것인지 지정하는 함수

    // D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST : 입력받은 정점을 3개씩 끊어서 삼각형을 그리는 모드

    deviceContext->VSSetShader(vertexShader, nullptr, 0);
    deviceContext->PSSetShader(pixelShader, nullptr, 0);
    // 정점 셰이더와 픽셀 셰이더를 등록

    // 여기까지는 그림을 그리는데 필요한 것들을 상세히 설정함.

    // 실제로 그리는 코드
    deviceContext->Draw(24, 0);  // Draw : (3, 0) 최대 3개의 정점을 이용해 0번째 정점부터 그리기
    // 디바이스에 등록된 정점 3개를 이용해 그리기

    // 삼각형만 그릴 수 있게 되어있다. 다른 도형을 그리려면 이걸 응용해서 만들어야 한다.

    swapChain->Present(0, 0);   // Present : (0, 0) 버퍼링을 교체하는 방식 모드 지정 변수, 스왑체인 클래스 관련 플래그 설정 변수
    // 더블 버퍼링 교체 = Present 함수를 이용해 화면 교체


    /*
        과제

        8각형을 삼각형을 이용하여 그리기
    */
}

void ReleaseDevice()
{
    device->Release();
    deviceContext->Release();

    swapChain->Release();
    renderTargetView->Release();

    vertexShader->Release();
    pixelShader->Release();

    inputLayout->Release();
    vertexBuffer->Release();
}

float calc_ratio_pos_x(int pos_x, int mode)   // 입력한 x좌표를 -1.0f ~ 1.0f로 전환
{
    // mode = 0 : 왼쪽 하단 기준, mode = 1 : 중앙 기준
    float ratio;

    switch (mode) {
    case 0:
        ratio = ((float)pos_x - WIN_CENTER_X) / WIN_CENTER_X;
        break;
    case 1:
    default: 
        ratio = (float)pos_x / WIN_CENTER_X;
        break;
    }
    
    
    return ratio;
}

float calc_ratio_pos_y(int pos_y, int mode)   // 입력한 y좌표를 -1.0f ~ 1.0f로 전환
{
    // mode = 0 : 왼쪽 하단 기준, mode = 1 : 중앙 기준
    float ratio;

    switch (mode) {
    case 0:
        ratio = ((float)pos_y - WIN_CENTER_Y) / WIN_CENTER_Y;
        break;
    case 1:
    default:
        ratio = (float)pos_y / WIN_CENTER_Y;
        break;
    }
    return ratio;
}
