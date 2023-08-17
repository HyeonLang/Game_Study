#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
	SAFE_RELEASE(render_target_view);
	SAFE_RELEASE(device);
	SAFE_RELEASE(device_context);
	SAFE_RELEASE(swap_chain);
}

void Graphics::Initialize()
{
	// ����̽�, ����̽� ���ؽ�Ʈ, ����ü�� ����
	{
		// ���� ü���� ����� ���� ����
		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

		desc.BufferDesc.Width = 0;	// ���� ü���� ������ ������ ũ��
		desc.BufferDesc.Height = 0;	// ���� ü���� ������ ������ ũ��

		/*
			RefreshRate : ȭ�� �ֻ���, ȭ���� ��� �ֱ�� ������ ���ΰ�?
			Numerator : ����
			Denominator : �и�

			60/1 => 1�ʴ� 60�� ȭ���� ���� �ϰڴ� => 60������
		*/
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;

		/*

			RGBA : ���� ä���� �ǹ�, ������ ���� �����͸� ���� �ʿ�� ����.
			R8G8B8A8 : BPC, Color Depth��� �θ���
			������ ä�ο� ��ŭ�� �޸𸮸� �Ҵ������� �ǹ��Ѵ�.
			�� ä���� 8��Ʈ�̴� �� ä�δ� 0 ~ 255�� ������ ������.

			UNORM : Unsigned Normalize
			0 ~ 1 �� ����ȭ�� �����ͷ� ���ڴ�.
			�� ä���� 8��Ʈ�� ��� 0 ~ 255 ������ 0 ~ 1�� ����ȭ�Ͽ� ����Ѵٴ� ��

			DXGI_FORMAT_R8G8B8A8_UNORM
			=>	4����Ʈ ũ��(�� ä�δ� 8��Ʈ * 4)�� ������ ����ȭ�� �����͸� ��ڴ�.

			���� BPC ����
		*/
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// Scanline : ȭ���� ����� �� ���پ� �׾ ����ϴ� ��
		// UNSPECIFIED : �������� ����
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // ȭ�� ���/Ȯ���� �� � ȿ���� �ٰ��ΰ�?

		desc.BufferCount = 1; // ������ ����
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ���۸� ��� ����� ���ΰ�?

		/*
			Aliasing : �ȼ� ǥ������ ���� Ȯ���ϸ� �ܰ����� ���ó�� ���̴� ����

			Anti Aliasing(AA) - ��� ������ �����ϴ� ���
				�� Super Sampling AA(SSAA)
					�� ���ø� �����ŭ �ػ󵵸� Ȯ���� �Ŀ� Down Sampling(�ػ󵵸� �ٿ� ���� ���´�)�� �ϴ� ���
					�� ���� ���귮�� �޸𸮰� �ʿ��ϴ�

				�� Multi Sampling AA(MSAA)
					�� ���� ���귮�� �޸𸮸� �䱸�ϴ� SSAA�� �����ؼ� ���� ���
					�� �������� �����ڸ��� AA�� �����Ѵ�.

			// ���� ��Ƽ �ٸ���� �����ϱ�
		*/
		desc.SampleDesc.Count = 1;		// ������ ����, ���
		desc.SampleDesc.Quality = 0;	// ���ø��� ����Ƽ ����, 0�� ���ϰڴٴ� �ǹ�

		desc.OutputWindow = Settings::Get().GetWindowHandle(); // ����� ������ �ڵ�
		desc.Windowed = TRUE; // â��� ����

		// DXGI_SWAP_EFFECT_DISCARD : �����Ͽ� ���� �����͸� ����ϰڴ�
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // ���� �� � ȿ���� �� ���ΰ�?

		// D3D_FEATURE_LEVEL : ��� ����, DX �� ������ �� ���ΰ�?
		std::vector<D3D_FEATURE_LEVEL> feature_levels =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};
		
		HRESULT hr = D3D11CreateDeviceAndSwapChain
		(
			nullptr,					// ���� ī�带 ������ �� ���
			D3D_DRIVER_TYPE_HARDWARE,	// ����̽� Ÿ��
			nullptr,					// �ٸ� ����Ʈ��� �߰����� ������ ���
			0,							// ����̽��� ���� �� � ����� �߰������� ���� ���ΰ�?
			feature_levels.data(),		// ��ó ������ ���� �ּ�
			feature_levels.size(),		// ��ó ���� ����
			D3D11_SDK_VERSION,			// ����ϴ� SDK����
			&desc,						// ����ü�� desc 
			&swap_chain,				// ������ ����ü���� �Ҵ� �޴´�.
			&device,					// ������ ����̽��� �Ҵ� �޴´�.
			nullptr,					// ���õ� ��ó ������ ��ȯ�޴´�.
			&device_context				// ������ ����̽� ���ؽ�Ʈ�� �Ҵ� �޴´�.
		);
		assert(SUCCEEDED(hr));

	}
}

void Graphics::CreateBackBuffer(const uint& width, const uint& height)
{
	// ResizeBuffers : ���� ü���� ���������� �����ϴ� �Լ�
	// �������� ���� ���� �ʱⰪ�� ������ �������� �ʴ´�.
	HRESULT hr = swap_chain->ResizeBuffers
	(
		0,	// �ʱⰪ
		width,
		height,
		DXGI_FORMAT_UNKNOWN, // �ʱⰪ
		0 // �ʱⰪ
	);
	assert(SUCCEEDED(hr));

	ID3D11Texture2D* back_buffer = nullptr;

	/*
		Interface Identifier(IID)
			- �������̽��� �����ϱ� ���� �ĺ���
			- GUID�� ���� �ϳ��̴�.

		Globally Unique Identifier(GUID)
			- MS���� ����ϴ� ���� �׸��� �����ϱ� ���� �ĺ���
			- 16����Ʈ�� ũ�⸦ ������.
			- UUID��� �ִµ� ū ���̴� ����.

		���� : GUID, UUID����
	*/
	hr = swap_chain->GetBuffer // ����ü�� ������ ���۸� �����´�.
	(
		0, // ��� ���۸� ���� ���ΰ�
		__uuidof(ID3D11Texture2D), // �� ���۸� ��� ���·� �������� ���� �������̽� Ÿ��
		reinterpret_cast<void**>(&back_buffer) // ��ȯ�� �������̽��� �޴� ���� ������
	);
	assert(SUCCEEDED(hr));

	// ������ �� ���۸� ����Ͽ� ���� Ÿ�ٺ� ����
	hr = device->CreateRenderTargetView
	(
		back_buffer,	// �信�� ������ ���ҽ�, �ش� ���ҽ��� ����Ͽ� RTV ����
		nullptr,		// RTV�� desc, nullptr�Ͻ� ���ҽ��� ������ ������.
		&render_target_view	// RTV�� ���� ����
	);
	assert(SUCCEEDED(hr));

	// ����Ʈ �ʱ�ȭ
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(width);
	viewport.height = static_cast<float>(height);
	viewport.min_depth = 0.0f;
	viewport.max_depth = 1.0f;

	//����
	SAFE_RELEASE(back_buffer);
}
void Graphics::Begin()
{
	/*
		Output Merger Stage(OM) - ��� ���� �ܰ�
		- �׸��� �׸� ���� Ÿ���� �����ϰ�, ���� ��� �������ΰ�(����)�� �������ش�.
		- OM�� ���õ� �� �ִ� ���� Ÿ���� ������ 8���̴�. -> 8���� ���ÿ� �׸� �� �ִ�.
	*/
	device_context->OMSetRenderTargets(1, &render_target_view, nullptr); // �׸��� �׸� ���� Ÿ�� ����

	D3D11_VIEWPORT d3d11_viewport;

	d3d11_viewport.TopLeftX = viewport.x;
	d3d11_viewport.TopLeftY = viewport.y;
	d3d11_viewport.Width	= viewport.width;
	d3d11_viewport.Height	= viewport.height;
	d3d11_viewport.MinDepth = viewport.min_depth;
	d3d11_viewport.MaxDepth = viewport.max_depth;

	device_context->RSSetViewports(1, &d3d11_viewport); // �׸� ���� ����

	device_context->ClearRenderTargetView(render_target_view, clear_color); // ����Ÿ�� �ʱ�ȭ
}

void Graphics::End()
{
	HRESULT hr =  swap_chain->Present(1, 0);
	assert(SUCCEEDED(hr));
}
/*
	ID3D11Resource
		- DX���� �����ϴ� �ڿ����� ��ӹ޴� Ŭ����
		- ũ�� buffer, texture�� ������.

	ID3D11Buffer

	ID3D11Texture1D, ID3D11Texture2D, ID3D11Texture3D
	- 1D, 2D, 3D �̹����� �����ϴ� �ڿ�
	- �̹����� �������� ������ �ϱ� ������ �ڷ��������δ� ��� �뵵�� �����ϱ� ��ƴ�.
	- �뵵�� �����ϱ����� Resource View�� ����Ѵ�.
		�� Resource View
			- �ؽ�ó �ڿ��� �뵵�� ��Ȯ�� ���ش�
			�� ���� 
				- ID3D11RenderTargetView	: ȭ�鿡 �׸��� ���� �뵵
				- ID3D11ShaderResourceView	: �ڿ��� �ѱ�� ���� �뵵
				- ID3D11DepthStencilView	: ���� ������ �����ϴ� �뵵
				- ID3D11UnorderedAccessView	: �������� �����ϴ� �ڿ�
*/