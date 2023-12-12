// �Ӽ� - �߰� ���� ���͸� : ./ = ��� ���� ������ �ν�
#include "pch.h"	

Device* Device::instance = nullptr;

UINT width = WIN_WIDTH; // UINT = unsigned int�� typedef�� �ٸ� �̸� ���� ��
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

void Device::CreateDeviceAndSwapChain() // ����̽� �ʱ�ȭ �� ������۸� �ʱ�ȭ
{
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;     // ���� ���۸��� ���� ����� �߰� ���� ����
    sd.BufferDesc.Width = width;     // ������ ���� ���� ũ�� ����
    sd.BufferDesc.Height = height;

    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // ���۰� ����� �ڷ��� ���� ����
    // ���۰� ����� �ڷ��� ���� ����
    // ��Ȯ�� � �ڷ����� �ִ����� ���� �ּҸ� ����
    // https://learn.microsoft.com/ko-kr/windows/win32/api/dxgiformat/ne-dxgiformat-dxgi_format

    // R8G8B8A8�� RGBA ���� 8��Ʈ�� �� 32��Ʈ�� ����Ѵٴ� �ǹ�
    // R5G6B5�� RGB 3������ �Ἥ, ���� 16��Ʈ���� ����ϵ��� �����͸� �Ʋ� ǥ���Ѵ�

    // R5G6B5�� ������ ������ �� ���� :
    // �츮�� ���ۿ��� ����־��� ������ 32��Ʈ ���̾��� ����

    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    // RefreshRate = �ֻ��� (���÷��� ��� ���ŷ� Numerator / Denominator)

    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // ���۰� ���� ���� ���
    sd.OutputWindow = hWnd;     // sd ��ü�� ��µ� â

    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    // �ֿ� ����� �ƴϹǷ� Ư���� �˾ƺ� �ʿ������ ����

    sd.Windowed = true;     // â��� ����

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
    );  // ������ �Ű������� �ǹ̸� ������ �ٷ��� ���� : ������ ������ ���� ������ ������ �ʱ�ȭ�ϴ� ����
}

void Device::CreateBackBuffer() // ������۸��� ����� ������ �ʱ�ȭ
{
    // �� �κ��� ���� �������� ���� ���۸� ������ �ϴ� �κ�
    // DX������ �츮�� ���� ��ü���� �˾Ƽ� ������۸��� ���ش�.

    ID3D11Texture2D* backBuffer = nullptr;
    //void������
    //IID(Interface ID)
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

    // ������� ���� ���۸�
}

void Device::SetViewPoint() // �� ����Ʈ �ʱ�ȭ
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
    // ����Ʈ�� �����ϴ� �κ�

    // ����Ʈ : ����
    // ������ ������� ������ ��, �츮�� ���� �� ������ ������ ����Ʈ�� ���� ����

}

void Device::Clear()    // ȭ���� ������ �������� �ʱ�ȭ�ϴ� �Լ�
{
    // ����� ���� �����ϴ� �迭 : red, green, blue, alpha �� 8bit�� �̿�: 0.0f ~ 1.0f 
   // API������ 0~255�� 0~1�� ����
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    // B5G6R5�� ������ �����ߴٸ� ���İ��� ������� �����Ƿ� ����

    deviceContext->ClearRenderTargetView(renderTargetView, clearColor); // ȭ���� clearColor�� �����ص� ������ �ʱ�ȭ
}

void Device::Present()  // ������۸� ���� = �� ���ۿ� �ִ� ������ ȭ�鿡 ǥ��
{
    swapChain->Present(0, 0);   // Present : (0, 0) ���۸��� ��ü�ϴ� ��� ��� ���� ����, ����ü�� Ŭ���� ���� �÷��� ���� ����
    // ���� ���۸� ��ü = Present �Լ��� �̿��� ȭ�� ��ü
}
