// 속성 - 추가 포함 디렉터리 : ./ = 모든 파일 폴더를 인식
#include "pch.h"	

Device* Device::instance = nullptr;

UINT width = WIN_WIDTH; // UINT = unsigned int를 typedef로 다른 이름 붙인 것
UINT height = WIN_HEIGHT;

Device::Device()
{
	CreateDeviceAndSwapChain();
	CreateBackBuffer();
	SetViewPoint();
}

Device::~Device()
{
	device->Release();
	deviceContext->Release();

	swapChain->Release();
	renderTargetView->Release();
}

void Device::CreateDeviceAndSwapChain() // 디바이스 초기화 및 더블버퍼링 초기화
{
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
}

void Device::CreateBackBuffer() // 더블버퍼링에 사용할 데이터 초기화
{
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
}

void Device::SetViewPoint() // 뷰 포인트 초기화
{
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

}

void Device::Clear()    // 화면을 지정한 배경색으로 초기화하는 함수
{
    // 출력할 색을 저장하는 배열 : red, green, blue, alpha 를 8bit씩 이용: 0.0f ~ 1.0f 
   // API에서의 0~255를 0~1로 조정
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    // B5G6R5로 위에서 선언했다면 알파값을 취급하지 않으므로 에러

    deviceContext->ClearRenderTargetView(renderTargetView, clearColor); // 화면을 clearColor에 지정해둔 색으로 초기화
}

void Device::Present()  // 더블버퍼링 실행 = 뒷 버퍼에 있는 내용을 화면에 표기
{
    swapChain->Present(0, 0);   // Present : (0, 0) 버퍼링을 교체하는 방식 모드 지정 변수, 스왑체인 클래스 관련 플래그 설정 변수
    // 더블 버퍼링 교체 = Present 함수를 이용해 화면 교체
}
