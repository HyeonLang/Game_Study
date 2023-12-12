#include "pch.h"
#include "PixelShader.h"

PixelShader::PixelShader(LPCWSTR file_loc, DWORD flags)
{
	// �� ������ ȭ���� �ȼ��� �����ϴ� ���̴��� ���ؼ��� ���������� ó��
    // VertexShader�� �����ڸ� ����� ���� ����
    ID3DBlob* pixelBlob;
    D3DCompileFromFile(file_loc, nullptr, nullptr, "PS",
        "ps_5_0", flags, 0, &pixelBlob, nullptr);

    Device::Get()->GetDevice()->CreatePixelShader(pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(), nullptr, &PS);
    pixelBlob->Release();

    // DirectX���� ȭ���� ����� ���� �� ���̴���°��� ���� ���̴�, �ȼ����̴� �ּ� 2���� �ʿ�� �Ѵ�.
}

PixelShader::~PixelShader()
{
	Release();
}

void PixelShader::Release()
{
	PS->Release();
}
