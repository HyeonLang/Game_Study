#include "pch.h"

Device* Device::instance = nullptr;

UINT width = WIN_WIDTH;
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
	device_context->Release();

	swap_chain->Release();
	render_target_view->Release();
}

void Device::CreateDeviceAndSwapChain()
// ������۸� ���� ������ �ʱ�ȭ�ϴ� �Լ�
{
    DXGI_SWAP_CHAIN_DESC sd = {};

    sd.BufferCount = 1; 

    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    // �� hWnd��ŭ�� �ܺο��� �޾ƿͼ� ����ؾ� ��

    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true;

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

    // ������ ������۸��� �����ϴ� �κ��� �״�� ������
}

void Device::CreateBackBuffer()
// ����۸� �ʱ�ȭ�ϰ� ����̽��� ����ϴ� �Լ�
{
    ID3D11Texture2D* backBuffer = nullptr;

    swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &render_target_view);
    backBuffer->Release();

    device_context->OMSetRenderTargets(1, &render_target_view, nullptr);

    // ���� ������Ʈ���� ����۸� �����ϰ� ����̽��� �̸� ����ϴ� �κ��� ������
}

void Device::SetViewPoint()
{
    D3D11_VIEWPORT viewPort;
    viewPort.Width = width; // �츮�� ������ â�� ũ�� ��ü�� ȭ�鿡 ǥ���ϰڴ�
    viewPort.Height = height; // ��������
    viewPort.MinDepth = 0.0f; // ���̸� ������ ����
    viewPort.MaxDepth = 1.0f; // �̿� ���ؼ��� ���� 3D�� ��� �� �ٷ�� �� ��
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    device_context->RSSetViewports(1, &viewPort);

    // ������ ����Ʈ�� ������ �� ����ߴ� �ڵ带 �״�� ������ ���

}

void Device::Clear()
// ȭ���� �ʱ�ȭ�ϴ� �Լ�
{
    float clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    device_context->ClearRenderTargetView(render_target_view, clear_color);

    // ������ Render() �Լ��� ó�� ������ ������ ȭ�� �ʱ�ȭ�ߴ� ����
    // Device�� ������μ� ��ȭ
}

void Device::Present()
// ������۸��� �����ϴ� �Լ�
{
    swap_chain->Present(0, 0);
}
